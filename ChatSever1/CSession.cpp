#include "CSession.h"
#include "CServe.h"
#include <iostream>
#include <sstream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "LogicSystem.h"
#include "RedisMgr.h"
#include "ConfigMgr.h"
#include"const.h"
CSession::CSession(boost::asio::io_context& ioc,CServe* cserver):_socket(ioc) , serve(cserver),b_close(false){
	boost::uuids::uuid  a_uuid = boost::uuids::random_generator()();
	session_id = boost::uuids::to_string(a_uuid);
	_recv_head_node = std::make_shared<MsgNode>(HEAD_TOTAL_LEN);
}

tcp::socket& CSession::Getsocket() {

	return _socket;
}

void CSession::Close() {
	std::lock_guard<std::mutex>lock(_session_lock);
	_socket.close();
	b_close = true;
}

void CSession::Start() {
	AsyncReadHead(HEAD_TOTAL_LEN);
}

std::string& CSession::Geisessionid() {
	return session_id;
}
void CSession::SetUserid(int uid) {
	user_id = uid;
}
int CSession::GetUserid() {
	return user_id;
}

void CSession::AsyncReadHead(int total) {
	auto self = shared_from_this();
	AsyncReadfull(total, [self,this](boost::system::error_code error, std::size_t size) {
		try {
			if (error) {
				std::cout << "AsyncReadLen error is " << error.what() << std::endl;
				serve->Clearcsession(this->session_id);
				Close();
				return;
			}
			_recv_head_node->Clear();
			memcpy(_recv_head_node->_data, _data, size);
			short msg_id = 0; 
			memcpy(&msg_id, _recv_head_node->_data, HEAD_ID_LEN);
			msg_id= boost::asio::detail::socket_ops::network_to_host_short(msg_id);
			std::cout << "msg_id is " << msg_id << std::endl;

			if (msg_id > MAX_LENGTH) {
				std::cout << "msg_id is error" <<  std::endl;
				serve->Clearcsession(session_id);
				Close();
				return;
			}

			short msg_len = 0;
			memcpy(&msg_len, _recv_head_node->_data+ HEAD_ID_LEN, HEAD_DATA_LEN);
			msg_len = boost::asio::detail::socket_ops::network_to_host_short(msg_len);
			std::cout << "msg_len is " << msg_len << std::endl;

			if (msg_len > MAX_LENGTH) {
				std::cout << "msg_len is error" << std::endl;
				serve->Clearcsession(session_id);
				Close();
				return;
			}

			_recv_msg_node = std::make_shared<RecvNode>(msg_len, msg_id);
			AsyncReadBody(msg_len);

		}
		catch (std::exception e) {
			std::cout << "AsyncReadfull error is " << e.what() << std::endl;
		}
	});
}

void CSession::AsyncReadfull(std::size_t total,
	std::function<void(boost::system::error_code error, std::size_t size)> hander) {
	::memset(_data, 0, MAX_LENGTH);
	AsyncReadLen(0, total, hander);
}

void CSession::AsyncReadLen(std::size_t read_len, std::size_t total,
	std::function<void(boost::system::error_code error, std::size_t size)> hander) {
	auto self = shared_from_this();
	_socket.async_read_some(boost::asio::buffer(_data + read_len, total - read_len),
		[read_len, total,hander,self](boost::system::error_code error, std::size_t size) {
			if (error) {
				std::cout << "AsyncReadLen error is " << error.what() << std::endl;
				self->serve->Clearcsession(self->session_id);
				self->Close();
				return;
			}

			if (size+ read_len >=total) {
				hander(error, read_len + size);
				return;
			}
			self->AsyncReadLen(size + read_len, total, hander);

		});
}


void CSession::AsyncReadBody(int total_len) {
	auto self = shared_from_this();
	AsyncReadfull(total_len, [self, this, total_len](boost::system::error_code error, std::size_t size) {
		try {
			if (error) {
				std::cout << "AsyncReadfull(body) error is " << error.what() << std::endl;
				serve->Clearcsession(session_id);
				Close();
				return;
			}

			memcpy(_recv_msg_node->_data, _data, size);
			_recv_msg_node->cur_len += size;
			_recv_msg_node->_data[_recv_msg_node->total_len] = '\0';
			std::cout << "receive data is " << _recv_msg_node->_data << std::endl;

			LogicSystem::GetInstance()->PostMsgToQue(std::make_shared<LogicNode>(shared_from_this(), _recv_msg_node));
			AsyncReadHead(HEAD_TOTAL_LEN);
		}
		catch (std::exception error) {
			std::cout << "AsyncReadBody error is " << error.what() << std::endl;
		}
	});
}


void CSession::Send(std::string msg, short msgid) {
	std::lock_guard<std::mutex> lock(_session_lock);
	auto send_queue_size = send_queue.size();
	if (send_queue_size > MAX_SENDQUE) {
		std::cout << "session send queue is too much" << std::endl;
		return;
	}

	send_queue.push(std::make_shared<SendNode>(msg.c_str(), msg.length(), msgid));
	auto msgnode = send_queue.front();
	if (send_queue_size > 0) {
		return;
	}

	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
}
void CSession::Send(char* data, short len, short msgid) {
	std::lock_guard<std::mutex> lock(_session_lock);
	auto send_queue_size = send_queue.size();
	if (send_queue_size > MAX_SENDQUE) {
		std::cout << "session send queue is too much" << std::endl;
		return;
	}

	send_queue.push(std::make_shared<SendNode>(data, len, msgid));
	auto msgnode = send_queue.front();
	if (send_queue_size > 0) {
		return;
	}

	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
}

std::shared_ptr<CSession> CSession::SharedSelf(){
	return shared_from_this();
}
void CSession::HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self) {
	std::lock_guard<std::mutex> lock(_session_lock);
	auto self = shared_from_this();
	send_queue.pop();
	if (!error) {
		if (!send_queue.empty()) {
			auto& msgnode = send_queue.front();
			boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->total_len),
				std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
		}
	}
	else {
		std::cout << "handle write failed, error is " << error.what() << std::endl;
		Close();
		self->serve->Clearcsession(session_id);
	}
	
}


LogicNode::LogicNode(std::shared_ptr<CSession> csession, std::shared_ptr<RecvNode> recvnode):_CSession(csession),_RecvNode(recvnode) {

}