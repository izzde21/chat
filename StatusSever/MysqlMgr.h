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
    bool CheckPass(std::string email, std::string passwd, UserInfo userInfo);
private:
    MysqlMgr();

    MySqlDao  _dao;
};



