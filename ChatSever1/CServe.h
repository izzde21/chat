#pragma once
#include <boost/asio.hpp>
#include <memory.h>
#include <map>
#include <mutex>
#include <boost/asio/steady_timer.hpp>
#include "CSession.h"
class CServe:public std::enable_shared_from_this<CServe>
{
public:
	CServe(boost::asio::io_context& ioc, unsigned short port);
	void StartAccept();
	void HandlesAccept(std::shared_ptr<CSession> new_session, const boost::system::error_code& error);
	boost::asio::io_context& _ioc;
	void Clearcsession(std::string uuid);
private:
	boost::asio::ip::tcp::acceptor _acceptor;
	std::map<std::string, std::shared_ptr<CSession>> _sessions;
	std::mutex _mutex;
};

