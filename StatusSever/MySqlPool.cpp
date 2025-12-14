#include "MySqlPool.h"
#include"ConfigMgr.h"


MySqlPool::MySqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, const int& poolsize):
	_user(user),_pass(pass),_poolsize(poolsize),_schema(schema),_url(url),_b_stop(false)
{		
	std::cout << "测试MySqlPool" << std::endl;
	try{
			for (int i = 0; i < _poolsize; ++i) {
				sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
				auto* con(driver->connect(_url, _user, pass));
				con->setSchema(_schema);
				auto currentTime = std::chrono::system_clock::now().time_since_epoch();
				// 将时间戳转换为秒
				long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
				_connect.push(std::make_unique<SqlConnect>(con, timestamp));
				
			}
			_check_thread = std::thread([this]() {
				while (!_b_stop) {
					checkConnectionPro();
					std::this_thread::sleep_for(std::chrono::seconds(60));
				}
				});

			_check_thread.detach();
		}
	catch (sql::SQLException e) {
		std::cout << "连接错误" << e.what() << std::endl;
	}

}


void MySqlPool::checkConnectionPro() {
	int size = _connect.size();
	auto currentTime = std::chrono::system_clock::now().time_since_epoch();
	// 将时间戳转换为秒
	long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();

	for (int i = 0; i < size; ++i) {
		std::unique_ptr<SqlConnect> con=std::move(_connect.front());
		_connect.pop();
			Defer defer([this,&con]() {
				_connect.push(std::move(con));
			});
		if (timestamp - con->_lasttime < 5) {
			continue;
		}
		try {
			std::unique_ptr<sql::Statement> stma(con->_con->createStatement());
			stma->executeQuery("SELECT 1");
			con->_lasttime = timestamp;
			std::cout << "currecy time is " << con->_lasttime << std::endl;
		}
		catch (sql::SQLException e) {
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
			auto c(driver->connect(_url, _user, _pass));
			c->setSchema(_schema);
			con->_con.reset(c);
			con->_lasttime = timestamp;
		}
	}
}


MySqlPool::~MySqlPool() {
	std::unique_lock<std::mutex> lock(_mutex);
	while (_connect.empty()) {
		_connect.pop();
	}
}

std::unique_ptr<SqlConnect> MySqlPool::Getsqlconn() {
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this]() {
		if (_b_stop) {
			return true;
		}
		return !_connect.empty();
	});
	if (_b_stop) {
		return nullptr;
	}
	std::unique_ptr<SqlConnect> conn(std::move(_connect.front()));
	_connect.pop();
	return conn;
}

void MySqlPool::returnconnect(std::unique_ptr<SqlConnect> conn) {
	std::unique_lock<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_connect.push(std::move(conn));
	_cond.notify_one();
}

void MySqlPool::Close() {
	_b_stop = true;
	_cond.notify_all();
}


MySqlDao::MySqlDao(){
	auto& cfg = ConfigMgr::GetConfigMgr();
	const auto& name = cfg["Mysql"]["Name"];
	const auto& pass = cfg["Mysql"]["Pass"];
	const auto& schema = cfg["Mysql"]["Schema"];
	const auto& user = cfg["Mysql"]["User"];
	const auto& host = cfg["Mysql"]["Host"];
	const auto& port = cfg["Mysql"]["Port"];
	std::cout << "测试MySqlDao" << std::endl;
	_pool.reset(new MySqlPool(host + ":" + port, user, pass, schema, 5));
}


int MySqlDao::Userreg(const std::string& name, const std::string& email, const std::string& passwd) {
	auto con = _pool->Getsqlconn();
	try {
		if (con == nullptr) {
			_pool->returnconnect(std::move(con));
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> stme(con->_con->prepareStatement("CALL reg_user(?,?,?,@result)"));
		std::cout << "测试sql::PreparedStatement" << std::endl;
		stme->setString(1, name);
		stme->setString(2, email);
		stme->setString(3, passwd);

		stme->execute();
		std::unique_ptr<sql::Statement>resstate(con->_con->createStatement());
		std::unique_ptr<sql::ResultSet>res(resstate->executeQuery("SELECT @result AS result"));
		if (res->next()) {
			int result = res->getInt("result");
			std::cout << result << std::endl;
			_pool->returnconnect(std::move(con));
			return result;
		}
			_pool->returnconnect(std::move(con));
			return -1;
	}
	catch (sql::SQLException e) {
		std::cout << "注册错误" << e.what() << std::endl;
		_pool->returnconnect(std::move(con));
		return -1;
	}


}


bool MySqlDao::CheckEmail(std::string name, std::string email) {
	auto con= _pool->Getsqlconn();
	try {
		if (!con) {
			_pool->returnconnect(std::move(con));
			return false;
		}
		//声明一个数据库操作
		std::unique_ptr<sql::PreparedStatement> stmt(con->_con->prepareStatement("SELECT email FROM user WHERE name=?"));
		stmt->setString(1, name);
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());//ql::Statement::executeQuery()返回的是一个 裸指（raw pointer）
		//查询结果是一个集合，res->next()定位到第一行
		if (res->next()) {
			std::cout << "email is " << email << std::endl;
			std::cout << "res is " << res->getString("email") << std::endl;
			if (email != res->getString("email"))
			{
				_pool->returnconnect(std::move(con));
				return false;
			}
			return true;
		}
		_pool->returnconnect(std::move(con));
		return false;
	}
	catch (sql::SQLException e) {
		_pool->returnconnect(std::move(con));
		std::cout << "error sqlconnect " << e.what() << std::endl;
		return false;
	}

}


bool MySqlDao::UpdateEmail(std::string email, std::string passwd) {
	auto con = _pool->Getsqlconn();
	try {
		if (con == nullptr) {
			_pool->returnconnect(std::move(con));
			return false;
		}

		std::unique_ptr<sql::PreparedStatement> stmt(con->_con->prepareStatement("UPDATE user SET pass=? WHERE email=? "));
		stmt->setString(1, passwd);
		stmt->setString(2, email);

		int updatawor = stmt->execute();
		std::cout << "update row is " << updatawor << std::endl;
		return true;
	}
	catch (sql::SQLException e) {
		_pool->returnconnect(std::move(con));
		std::cout << "error sqlconnect " << e.what() << std::endl;
		return false;
	}

}

bool MySqlDao::CheckPass(std::string email, std::string passwd, UserInfo userInfo) {
	return true;
}


MySqlDao::~MySqlDao() {
	_pool->Close();
}