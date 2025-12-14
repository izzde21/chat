#include "ChatGrpcClient.h"
ChatGrpcClient::ChatGrpcClient() {
	auto &cfg = ConfigMgr::GetConfigMgr();
	auto server_list = cfg["FeerServer"]["servers"];
	std::vector<std::string> words;
	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for(auto &a: words){
		if (cfg[word]["Name"].empty()) {
			continue;
		}
		_pools[cfg[word]["Name"]] = std::make_unique<ChatConPool>(5, cfg[word]["Host"], cfg[word]["Port"]);
	}
}

ChatGrpcClient::~ChatGrpcClient() {

}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req) {
	AddFriendRsp rsp;
	Defer defer([this, &rsp,req]() {
		rsp.set_applyuid(req.applyuid());
		rsp.set_error(SUCCESS);
		rsp.set_touid(req.touid());
		});

	auto itea = _pools.find(server_ip);
	if (itea == _pools.end()) {
		return rsp;
	}
	ClientContext context;
	auto &stub = itea->second;
	Status status = stub->Getcon()->NotifyAddFriend(&context, req, &rsp);
	if (status.ok()) {
		rsp.set_error(RPCFailed);
		return rsp;
	}
	return rsp;
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req) {
		AuthFriendRsp rsp;
		Defer defer([&rsp, &req]() {
			rsp.set_fromuid(req.fromuid());
			rsp.set_touid(req.touid());
			});

		auto itea = _pools.find(server_ip);
		if (itea == _pools.end()) {
			return rsp;
		}



		auto &pool = itea->second;
		ClientContext context;
		auto stub = pool->Getcon();
		Defer defer2([&pool,&stub]() {
			pool->Returncon(std::move(stub));
			});

		Status status = stub->NotifyAuthFriend(&context, req, &rsp);

		if (!status.ok()) {
			rsp.set_error(RPCFailed);
			return rsp;
		}

		return rsp;
}

bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo) {
	return true;
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue) {
	TextChatMsgRsp rsp;
	rsp.set_error(SUCCESS);

	Defer defer([&rsp, &req]() {
		rsp.set_fromuid(req.fromuid());
		rsp.set_touid(req.touid());
		for (const auto& text_data : req.textmsgs()) {
			TextChatData* new_msg = rsp.add_textmsgs();
			new_msg->set_msgid(text_data.msgid());
			new_msg->set_msgcontent(text_data.msgcontent());
		}

		});

	auto find_iter = _pools.find(server_ip);
	if (find_iter == _pools.end()) {
		return rsp;
	}

	auto& pool = find_iter->second;
	ClientContext context;
	auto stub = pool->Getcon();
	Status status = stub->NotifyTextChatMsg(&context, req, &rsp);
	Defer defercon([&stub, this, &pool]() {
		pool->Returncon(std::move(stub));
		});

	if (!status.ok()) {
		rsp.set_error(RPCFailed);
		return rsp;
	}

	return rsp;
}