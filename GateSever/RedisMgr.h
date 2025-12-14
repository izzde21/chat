#pragma once
#include"Singelton.h"
#include"const.h"

class RedisConPool
{
public:
    RedisConPool(std::size_t poolsize, const char* host,  int port, const char*  pass);
    ~RedisConPool();
    redisContext* Getconnect();
    void stop();
    void returnredisContext(redisContext* context);
    void Close();
private:
    const char* host_;
    int _port;
    const char* _pass;
    std::mutex _mutex;
    std::condition_variable _cond;
    std::queue<redisContext*> connetc_;
    std::size_t _poolsize;
    bool b_stop_;
};

class RedisMgr:public Singelton<RedisMgr>,public std::enable_shared_from_this<RedisMgr>
{
	friend class Singelton<RedisMgr>;
public:
	~RedisMgr();
    bool Connect(const std::string& host, int port);
    bool Get(const std::string& key, std::string& value);
    bool Set(const std::string& key, const std::string& value);
    bool Auth(const std::string& password);
    bool LPush(const std::string& key, const std::string& value);
    bool LPop(const std::string& key, std::string& value);
    bool RPush(const std::string& key, const std::string& value);
    bool RPop(const std::string& key, std::string& value);
    bool HSet(const std::string& key, const std::string& hkey, const std::string& value);
    bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
    std::string HGet(const std::string& key, const std::string& hkey);
    bool Del(const std::string& key);
    bool ExistsKey(const std::string& key);
    void Close();
private:
	RedisMgr();
    std::unique_ptr<RedisConPool> con_pool;
};

