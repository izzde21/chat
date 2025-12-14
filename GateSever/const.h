#pragma once
#include<boost/asio.hpp>
#include<boost/beast.hpp>
#include<boost/beast/http.hpp>
#include<memory>
#include<iostream>
#include<map>
#include<functional>
#include<unordered_map>
#include<Json/json.h>
#include<Json/value.h>
#include<Json/Reader.h>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/ini_parser.hpp>
#include<boost/filesystem.hpp>
#include"ConfigMgr.h"
#include<queue>
#include<mutex>
#include<hiredis.h>
#include<atomic>
namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using tcp=boost::asio::ip::tcp;


enum ErrorCode {
	SUCCESS = 0,
	Error_json = 1001,
	RPCFailed = 1002,
	VarifyExpired = 1003, //验证码过期
	VarifyCodeErr = 1004, //验证码错误
	UserExist = 1005,       //用户已经存在
	PasswdErr = 1006,    //密码错误
	EmailNotMatch = 1007,  //邮箱不匹配
	PasswdUpFailed = 1008,  //更新密码失败
	PasswdInvalid = 1009,   //密码更新失败
	TokenInvalid = 1010,   //Token失效
	UidInvalid = 1011,  //uid无效
};


class Defer
{
public:
	Defer(std::function<void()> fun):_fun(fun){}
	
	
	~Defer(){
		_fun();
	}
private:
	std::function<void()> _fun;
};