#include "CServe.h"
#include"AaioIoServerPool.h"
#include"UserMgr.h"
CServe::CServe(net::io_context& ioc, unsigned short port) :_acceptor(ioc,boost::asio::ip::tcp::endpoint(tcp::v4(),port)),_ioc(ioc)
{
	std::cout << "Server start success, listen on port : " << port << std::endl;
	StartAccept();
}

void CServe::StartAccept() {
	auto& ioc = AaioIoServerPool::GetInstance()->GetIoServer();
	std::shared_ptr<CSession> new_csession = std::make_shared<CSession>(ioc, this);
	_acceptor.async_accept(new_csession->Getsocket(), [this,new_csession](boost::system::error_code error) {
		this->HandlesAccept(new_csession,error);
	});
}

void CServe::HandlesAccept(std::shared_ptr<CSession> new_session, const boost::system::error_code& error) {
	if (!error) {
		new_session->Start();
		std::lock_guard<std::mutex> lock(_mutex);
		_sessions.insert(std::make_pair(new_session->Geisessionid(), new_session));
	}
	else {
		std::cout << "error HandlesAccept " << error.what() << std::endl;
	}

	StartAccept();
}

void CServe::Clearcsession(std::string session_id) {
	std::lock_guard<std::mutex> lock(_mutex);
	if (_sessions.find(session_id) == _sessions.end()) {
		auto userid = _sessions[session_id]->GetUserid();

		UserMgr::GetInstance()->RmvUserSession(userid, session_id);
	}
	_sessions.erase(session_id);
}