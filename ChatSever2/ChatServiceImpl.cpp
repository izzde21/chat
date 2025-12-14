#include "ChatServiceImpl.h"
#include "UserMgr.h"
#include "CSession.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "RedisMgr.h"
#include "MysqlMgr.h"
ChatServiceImpl::ChatServiceImpl() {

}
Status ChatServiceImpl::NotifyAddFriend(ServerContext* context, const AddFriendReq* request, AddFriendRsp* reply) {
	auto uid = request->touid();
	auto session = UserMgr::GetInstance()->GetSession(uid);

	Defer defer([this, &reply, request]() {
		reply->set_error(SUCCESS);
		reply->set_applyuid(request->applyuid());
		reply->set_touid(request->touid());
		});

	if (session==nullptr) {

		return Status::OK;
	}

		Json::Value  rtvalue;
		rtvalue["error"] = SUCCESS;
		rtvalue["applyuid"] = request->applyuid();
		rtvalue["name"] = request->name();
		rtvalue["desc"] = request->desc();
		rtvalue["icon"] = request->icon();
		rtvalue["sex"] = request->sex();
		rtvalue["nick"] = request->nick();
		std::cout << "icon is " << rtvalue["icon"].asString() << std::endl;
		std::string return_str = rtvalue.toStyledString();

		session->Send(return_str, ID_NOTIFY_ADD_FRIEND_REQ);

	return Status::OK;
}



Status ChatServiceImpl::NotifyAuthFriend(ServerContext* context, const AuthFriendReq* request, AuthFriendRsp* response) {
	Defer defer([request, &response]() {
		response->set_fromuid(request->fromuid());
		response->set_touid(request->touid());
		response->set_error(SUCCESS);
		});
	std::cout << "NotifyAuthFriend" << std::endl;
	auto touid = request->touid();
	auto fromuid = request->fromuid();
	auto session = UserMgr::GetInstance()->GetSession(touid);
	if (!session) {
		std::cout << "session is null" << std::endl;
		return Status::OK;
	}
	Json::Value rvalue;
	rvalue["touid"] = request->touid();
	rvalue["fromuid"] = request->fromuid();
	rvalue["error"] = SUCCESS;
	std::string base_key = USER_BASE_INFO + std::to_string(fromuid);
	auto userinfo = std::make_shared<UserInfo>();
	bool is = GetBaseInfo(base_key, fromuid, userinfo);
	if (is) {
		std::cout << "is no null" << std::endl;
		rvalue["name"] = userinfo->name;
		rvalue["nick"] = userinfo->nick;
		rvalue["sex"] = userinfo->sex;
		rvalue["icon"] = userinfo->icon;
		std::cout << "name is  " << rvalue["name"].asString() << std::endl;
	}
	else {
		rvalue["error"] = UidInvalid;
	}
	auto return_root = rvalue.toStyledString();
	session->Send(return_root, ID_NOTIFY_AUTH_FRIEND_REQ);
	return Status::OK;


}



Status ChatServiceImpl::NotifyTextChatMsg(::grpc::ServerContext* context, const TextChatMsgReq* request, TextChatMsgRsp* response) {
	auto touid = request->touid();
	auto session = UserMgr::GetInstance()->GetSession(touid);
	response->set_error(SUCCESS);
	if (!session) {
		return Status::OK;
	}
	Json::Value rvaule;
	rvaule["error"] = SUCCESS;
	rvaule["fromuid"] = request->fromuid();
	rvaule["touid"] = touid;
	Json::Value text_arr;

	for (auto& arr : request->textmsgs()) {
		Json::Value ele;
		ele["content"] = arr.msgcontent();
		ele["msgid"] = arr.msgid();
		text_arr.append(ele);
	}
	rvaule["text_array"] = text_arr;

	std::string retirnstr = rvaule.toStyledString();
	session->Send(retirnstr, ID_NOTIFY_TEXT_CHAT_MSG_REQ);

	return Status::OK;
}

bool ChatServiceImpl::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo) {
	std::cout << "base_key is" << base_key << std::endl;
	std::string value = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, value);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(value, root);
		userinfo->uid = root["uid"].asInt();
		userinfo->name = root["name"].asString();
		userinfo->pwd = root["pwd"].asString();
		userinfo->email = root["email"].asString();
		userinfo->nick = root["nick"].asString();
		userinfo->desc = root["desc"].asString();
		userinfo->sex = root["sex"].asInt();
		userinfo->icon = root["icon"].asString();
		std::cout << "emain : " << root["email"].asString() << std::endl;
	}
	else {
		std::shared_ptr<UserInfo> user_info = nullptr;
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr) {
			return false;
		}
		userinfo = user_info;

		//将数据库内容写入redis缓存
		Json::Value redis_root;
		redis_root["uid"] = uid;
		redis_root["pwd"] = userinfo->pwd;
		redis_root["name"] = userinfo->name;
		redis_root["email"] = userinfo->email;
		redis_root["nick"] = userinfo->nick;
		redis_root["desc"] = userinfo->desc;
		redis_root["sex"] = userinfo->sex;
		redis_root["icon"] = userinfo->icon;
		RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
		std::cout << "base_key is" << base_key << std::endl;
	}
	return true;
}