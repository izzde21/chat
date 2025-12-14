#pragma once
#include"const.h"
#include<iostream>
class CServe:public std::enable_shared_from_this<CServe>
{
public:
	CServe(net::io_context& ioc, unsigned short port);
	void Start();
	net::io_context& _ioc;
private:
	tcp::acceptor _acceptor;
	
};

