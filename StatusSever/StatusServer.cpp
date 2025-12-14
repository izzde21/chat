#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "const.h"
#include "ConfigMgr.h"
#include "hiredis.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "AaioIoServerPool.h"
#include <memory>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "StatusServiceImpl.h"
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"

void run()
{
	auto& cfg = ConfigMgr::GetConfigMgr();
	std::string server_address(cfg["StatusServer"]["Host"] + ":" + cfg["StatusServer"]["Port"]);
	grpc::ServerBuilder builder;

	StatusServiceImpl sever;

	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&sever);

	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	boost::asio::io_context ioc;
	boost::asio::signal_set signal(ioc,SIGINT, SIGTERM);
	signal.async_wait([&](const boost::system::error_code & error, int signal_number) {
		std::cout << "Shutting down server..." << std::endl;
		ioc.stop();
		server->Shutdown();
		});

	// 在单独的线程中运行io_context
	std::thread([&ioc]() { ioc.run(); }).detach();

	// 等待服务器关闭
	server->Wait();
}


int main() {
	try {
		run();
		std::cout << "启动成功" << std::endl;
		RedisMgr::GetInstance()->Close();
	}
	catch (std::exception e) {
		std::cout << "statusserver启动失败" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}