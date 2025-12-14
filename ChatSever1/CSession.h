#pragma once
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <queue>
#include <mutex>
#include <memory>
#include "MsgNode.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class CServe;

class CSession:public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& ioc, CServe * q);
	tcp::socket& Getsocket();
	void Start();
	void Close();
	std::string &Geisessionid();
	void SetUserid(int uid);
	int GetUserid();
	char _data[MAX_LENGTH];
	std::shared_ptr<MsgNode>_recv_head_node;
	std::shared_ptr<RecvNode>_recv_msg_node;
	std::shared_ptr<CSession> SharedSelf();
	void HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self);
	void Send(std::string msg,short msgid);
	void Send(char* data, short len, short msgid);
	void AsyncReadBody(int total_len);
	void AsyncReadHead(int total);
	void AsyncReadfull(std::size_t total,std::function<void(boost::system::error_code error,std::size_t size)> hander);
	void AsyncReadLen(std::size_t read_len, std::size_t total,std::function<void(boost::system::error_code error, std::size_t size)> hander);
private:
	bool b_close;
	CServe* serve;
	tcp::socket _socket;
	std::string session_id;
	std::mutex _session_lock;
	std::queue<std::shared_ptr<SendNode>> send_queue;
	int user_id;
};


class LogicNode
{
public:
	LogicNode(std::shared_ptr<CSession> csession, std::shared_ptr<RecvNode> recvnode);
	std::shared_ptr<CSession> _CSession;
	std::shared_ptr<RecvNode> _RecvNode;
};
