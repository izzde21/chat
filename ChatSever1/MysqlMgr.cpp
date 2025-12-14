#include "MysqlMgr.h"
MysqlMgr::~MysqlMgr() {
}


int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
    return _dao.Userreg(name, email, pwd);
}

bool MysqlMgr::CheckEmail(std::string name, std::string email) {

    return _dao.CheckEmail(name, email);
}

bool MysqlMgr::UpdateEmail(std::string email, std::string passwd) {

    return _dao.UpdateEmail(email, passwd);
}

bool MysqlMgr::CheckPass(std::string email, std::string passwd, UserInfo &userInfo) {
    return _dao.CheckPass(email, passwd, userInfo);
}
std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid) {
    return _dao.GetUser(uid);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(std::string name) {
    return _dao.GetUser(name);
}

bool MysqlMgr::AddFriendReply(int uid, int touid) {
    return _dao.AddFriendReply(uid,touid);
}

bool MysqlMgr::GetApplyList(int to_uid, std::vector<std::shared_ptr<ApplyInfo>> &list, int begin, int end) {
    return _dao.GetApplyList(to_uid, list, begin, end);
}

bool MysqlMgr::AuthFriendApply(const int& uid, const int& touid) {
    return _dao.AuthFriendApply(uid, touid);
}
bool MysqlMgr::AddFriend(const int& from, const int& to, std::string back_name) {
    return _dao.AddFriend(from, to, back_name);
}

bool MysqlMgr::GetFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list) {
    return _dao.GetFriendList(uid, list);
}

MysqlMgr::MysqlMgr() {
}
