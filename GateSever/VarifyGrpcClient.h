#pragma once
#include"const.h"
#include"Singelton.h"
#include "message.grpc.pb.h"
#include<grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class RPConpool
{
public:
	RPConpool(std::size_t size, std::string ip, std::string port);
	std::unique_ptr<VarifyService::Stub> Getstub();
	void BackStub(std::unique_ptr<VarifyService::Stub> content);
	void Close();
	~RPConpool();
private:

	std::size_t _size;
	std::string _ip;
	std::string _port;
	std::queue<std::unique_ptr<VarifyService::Stub>> connections_;
	bool _b_stop;
	std::condition_variable cond_;
	std::mutex mutex_;
};

class VarifyGrpcClient:public Singelton<VarifyGrpcClient>
{
	friend class Singelton<VarifyGrpcClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext Context;
		GetVarifyRsp reply;
		GetVarifyReq request;
		request.set_email(email);
		auto stub=pool_->Getstub();
		Status status= stub->GetVarifyCode(&Context, request, &reply);
		if (status.ok()) {
			pool_->BackStub(std::move(stub));
			return reply;
		}
		else {
			pool_->BackStub(std::move(stub));
			reply.set_error(ErrorCode::RPCFailed);
			return reply;
		}

	}
private:
	VarifyGrpcClient();
	std::unique_ptr<RPConpool> pool_;
	
};

