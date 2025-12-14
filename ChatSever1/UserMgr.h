#pragma once
#include"Singelton.h"
#include "CSession.h"
#include"const.h"
#include<unordered_map>
class UserMgr :public Singelton<UserMgr>
{
	friend class Singelton<UserMgr>;
public:
	~UserMgr();
	void SetUserSession(int uid, std::shared_ptr<CSession>session);
	std::shared_ptr<CSession> GetSession(int uid);
	void RmvUserSession(int uid, std::string);
private:
	UserMgr();
	std::mutex mutex_;
	std::unordered_map<int, std::shared_ptr<CSession>> _uid_to_session;
};

