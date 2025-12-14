#pragma once
#include"const.h"
#include"Singelton.h"
class HttpConnect;
typedef std::function<void(std::shared_ptr<HttpConnect>)>HttpHandler;
class LogicSystem :public Singelton<LogicSystem>
{
	friend class Singelton<LogicSystem>;
public:
	void RegGet(std::string url, HttpHandler handle);				//注册get请求
	bool HandleGet(std::string path, std::shared_ptr<HttpConnect>);	//处理get请求

	void RegPost(std::string url, HttpHandler handle);				//注册post请求
	bool HandlePost(std::string path, std::shared_ptr<HttpConnect>);	//处理post请求
	~LogicSystem();
private:
	LogicSystem();
	std::map<std::string, HttpHandler> _get_handle;		//存放get的请求
	std::map<std::string, HttpHandler> _post_handle;	//存放post的请求
};

