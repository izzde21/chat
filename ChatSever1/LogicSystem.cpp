#include"LogicSystem.h"
#include"data.h"
#include"const.h"
#include"UserMgr.h"
#include <grpcpp/grpcpp.h> 
#include "message.grpc.pb.h"
#include "message.pb.h"
#include "ChatGrpcClient.h"
LogicSystem::LogicSystem():_b_stop(false)
{
	RegisterCallBacks();
	_thread = std::thread(&LogicSystem::DealMsg, this);
}

LogicSystem::~LogicSystem() {
	_b_stop = true;
	_cond.notify_one();
	_thread.join();
}
bool LogicSystem::Checkintorstring(std::string uid) {
	for (char a : uid) {
		if (!std::isdigit(a)) {
			return false;
		}
	}
	return true;
}

void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg) {
	std::unique_lock<std::mutex> lock(_mutex);
	_msg_que.push(msg);
	if (_msg_que.size() == 1) {
		lock.unlock();
		_cond.notify_one();
	}
}
bool LogicSystem::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo) {
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

void LogicSystem::LoginHander(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data) {
	Json::Reader reader;
	Json::Value root;
	Json::Value root_str;
	reader.parse(msg_data, root_str);

	auto uid = root_str["uid"].asInt();
	auto token = root_str["token"].asString();
	std::string token_value="";
	std::cout << "uid is " << uid << std::endl;
	std::cout << "token is " << token << std::endl;
	Defer defer([&]() {
		std::string return_str = root.toStyledString();
		csess->Send(return_str, MSG_CHAT_LOGIN_RSP);
		});

	auto success = RedisMgr::GetInstance()->Get(USERTOKENPREFIX +std::to_string(uid), token_value);
	if (!success) {
		root["error"] = UidInvalid;
		return;
	}

	if (token != token_value) {
		root["error"] = TokenInvalid;
		return;
	}
	root["error"] = SUCCESS;
	std::string base_key = USER_BASE_INFO + std::to_string(uid);
	auto user_info = std::make_shared<UserInfo>();
	bool b_base = GetBaseInfo(base_key, uid, user_info);
	if (!b_base) {
		root["error"] = UidInvalid;
		return;
	}

	root["uid"] = uid;
	root["pwd"] = user_info->pwd;
	root["name"] = user_info->name;
	root["email"] = user_info->email;
	root["nick"] = user_info->nick;
	root["desc"] = user_info->desc;
	root["sex"] = user_info->sex;
	root["icon"] = user_info->icon;
	
	std::vector<std::shared_ptr<ApplyInfo>> apply_list;
	auto b_apply = GetFriendApplyInfo(uid, apply_list);
	if (b_apply) {

		for (auto& app : apply_list) {
			Json::Value obj;
			obj["name"]= app->_name;
			obj["sex"] = app->_sex;
			obj["nick"] = app->_nick;
			obj["uid"] = app->_uid;
			obj["status"] = app->_status;
			obj["icon"] = app->_icon;
			obj["desc"] = app->_desc;
			root["apply_list"].append(obj);
		}
			
	}
	std::vector<std::shared_ptr<UserInfo>> friend_list;
	auto b_friend = GetFriendList(uid, friend_list);
	if (b_friend) {

		for (auto& app : friend_list) {
			Json::Value obj;
			obj["name"] = app->name;
			obj["sex"] = app->sex;
			obj["nick"] = app->nick;
			obj["uid"] = app->uid;
			obj["back"] = app->back;
			obj["icon"] = app->icon;
			obj["desc"] = app->desc;
			root["friend_list"].append(obj);
		}

	}


	auto& con = ConfigMgr::GetConfigMgr();
	auto server = con["SelfServer"]["Name"];

	auto res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server);
	int count = 0;
	if (!res.empty()) {
		count = std::stoi(res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server, count_str);
	//绑定到session
	csess->SetUserid(uid);
	std::string  ipkey = USERIPPREFIX + std::to_string(uid);
	RedisMgr::GetInstance()->Set(ipkey, server);

	//uid和session绑定管理,方便以后踢人操作
	UserMgr::GetInstance()->SetUserSession(uid, csess);

	return;
}
bool LogicSystem::GetFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list) {
	return MysqlMgr::GetInstance()->GetFriendList(uid, list);
}
bool LogicSystem::GetFriendApplyInfo(int uid,std::vector<std::shared_ptr<ApplyInfo>> &list) {
	return MysqlMgr::GetInstance()->GetApplyList(uid, list, 0, 10);
}

void LogicSystem::SearchInfo(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data) {
	Json::Reader reader;
	Json::Value root;
	Json::Value root_str;
	std::cout << ID_SEARCH_USER_RSP << std::endl;
	Defer deder([this, &root_str, csess]() {
		std::string return_str = root_str.toStyledString();
		csess->Send(return_str, ID_SEARCH_USER_RSP);
		});
	auto success=reader.parse(msg_data, root);
	auto uid = root["uid"].asString();
	bool isdigit=Checkintorstring(uid);
	if (isdigit) {
		GetUserByUid(uid, root_str);
	}
	else {
		GetUserByName(uid, root_str);
	}
}

void LogicSystem::AddFriendApply(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data) {
	Json::Reader reader;
	Json::Value root;
	Json::Value rvalue;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto touid = root["touid"].asInt();
	auto applyname = root["applyname"].asString();
	auto bakname = root["bakname"].asString();

	std::cout << "user login uid is  " << uid << "   applyname  is "
		<< applyname << "   bakname is " << bakname << "    touid is " << touid << std::endl;
	rvalue["error"] = SUCCESS;
	Defer defer([csess, &rvalue]() {
		auto rvalueq = rvalue.toStyledString();
		csess->Send(rvalueq, ID_ADD_FRIEND_RSP);
		});
	bool success = MysqlMgr::GetInstance()->AddFriendReply(uid, touid);
	if (!success) {
		rvalue["error"] = UidInvalid;
		return;
	}

	auto sever_key = USERIPPREFIX + std::to_string(touid);
	std::string sever_key_value = "";
	bool isex = RedisMgr::GetInstance()->Get(sever_key, sever_key_value);
	if (!isex) {
		return;
	}

	auto& cfg = ConfigMgr::GetConfigMgr();
	auto selfsever = cfg["SelfServer"]["Name"];
	if (sever_key_value == selfsever) {

		auto sess = UserMgr::GetInstance()->GetSession(touid);
		if (sess) {
			Json::Value  notify;
			rvalue["error"] = SUCCESS;
			rvalue["applyuid"] = uid;
			rvalue["name"] = applyname;
			rvalue["desc"] = "";
			std::string str = rvalue.toStyledString();
			sess->Send(str, ID_NOTIFY_ADD_FRIEND_REQ);
		}
		return;

	}

	auto key = USER_BASE_INFO + std::to_string(uid);
	auto apply_info = std::make_shared<UserInfo>();
	bool b_info = GetBaseInfo(key, uid, apply_info);

	AddFriendReq req;
	req.set_name(applyname);
	req.set_touid(touid);
	req.set_applyuid(uid);
	req.set_desc("");
	if (b_info) {
		req.set_icon(apply_info->icon);
		req.set_nick(apply_info->nick);
		req.set_sex(apply_info->sex);
	}
	ChatGrpcClient::GetInstance()->NotifyAddFriend(sever_key_value, req);
}

void LogicSystem::AuthFriendApply(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data) {
	Json::Reader reader;
	Json::Value root;
	Json::Value rvalue;
	std::cout << "AuthFriendApply" << std::endl;
	reader.parse(msg_data, root);
	auto touid = root["touid"].asInt();
	auto fromuid = root["uid"].asInt();
	auto applyname = root["applyname"].asString();
	auto bakname = root["bakname"].asString();

	Defer defer([csess,&rvalue,this]() {
		std::string root_str = rvalue.toStyledString();
		csess->Send(root_str, ID_AUTH_FRIEND_RSP);
		});
	rvalue["error"] = SUCCESS;
	auto base_key = USER_BASE_INFO + std::to_string(touid);
	auto userinfo = std::make_shared<UserInfo>();
	bool isex = GetBaseInfo(base_key, touid, userinfo);
	if (isex) {
		rvalue["name"] = userinfo->name;
		rvalue["uid"] = userinfo->uid;
		rvalue["icon"] = userinfo->icon;
		rvalue["nick"] = userinfo->nick;
		rvalue["sex"] = userinfo->sex;
		std::cout << "uid is" << rvalue["uid"].asInt() << std::endl;
	}
	else {
		rvalue["error"] = UidInvalid;
	}

	MysqlMgr::GetInstance()->AuthFriendApply(fromuid, touid);

	//更新数据库添加好友
	MysqlMgr::GetInstance()->AddFriend(fromuid, touid, bakname);

	std::string sever = "";
	std::string sever_key = USERIPPREFIX + std::to_string(touid);
	bool success = RedisMgr::GetInstance()->Get(sever_key, sever);
	if (!success) {
		return;
	}

	auto& cfg = ConfigMgr::GetConfigMgr();
	std::string self_sever = cfg["SelfServer"]["Name"];
	if (self_sever == sever) {
		auto sess = UserMgr::GetInstance()->GetSession(touid);
		if (sess) {
			Json::Value notify;
			notify["error"] = SUCCESS;
			notify["fromuid"] = fromuid;
			notify["touid"] = touid;

			auto base_key = USER_BASE_INFO + std::to_string(fromuid);
			auto user_info = std::make_shared<UserInfo>();
			bool isex = GetBaseInfo(base_key, fromuid, user_info);
			if (isex) {
				notify["name"] = userinfo->name;
				notify["nick"] = userinfo->nick;
				notify["icon"] = userinfo->icon;
				notify["sex"] = userinfo->sex;
			}
			else {
				notify["error"] = UidInvalid;
			}
			std::string return_str = notify.toStyledString();
			sess->Send(return_str, ID_NOTIFY_AUTH_FRIEND_REQ);
		}
		return;
	}
	AuthFriendReq req;
	req.set_fromuid(fromuid);
	std::cout << req.fromuid() << std::endl;
	req.set_touid(touid);

	ChatGrpcClient::GetInstance()->NotifyAuthFriend(sever, req);
	
	
}

void LogicSystem::DealChatTextMsg(std::shared_ptr<CSession> csess, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	Json::Value rvalue;
	Json::Value array;
	reader.parse(msg_data, root);
	auto fromuid = root["fromuid"].asInt();
	auto touid= root["touid"].asInt();
	array = root["text_array"];

	rvalue["error"] = SUCCESS;
	rvalue["fromuid"] = fromuid;
	rvalue["text_array"] = array;
	rvalue["touid"] = touid;

	Defer defer([this, csess, rvalue]() {
		std::string rstr = rvalue.toStyledString();
		csess->Send(rstr, ID_TEXT_CHAT_MSG_RSP);
		});

	auto sever_key = USERIPPREFIX + std::to_string(touid);
	std::string value = "";
	bool isex= RedisMgr::GetInstance()->Get(sever_key, value);
	if (!isex) {
		rvalue["error"] = UidInvalid;
		return;
	}

	auto& cfg = ConfigMgr::GetConfigMgr();
	auto self_sever = cfg["SelfServer"]["Name"];
	if (self_sever == value) {
		auto session = UserMgr::GetInstance()->GetSession(touid);
		if (session) {
			std::string return_str = rvalue.toStyledString();
			session->Send(return_str, ID_NOTIFY_TEXT_CHAT_MSG_REQ);
		}

		return;
	}
	TextChatMsgReq text_msg;
	text_msg.set_fromuid(fromuid);
	text_msg.set_touid(touid);
	for (const auto& arr : array) {
		auto content = arr["content"].asString();
		auto msgid = arr["msgid"].asString();
		std::cout << "content is " << content << std::endl;
		std::cout << "msgid is " << msgid << std::endl;
		auto* textmsgs = text_msg.add_textmsgs();
		textmsgs->set_msgcontent(content);
		textmsgs->set_msgid(msgid);
	}
	ChatGrpcClient::GetInstance()->NotifyTextChatMsg(value, text_msg, rvalue);
}


void LogicSystem::GetUserByUid(std::string uid, Json::Value& root) {
	root["error"] = SUCCESS;
	std::string value = "";
	Json::Reader reader;
	Json::Value root_str;

	auto issuccess=RedisMgr::GetInstance()->Get(USER_BASE_INFO + uid, value);
	if (issuccess) {

		reader.parse(value, root_str);
		root["name"] = root_str["name"].asString();
		root["uid"] = root_str["uid"].asInt();
		root["emile"] = root_str["emile"].asString();
		root["pwd"] = root_str["pwd"].asString();
		root["nick"] = root_str["nick"].asString();
		root["desc"] = root_str["desc"].asString();
		root["sex"] = root_str["sex"].asInt();
		root["icon"] = root_str["iocn"].asString();
		return;
	}

	auto info = std::shared_ptr<UserInfo>();
	info=MysqlMgr::GetInstance()->GetUser(std::stoi(uid));
	if (info == nullptr) {
		root["error"] = UidInvalid;
		return;
	}
	Json::Value infovalue;
	infovalue["name"] = info->name;
	infovalue["uid"] = info->uid;
	infovalue["emile"] = info->email;
	infovalue["pwd"] = info->pwd;
	infovalue["nick"] = info->nick;
	infovalue["desc"] = info->desc;
	infovalue["sex"] = info->sex;
	infovalue["icon"] = info->icon;

	RedisMgr::GetInstance()->Set(USER_BASE_INFO + uid, infovalue.toStyledString());

	root["name"] = info->name;
	root["uid"] = info->uid;
	root["emile"] = info->email;
	root["pwd"] = info->pwd;
	root["nick"] = info->nick;
	root["desc"] = info->desc;
	root["sex"] = info->sex;
	root["icon"] = info->icon;
	return;
}

void LogicSystem::GetUserByName(std::string uid, Json::Value& root) {
	root["error"] = SUCCESS;
	std::string value = "";
	Json::Reader reader;
	Json::Value root_str;

	auto issuccess = RedisMgr::GetInstance()->Get(NAME_INFO + uid, value);
	if (issuccess) {

		reader.parse(value, root_str);
		root["name"] = root_str["name"].asString();
		root["uid"] = root_str["uid"].asInt();
		root["emile"] = root_str["emile"].asString();
		root["pwd"] = root_str["pwd"].asString();
		root["nick"] = root_str["nick"].asString();
		root["desc"] = root_str["desc"].asString();
		root["sex"] = root_str["sex"].asInt();
		root["icon"] = root_str["iocn"].asString();
		return;
	}

	auto info = std::shared_ptr<UserInfo>();
	info = MysqlMgr::GetInstance()->GetUser(uid);
	if (info == nullptr) {
		root["error"] = UidInvalid;
		return;
	}
	Json::Value infovalue;
	infovalue["name"] = info->name;
	infovalue["uid"] = info->uid;
	infovalue["emile"] = info->email;
	infovalue["pwd"] = info->pwd;
	infovalue["nick"] = info->nick;
	infovalue["desc"] = info->desc;
	infovalue["sex"] = info->sex;
	infovalue["icon"] = info->icon;

	RedisMgr::GetInstance()->Set(NAME_INFO + uid, infovalue.toStyledString());

	root["name"] = info->name;
	root["uid"] = info->uid;
	root["emile"] = info->email;
	root["pwd"] = info->pwd;
	root["nick"] = info->nick;
	root["desc"] = info->desc;
	root["sex"] = info->sex;
	root["icon"] = info->icon;
	return;
}
void LogicSystem::RegisterCallBacks() {
	_funcallback[MSG_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHander, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	_funcallback[ID_SEARCH_USER_REQ] = std::bind(&LogicSystem::SearchInfo, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	_funcallback[ID_ADD_FRIEND_REQ] = std::bind(&LogicSystem::AddFriendApply, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	_funcallback[ID_AUTH_FRIEND_REQ] = std::bind(&LogicSystem::AuthFriendApply, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	_funcallback[ID_TEXT_CHAT_MSG_REQ] = std::bind(&LogicSystem::DealChatTextMsg, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void LogicSystem::DealMsg() {
	for (;;) {
		std::unique_lock<std::mutex> lock(_mutex);
 		if (_msg_que.empty() && !_b_stop) {
			_cond.wait(lock);
		}

		if (_b_stop) {
			while (!_msg_que.empty()) {
				auto msg_node = _msg_que.front();
				std::cout << "recv_msg id  is " << msg_node->_RecvNode->msg_id << std::endl;
				auto funcall = _funcallback.find(msg_node->_RecvNode->msg_id);
				if (funcall == _funcallback.end()) {
					_msg_que.pop();
					continue;
				}

				funcall->second(msg_node->_CSession, msg_node->_RecvNode->msg_id,
					std::string(msg_node->_RecvNode->_data, msg_node->_RecvNode->cur_len));
				_msg_que.pop();
			}
			break;
		}
		auto msg_node = _msg_que.front();
		std::cout << "recv_msg id  is " << msg_node->_RecvNode->msg_id << std::endl;
		auto funcall = _funcallback.find(msg_node->_RecvNode->msg_id);
		if (funcall == _funcallback.end()) {
			_msg_que.pop();
			continue;
		}

		funcall->second(msg_node->_CSession, msg_node->_RecvNode->msg_id,
			std::string(msg_node->_RecvNode->_data, msg_node->_RecvNode->cur_len));
		_msg_que.pop();
	}
}