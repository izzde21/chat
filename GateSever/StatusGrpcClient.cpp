#include "StatusGrpcClient.h"
StatusGrpcClient::StatusGrpcClient() {
	auto& mfg = ConfigMgr::GetConfigMgr();
	auto host = mfg["StatusServer"]["Host"];
	auto port = mfg["StatusServer"]["Port"];
	std::cout << "Connecting to " << host << ":" << port << std::endl;
	_pool.reset(new StatusPool(5, host, port));
}


//获取可用服务器信息的grpc服务
GetChatServerRsp StatusGrpcClient::GetChatServer(int uid) {
	ClientContext context;
	GetChatServerReq request;
	GetChatServerRsp reply;
	request.set_uid(uid);
	auto stub = _pool->Getcon();
	if (!stub) {
		reply.set_error(RPCFailed);
		std::cout << "stub is null" << std::endl;
		return reply;
	}
	Status stauts = stub->GetChatServer(&context, request, &reply);
	Defer defer([this, &stub]() {
		_pool->returncon(std::move(stub));
		});
	if (stauts.ok()) {
		return reply;
	}
	else {
		reply.set_error(SUCCESS);
		return reply;
	}
}


//获取可用登录的grpc服务
LoginRsp StatusGrpcClient::Login(int uid, std::string token) {
	ClientContext context;
	LoginRsp reply;
	LoginReq request;
	auto stub = _pool->Getcon();
	Defer defer([this, &stub]() {
		_pool->returncon(std::move(stub));
		});
	Status stauts = stub->Login(&context, request, &reply);
	if (stauts.ok()) {
		return reply;
	}
	else {
		reply.set_error(RPCFailed);
		return reply;
	}
}