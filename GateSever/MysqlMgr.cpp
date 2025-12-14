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

MysqlMgr::MysqlMgr() {
}
