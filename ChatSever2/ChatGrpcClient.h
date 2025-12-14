#pragma once

#include "const.h"
#include "Singelton.h"
#include <grpcpp/grpcpp.h> 
#include "message.grpc.pb.h"
#include "message.pb.h"
#include"ConfigMgr.h"
#include<unordered_map>
#include "MySqlPool.h"
using grpc::Status;
using grpc::Channel;
using grpc::ClientContext;
using message::AddFriendReq;
using message::AddFriendRsp;

using message::AuthFriendRsp;
using message::AuthFriendReq;

using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::ChatService;
using message::TextChatMsgReq;
using message::TextChatData;
using message::TextChatMsgRsp;


class ChatConPool
{
public:
	ChatConPool(std::size_t poolsize, std::string host, std::string port):
		poolsize_(poolsize), host_(host), port_(port), b_stop_(false)
	{
		for (int i = 0; i < poolsize_; i++) {
			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
			connect_.push(ChatService::NewStub(channel));
		}
	}

	~ChatConPool() {
		std::lock_guard<std::mutex> lock(mutex_);
		Close();
		while (connect_.empty()) {
			connect_.pop();
		}
	}
	void Close() {
		b_stop_ = true;
		cond_.notify_all();
	}

	std::unique_ptr<ChatService::Stub> Getcon() {
		std::unique_lock<std::mutex> lock(mutex_);
		cond_.wait(lock, [this]() {
			if (b_stop_) {
				return true;
			}
			return !connect_.empty();
			});

		if (b_stop_) {
			return nullptr;
		}
		auto context = std::move(connect_.front());
		connect_.pop();
		return context;
	}

	void Returncon(std::unique_ptr<ChatService::Stub> stub) {
		std::unique_lock<std::mutex> lock(mutex_);
		if (b_stop_) {
			return;
		}
		connect_.push(std::move(stub));
		cond_.notify_one();
	}

private:
	std::size_t poolsize_;
	std::string host_;
	std::string port_;
	std::mutex mutex_;
	std::condition_variable cond_;
	std::queue<std::unique_ptr<ChatService::Stub>> connect_;
	std::atomic<bool> b_stop_;
};

class ChatGrpcClient:public Singelton<ChatGrpcClient>
{
	friend class Singelton<ChatGrpcClient>;
public:
	~ChatGrpcClient();
	AddFriendRsp NotifyAddFriend(std::string server_ip, const AddFriendReq& req);
	AuthFriendRsp NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req);
	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);
	TextChatMsgRsp NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue);
private:
	ChatGrpcClient();
	std::unordered_map<std::string, std::unique_ptr<ChatConPool>> _pools;
};

