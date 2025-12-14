#include "RedisMgr.h"
#include"ConfigMgr.h"

bool RedisMgr::Get(const std::string& key, std::string& value) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "GET %s", key.c_str());
	if (_reply == NULL) {
		std::cout << "Get[" << key << "]" << "failed" << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}


	if (_reply->type != REDIS_REPLY_STRING) {
		std::cout << "Get[" << key << "]" << "failed" << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return 	false;
	}
	std::cout << "Get[" << key << "]" << "success" << std::endl;
	value = _reply->str;
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	return 	true;
}
bool RedisMgr::Set(const std::string& key, const std::string& value) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "SET %s %s", key.c_str(), value.c_str());
	//如果返回NULL则说明执行失败
	if (NULL == _reply)
	{
		std::cout << "Execut command [ SET " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	//如果执行失败则释放连接
	if (!(_reply->type == REDIS_REPLY_STATUS && (strcmp(_reply->str, "OK") == 0 || strcmp(_reply->str, "ok") == 0)))
	{
		std::cout << "Execut command [ SET " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	//执行成功 释放redisCommand执行后返回的redisReply所占用的内存
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	std::cout << "Execut command [ SET " << key << "  " << value << " ] success ! " << std::endl;
	return true;
}


bool RedisMgr::Auth(const std::string& password) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "AUTH %s", password.c_str());
	if (_reply->type == REDIS_REPLY_ERROR) {
		std::cout << "认证失败" << std::endl;
		//执行成功 释放redisCommand执行后返回的redisReply所占用的内存
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	else {
		//执行成功 释放redisCommand执行后返回的redisReply所占用的内存
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		std::cout << "认证成功" << std::endl;
		return true;
	}
}


bool RedisMgr::LPush(const std::string& key, const std::string& value) {
		auto context = con_pool->Getconnect();
		auto _reply = (redisReply*)redisCommand(context, "LPUSH %s %s", key.c_str(), value.c_str());
		if (NULL == _reply)
		{
			std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
			freeReplyObject(_reply);
			con_pool->returnredisContext(context);
			return false;
		}
		if (_reply->type != REDIS_REPLY_INTEGER || _reply->integer <= 0) {
			std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
			freeReplyObject(_reply);
			con_pool->returnredisContext(context);
			return false;
		}
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return true;
}



bool RedisMgr::LPop(const std::string& key, std::string& value) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "LPOP %s ", key.c_str());
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	value = _reply->str;
	std::cout << "Execut command [ LPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	return true;

}


bool RedisMgr::RPush(const std::string& key, const std::string& value) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "RPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == _reply)
	{
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	if (_reply->type != REDIS_REPLY_INTEGER || _reply->integer <= 0) {
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	return true;

}


bool RedisMgr::RPop(const std::string& key, std::string& value) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "RPOP %s ", key.c_str());
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	value = _reply->str;
	std::cout << "Execut command [ RPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	return true;
}


bool RedisMgr::HSet(const std::string& key, const std::string& hkey, const std::string& value) {
	auto context = con_pool->Getconnect();
	auto _reply = (redisReply*)redisCommand(context, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	return true;
}


bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen) {
	auto context = con_pool->Getconnect();
	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;
	auto _reply = (redisReply*)redisCommandArgv(context, 4, argv, argvlen);
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	con_pool->returnredisContext(context);
	return true;
}



std::string RedisMgr::HGet(const std::string& key, const std::string& hkey) {

	auto context = con_pool->Getconnect();
		const char* argv[3];
		size_t argvlen[3];
		argv[0] = "HGET";
		argvlen[0] = 4;
		argv[1] = key.c_str();
		argvlen[1] = key.length();
		argv[2] = hkey.c_str();
		argvlen[2] = hkey.length();
		auto _reply = (redisReply*)redisCommandArgv(context, 3, argv, argvlen);
		if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
			freeReplyObject(_reply);
			con_pool->returnredisContext(context);
			std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
			return "";
		}
		std::string value = _reply->str;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		std::cout << "Execut command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
		return value;
	
}


bool RedisMgr::Del(const std::string& key) {
	auto context = con_pool->Getconnect();
		auto _reply = (redisReply*)redisCommand(context, "DEL %s", key.c_str());
		if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
			std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
			freeReplyObject(_reply);
			con_pool->returnredisContext(context);
			return false;
		}
		std::cout << "Execut command [ Del " << key << " ] success ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return true;
	
}


bool RedisMgr::ExistsKey(const std::string& key) {
		auto context = con_pool->Getconnect();
		auto _reply = (redisReply*)redisCommand(context, "exists %s", key.c_str());
		if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER || _reply->integer == 0) {
			std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
			freeReplyObject(_reply);
			con_pool->returnredisContext(context);
			return false;
		}
		std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
		freeReplyObject(_reply);
		con_pool->returnredisContext(context);
		return true;
	
}


void RedisMgr::Close() {
	con_pool->Close();
}

RedisMgr::RedisMgr() {
	auto&  config = ConfigMgr::GetConfigMgr(); 
	std::string host = config["redis"]["Host"];
	std::string port = config["redis"]["Port"];
	std::string pass = config["redis"]["Pass"];
	std::cout << host << std::endl;
	std::cout << port << std::endl;
	std::cout << pass << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	con_pool.reset(new RedisConPool(5, host.c_str(), atoi(port.c_str()), pass.c_str()));
}

RedisMgr::~RedisMgr() {
	
	Close();
}


RedisConPool::RedisConPool(std::size_t poolsize, const char* host,  int port, const char* pass) :
host_(host),_port(port),_pass(pass),_poolsize(poolsize), b_stop_(false)
{
	for (std::size_t size = 0; size < _poolsize; ++size) {
		auto* context = redisConnect(host, port);
		if (context == nullptr || context->err != 0) {
			if (context != nullptr) {
				std::cerr << "Redis connection error: " << context->errstr << std::endl;
				redisFree(context);
			}
			continue;
		}
		auto reply = (redisReply*)redisCommand(context, "AUTH %s", pass);
		std::cout << "reply2" << std::endl;
		if (reply->type == REDIS_REPLY_ERROR) {
			std::cout << "认证失败" << std::endl;
			freeReplyObject(reply);
			continue;
		}
		std::cout << "认证成功" << std::endl;
		freeReplyObject(reply);
		connetc_.push(context);
	}
}


redisContext* RedisConPool::Getconnect() {
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this]() {
		if (b_stop_) {
			return true;
		}
		return !connetc_.empty();
		});
	if (b_stop_) {
		return NULL;
	}
	auto* context = connetc_.front();
	connetc_.pop();
	return context;
}


void RedisConPool::returnredisContext(redisContext* context) {
	std::unique_lock<std::mutex> lock(_mutex);
	if (b_stop_) {
		return;
	}
	connetc_.push(context);
	_cond.notify_one();
}


void RedisConPool::Close() {
	b_stop_ = true;
	_cond.notify_all();

}

RedisConPool::~RedisConPool() {
	std::lock_guard<std::mutex> lock(_mutex);
	while (!connetc_.empty()) {
		redisFree(connetc_.front());
		connetc_.pop();
	}
}