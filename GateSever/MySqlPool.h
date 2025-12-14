#pragma once
#include"const.h"
#include<jdbc/mysql_driver.h>   
#include<jdbc/mysql_connection.h>   
#include<jdbc/cppconn/prepared_statement.h>
#include<jdbc/cppconn/resultset.h>
#include<jdbc/cppconn/statement.h>
#include<jdbc/cppconn/exception.h>

struct UserInfo {
	std::string name;
	std::string pwd;
	int uid;
	std::string email;
};

class SqlConnect 
{
public:
	SqlConnect(sql::Connection* con, int64_t lasttime) :_con(con), _lasttime(lasttime){
	}
	int64_t _lasttime;
	std::unique_ptr < sql::Connection> _con;
};

class MySqlPool
{
public:
	MySqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, const int& poolsize);
	~MySqlPool();
	std::unique_ptr<SqlConnect> Getsqlconn();
	void returnconnect(std::unique_ptr<SqlConnect> conn);
	void Close();
	void checkConnectionPro();
private:
	std::string _user;
	std::string _pass;
	std::string _url;
	int _poolsize;
	std::queue<std::unique_ptr<SqlConnect>> _connect;
	std::mutex _mutex;
	bool _b_stop;
	std::string _schema;
	std::condition_variable _cond;
	std::thread _check_thread;
};


class MySqlDao
{
public:
	MySqlDao();
	~MySqlDao();
	int Userreg(const std::string& name, const std::string& email, const std::string& passwd);
	bool CheckEmail(std::string name, std::string email);
	bool UpdateEmail(std::string email, std::string passwd);
	bool CheckPass(std::string email, std::string passwd, UserInfo& userInfo);
private:
	std::unique_ptr <MySqlPool> _pool;
};

