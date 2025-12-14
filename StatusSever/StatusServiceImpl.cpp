#include "StatusServiceImpl.h"
#include"ConfigMgr.h"
#include"const.h"
#include<string>
#include"RedisMgr.h"

std::string get_uudi() {
	boost::uuids::uuid uuid = boost::uuids::random_generator()();

	std::string unique_string = to_string(uuid);

	return unique_string;
}


StatusServiceImpl::StatusServiceImpl() {
	std::cout << "StatusServiceImpl构造函数"  << std::endl;
	auto& cfg = ConfigMgr::GetConfigMgr();
	auto server_list = cfg["chatservers"]["Name"];

	std::vector<std::string>words;
	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& work : words) {
		if (cfg[work]["Name"].empty()) {
			continue;
		}

		ChatServer charserve;
		charserve.name = cfg[work]["Name"];
		charserve.host= cfg[work]["Host"];
		charserve.port = cfg[work]["Port"];
		_servers[charserve.name] = charserve;
	}
}


Status StatusServiceImpl::GetChatServer(ServerContext* con, const GetChatServerReq* request, GetChatServerRsp* reply) {
	std::cout << "GetChatServer服务" << std::endl;
	const auto &server = Getcharserver();
	reply->set_host(server.host);
	reply->set_port(server.port);
	reply->set_token(get_uudi());
	reply->set_error(SUCCESS);
	insertoken(request->uid(), reply->token());
	return Status::OK;
}
Status StatusServiceImpl::Login(ServerContext* con, const LoginReq* request,  LoginRsp* reply) {
	auto uid = request->uid();
	auto token = request->token();
	
	std::string uid_str = std::to_string(uid);
	std::string token_key= USERTOKENPREFIX + uid_str;
	std::string token_value = "";

	auto success=RedisMgr::GetInstance()->Get(token_key, token_value);
	if (!success) {
		reply->set_error(UidInvalid);
		return Status::OK;
	}

	if (token_value != token) {
		reply->set_error(TokenInvalid);
		return Status::OK;
	}

	reply->set_token(token);
	reply->set_uid(uid);
	reply->set_error(SUCCESS);
	return Status::OK;
}
//找到计数次数最少的服务器
ChatServer StatusServiceImpl::Getcharserver() {
	std::lock_guard<std::mutex> guard(_mutex);
	auto min_server = _servers.begin()->second;
	auto count_str = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, min_server.name);
	if (count_str.empty()) {
		min_server.count = INT_MAX;
	}
	else {
		min_server.count= std::stoi(count_str);
	}
	
	for (auto& server : _servers) {
		if (server.second.name == min_server.name) {
			continue;
		}
		auto count_str = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server.second.name);
		if (count_str.empty()) {
			server.second.count = INT_MAX;
		}
		else {
			server.second.count = std::stoi(count_str);
		}

		if (server.second.count < min_server.count) {
			min_server = server.second;
		}
	}
	return min_server;

}



void StatusServiceImpl::insertoken(int uuid, std::string token) {
	std::string uid_str = std::to_string(uuid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(token_key, token);
}