#pragma once
#include"const.h"
#include"Singelton.h"
#include<vector>
#include<thread>
#include<iostream>
class AaioIoServerPool:public Singelton<AaioIoServerPool>
{
	
	friend	class Singelton<AaioIoServerPool>;
public:
	using IoServer = net::io_context;
	using Work = boost::asio::executor_work_guard <boost::asio::io_context::executor_type>;
	using WorkPtr = std::unique_ptr<Work>;
	AaioIoServerPool(const AaioIoServerPool &)= delete;
	AaioIoServerPool& operator=(const AaioIoServerPool&) = delete;
	void stop();
	net::io_context& GetIoServer();
	~AaioIoServerPool();
private:
	AaioIoServerPool(std::size_t size = std::thread::hardware_concurrency());
	std::size_t size;
	int NextIoServer;
	std::vector<IoServer> _IoServer;
	std::vector<WorkPtr> _Work;
	std::vector<std::thread> _threads;
};

