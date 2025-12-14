#pragma once
#include "const.h"
#include "Singelton.h"
#include <grpcpp/grpcpp.h> 
#include "message.grpc.pb.h"
#include "message.pb.h"
#include"ConfigMgr.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

class StatusPool
{
public:
	StatusPool(int poolsize, std::string host, std::string port) :pool_size(poolsize), _host(host), _port(port), _b_stop(false){
		for (int i = 0; i < pool_size; ++i) {
			std::shared_ptr<Channel> channel = grpc::CreateChannel(_host + ":" + _port, 
				grpc::InsecureChannelCredentials());
			if (!channel) {
				std::cout << "channel is null" << std::endl;
			}
			_con.push(StatusService::NewStub(channel));
		}
	}

	~StatusPool() {
		std::lock_guard<std::mutex> lock(_mutex);
		Close();
		while (!_con.empty()) {
			_con.pop();
		}
	}

	std::unique_ptr<StatusService::Stub> Getcon() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this]() {
			if (_b_stop) {
				return true;
			}
			return !_con.empty();
			});

		if (_b_stop) {
			return nullptr;
		}

		auto context = std::move(_con.front());
		_con.pop();
		return context;
	}

	void returncon(std::unique_ptr<StatusService::Stub> con) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_b_stop) {
			return;
		}
		_con.push(std::move(con));
		_cond.notify_one();
	}

	void Close() {
		_b_stop = true;
		_cond.notify_all();
	}

private:
	bool _b_stop;
	std::mutex _mutex;
	std::queue<std::unique_ptr<StatusService::Stub>> _con;
	std::condition_variable _cond;
	int pool_size;
	std::string _host;
	std::string _port;

};

class StatusGrpcClient:public Singelton<StatusGrpcClient>
{
	friend class Singelton<StatusGrpcClient>;
public:
	~StatusGrpcClient() {

	}

	GetChatServerRsp GetChatServer(int uid);
	LoginRsp Login(int uid, std::string token);
private:
	StatusGrpcClient();
	std::unique_ptr<StatusPool> _pool;
};

