#include "LogicSystem.h"
#include"HttpConnect.h"
#include"VarifyGrpcClient.h"
#include"RedisMgr.h"
#include"MysqlMgr.h"
#include"StatusGrpcClient.h"
LogicSystem::LogicSystem() {
	RegGet("/get_text", [](std::shared_ptr<HttpConnect> conn) {
		beast::ostream(conn->_response.body()) << "receive get_text" << std::endl;
		int i = 0;
		for (auto& elem : conn->_get_params) {
			i++;
			beast::ostream(conn->_response.body()) << "param" << i << " key is " << elem.first;
			beast::ostream(conn->_response.body()) << ", " << " value is " << elem.second << std::endl;
		}
		});

	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnect> conn) {
		auto body_str = boost::beast::buffers_to_string(conn->_request.body().data());
		std::cout << "receivr body is "<<body_str <<std::endl;
		conn->_response.set(http::field::content_type, "text/json");
		Json::Value root; 
		Json::Reader reader;
		Json::Value root_scr;
		bool success_parse = reader.parse(body_str, root_scr);
		if (!success_parse) 
		{
			std::cout << "Failde parse data" << std::endl;
			root["error"] = Error_json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(conn->_response.body()) << jsonstr;
			return true;
		}
		auto email = root_scr["email"].asString();
		GetVarifyRsp req = VarifyGrpcClient::GetInstance()->GetVarifyCode(email);
		std::cout << "success parse data" << std::endl;
		std::cout << "email is " << email << std::endl;
		root["error"] = SUCCESS;
		root["email"] = root_scr["email"];
		std::string jsonstr = root.toStyledString();
		beast::ostream(conn->_response.body()) << jsonstr;
		return true;
			});

	RegPost("/user_register", [](std::shared_ptr<HttpConnect> conn) {
		auto body_str = boost::beast::buffers_to_string(conn->_request.body().data());
		std::cout << "body_str is " << body_str << std::endl;
		conn->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value root_str;
		bool success=reader.parse(body_str, root_str);

		auto name = root_str["user"].asCString();
		auto email = root_str["email"].asCString();
		auto pwd = root_str["pass"].asCString();
		if (!success) {
			std::cout << "Json解析失败 "  << std::endl;
			root["error"] = Error_json;
			std::string str = root.toStyledString();
			beast::ostream(conn->_response.body())<<str;
			return true;
		}
		std::string value;
		bool check = RedisMgr::GetInstance()->Get("code_" + root_str["email"].asString(), value);
		if (!check) {
			std::cout << "检查错误" << std::endl;
			root["error"] = ErrorCode::VarifyExpired;
			std::string str = root.toStyledString();
			beast::ostream(conn->_response.body()) << str;
			return true;
		}

		if (value != root_str["varifycode"].asString()) {
			std::cout << "验证码错误" << std::endl;
			root["error"] = ErrorCode::VarifyExpired;
			std::string str = root.toStyledString();
			beast::ostream(conn->_response.body())<<str;
			return true;
		}
		int uid = MysqlMgr::GetInstance()->RegUser(name, email, pwd);
		if (uid == 0 || uid == -1) {
       	std::cout << " user or email exist" << std::endl;
		root["error"] = ErrorCode::UserExist;
		std::string jsonstr = root.toStyledString();
		beast::ostream(conn->_response.body()) << jsonstr;
		return true;
	}

		 
		root["error"] = 0;
		root["user"] = root_str["user"].asString();
		root["email"] = root_str["email"].asString();
		root["pass"] = root_str["pass"].asString();
		root["confrim"] = root_str["confrim"].asString();
		root["varifycode"] = root_str["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(conn->_response.body()) << jsonstr;
	});

	RegPost("/reset_pwd", [](std::shared_ptr<HttpConnect> conn) {
		auto str = beast::buffers_to_string(conn->_request.body().data());
		conn->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value root_str;
		auto success = reader.parse(str, root_str);
		if (!success) {
			std::cout << "解析失败" << std::endl;
			root["error"] = ErrorCode::Error_json;
			std::string str = root.toStyledString();
			beast::ostream(conn->_response.body()) << str;
			return true;
		}

		auto name = root_str["user"].asString();
		auto passwd = root_str["passwd"].asString();
		auto email = root_str["email"].asString();

		std::string value;
		auto vaify = RedisMgr::GetInstance()->Get("code_"+root_str["email"].asString(), value);
		std::cout << "Get is " << value << std::endl;
			if (!vaify) {
				std::cout << "验证码过期" << std::endl;
				root["error"] = ErrorCode::VarifyExpired;
				std::string str = root.toStyledString();
				beast::ostream(conn->_response.body()) << str;
				return true;
			}

			if (value != root_str["varifycode"].asString()) {
				std::cout << "验证码错误" << std::endl;
				root["error"] = ErrorCode::VarifyCodeErr;
				std::string str = root.toStyledString();
				beast::ostream(conn->_response.body()) << str;
				return true;
			}

			auto checkemail = MysqlMgr::GetInstance()->CheckEmail(name,email);
			if (!checkemail) {
				std::cout << "邮箱不匹配" << std::endl;
				root["error"] = ErrorCode::EmailNotMatch;
				std::string str = root.toStyledString();
				beast::ostream(conn->_response.body()) << str;
				return true;
			}

			auto updateemail = MysqlMgr::GetInstance()->UpdateEmail(email,passwd);
			if (!checkemail) {
				std::cout << "更改密码失败" << std::endl;
				root["error"] = ErrorCode::PasswdUpFailed;
				std::string str = root.toStyledString();
				beast::ostream(conn->_response.body()) << str;
				return true;
			}


			root["error"] = 0;
			root["user"] = root_str["user"].asString();
			root["email"] = root_str["email"].asString();
			root["passwd"] = root_str["passwd"].asString();
			root["user"] = root_str["user"].asString();
			std::string str_t = root.toStyledString();
			beast::ostream(conn->_response.body()) << str_t;
			return true;
		});

	RegPost("/user_login", [](std::shared_ptr<HttpConnect> conn) {
		auto str = boost::beast::buffers_to_string(conn->_request.body().data());
		Json::Value root;
		Json::Reader reader;
		Json::Value root_str;

		auto success = reader.parse(str, root_str);
		if (!success) {
			std::cout << "json解析错误" << std::endl;
			root["error"] = Error_json;
			auto str = root.toStyledString();
			beast::ostream(conn->_response.body()) << str;
			return;
		}
		//检查密码
		auto email = root_str["email"].asString();
		auto passwd = root_str["pass"].asString();
		std::cout << "passwd is" << passwd<< std::endl;
		UserInfo userInfo;
		auto pass_check=MysqlMgr::GetInstance()->CheckPass(email, passwd, userInfo);
		if (!pass_check) {
			std::cout << "密码错误" << std::endl;
			root["error"] = PasswdErr;
			auto str = root.toStyledString();
			beast::ostream(conn->_response.body()) << str;
			return;
		}
		//找可用的聊天服务器
		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(userInfo.uid);
		if (reply.error()) {
			std::cout << " grpc get chat server failed, error is " << reply.error() << std::endl;
			root["error"] = RPCFailed;
			auto str = root.toStyledString();
			beast::ostream(conn->_response.body()) << str;
			return;
		}

		root["error"] = SUCCESS;
		root["email"] = email;
		root["host"] = reply.host();
		root["port"] = reply.port();
		root["token"] = reply.token();
		root["uid"] = userInfo.uid;
		std::string str_1 = root.toStyledString();
		beast::ostream(conn->_response.body()) << str_1;
		return;
	});
}


void LogicSystem::RegPost(std::string url, HttpHandler handle) {
	_post_handle.insert(make_pair(url, handle));	//注册url和对应的函数
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnect>connect) {
	if (_post_handle.find(path) == _post_handle.end()) {
		return false;
	}
	_post_handle[path](connect);					//调用path对应的函数，参数为connect
	return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handle) {
	_get_handle.insert(make_pair(url ,handle));	//注册url和对应的函数
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnect> connect) {
	if (_get_handle.find(path) == _get_handle.end()) {
		return false;
	 }
	_get_handle[path](connect);					//调用path对应的函数，参数为connect
	return true;
}


LogicSystem::~LogicSystem() {

}