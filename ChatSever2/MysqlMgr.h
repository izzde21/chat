#pragma once
#include "const.h"
#include "MysqlPool.h"
#include"Singelton.h"


class MysqlMgr : public Singelton<MysqlMgr>
{
    friend class Singelton<MysqlMgr>;
public:
    ~MysqlMgr();
    int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
    bool CheckEmail(std::string name, std::string email);
    bool UpdateEmail(std::string name, std::string passwd);
    bool CheckPass(std::string email, std::string passwd, UserInfo& userInfo);
    std::shared_ptr<UserInfo> GetUser(int uid);
    std::shared_ptr<UserInfo> GetUser(std::string name);
    bool AddFriendReply(int uid, int touid);
    bool GetApplyList(int to_uid, std::vector<std::shared_ptr<ApplyInfo>> &list, int begin, int end);
    bool AuthFriendApply(const int& uid, const int& touid);
    bool AddFriend(const int& from, const int& to, std::string back_name);
    bool GetFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list);
private:
    MysqlMgr();

    MySqlDao  _dao;
};



