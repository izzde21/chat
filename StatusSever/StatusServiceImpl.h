#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include <mutex>

using grpc::ServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::Status;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

class ChatServer
{
public:
	ChatServer():name(""), host(""), port("") , count(0){}

	ChatServer(const ChatServer& cs) :name(cs.name),host(cs.host),port(cs.port), count(cs.count){}

	ChatServer& operator=(const ChatServer& cs) {
		if (&cs == this) {
			return *this;
		}
		name = cs.name;
		host = cs.host;
		port = cs.port;
		count = cs.count;
		return *this;
	}

	std::string name;
	std::string host;
	std::string port;
	int count;
};

class StatusServiceImpl final : public StatusService::Service
{
public:
	StatusServiceImpl();
	Status GetChatServer(ServerContext* con, const GetChatServerReq* request, GetChatServerRsp* reply)override;
	Status Login(ServerContext* con, const LoginReq* request,  LoginRsp* reply)override;

private:
	std::mutex _mutex;
	void insertoken(int uuid, std::string token);
	ChatServer Getcharserver();
	std::unordered_map<std::string, ChatServer> _servers;
};

