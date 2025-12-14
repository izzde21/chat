#pragma once
#include"const.h"
#include"Singelton.h"
#include"CSession.h"
#include"RedisMgr.h"
#include"MysqlMgr.h"
#include"MySqlPool.h"
typedef std::function<void(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data)>FunCallBack;
class LogicSystem :public Singelton<LogicSystem>
{
	friend class Singelton<LogicSystem>;
public:
	LogicSystem();
	~LogicSystem();
	void PostMsgToQue(std::shared_ptr<LogicNode> msg);
private:
	bool GetFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list);
	bool GetFriendApplyInfo(int uid, std::vector<std::shared_ptr<ApplyInfo>> &list);
	void GetUserByUid(std::string uid, Json::Value& root);
	void GetUserByName(std::string uid, Json::Value& root);
	bool Checkintorstring(std::string uid);
	void SearchInfo(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data);
	void LoginHander(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data);
	void AddFriendApply(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data);
	void AuthFriendApply(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data);
	void DealChatTextMsg(std::shared_ptr<CSession>csess, const short& msg_id, const std::string& msg_data);
	void RegisterCallBacks();
	void DealMsg();
	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);
	std::queue<std::shared_ptr<LogicNode>> _msg_que;
	std::thread _thread;
	std::mutex _mutex;
	std::map<short, FunCallBack>_funcallback;
	std::condition_variable _cond;
	bool _b_stop;
};

