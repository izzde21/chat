#include "VarifyGrpcClient.h"

VarifyGrpcClient::VarifyGrpcClient() {
	auto& conmgr = ConfigMgr::GetConfigMgr();
	std::string host = conmgr["VarifyServer"]["Host"];
	std::string port = conmgr["VarifyServer"]["Port"];
	std::cout << host << std::endl;
	std::cout << port << std::endl;
	pool_.reset(new RPConpool(5, host, port));
}

RPConpool::RPConpool(std::size_t size, std::string ip, std::string port) :_size(size), _ip(ip),
_port(port), _b_stop(false) {
	for (std::size_t si = 0; si < size; ++si) {
		std::string point = _ip + ":" + _port;
		std::shared_ptr<Channel> channel = grpc::CreateChannel(point, grpc::InsecureChannelCredentials());
		connections_.push(VarifyService::NewStub(channel));
	}
}

std::unique_ptr<VarifyService::Stub> RPConpool::Getstub() {
	std::unique_lock<std::mutex> lock(mutex_);
	cond_.wait(lock, [this]() {
		if (_b_stop) {
			return true;
		}
		return !connections_.empty();
		});
	if (_b_stop) {
		return nullptr;
	}
	auto conn = std::move(connections_.front());
	connections_.pop();
	return conn;
}



void RPConpool::BackStub(std::unique_ptr<VarifyService::Stub> content) {
	
	std::lock_guard<std::mutex> lock(mutex_);
	if (_b_stop) {
		return;
	}
	connections_.push(std::move(content));
	cond_.notify_one();
}


void RPConpool::Close() {
	_b_stop = true;
	cond_.notify_all();
}

RPConpool::~RPConpool() {
	std::lock_guard<std::mutex> lock(mutex_);
	Close();
	while (connections_.empty()) {
		connections_.pop();
	}
}