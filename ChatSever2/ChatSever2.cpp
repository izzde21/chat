#include<iostream>
#include"ConfigMgr.h"
#include"const.h"
#include"AaioIoServerPool.h"
#include"CServe.h"
#include"RedisMgr.h"
#include"ChatServiceImpl.h"
int main() {
	try {
		auto& cfg = ConfigMgr::GetConfigMgr();
		auto port = cfg["SelfServer"]["Port"];
		//设置本服务器的次数为0
		RedisMgr::GetInstance()->HSet(LOGIN_COUNT, cfg["SelfServer"]["Name"], "0");

		std::string address = cfg["SelfServer"]["Host"] + ":" + cfg["SelfServer"]["RPCPort"];
		ChatServiceImpl service;
		grpc::ServerBuilder builder;
		builder.AddListeningPort(address, grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		std::unique_ptr<grpc::Server>server (builder.BuildAndStart());
		std::cout << "RPC Server listening on " << address << std::endl;

		std::thread grpc_thread([&server]() {
			server->Wait();
			});

		auto pool = AaioIoServerPool::GetInstance();
		std::cout << "listen " << port << std::endl;
		boost::asio::io_context ioc;
		boost::asio::signal_set signal(ioc, SIGINT, SIGTERM);
		signal.async_wait([&ioc,pool,&server](auto,auto) {
			ioc.stop();
			pool->stop();
			server->Shutdown();
			});
		
		CServe cs(ioc, atoi(port.c_str()));
		ioc.run();

		RedisMgr::GetInstance()->HDel(LOGIN_COUNT, cfg["SelfServer"]["Name"]);
		RedisMgr::GetInstance()->Close();
		grpc_thread.join();
	}
	catch (std::exception e) {
		std::cout << "chatsever1 error " << e.what() << std::endl;
	}

}