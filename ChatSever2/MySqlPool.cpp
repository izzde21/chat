#include "MySqlPool.h"
#include"ConfigMgr.h"
#include"data.h"

MySqlPool::MySqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, const int& poolsize):
	_user(user),_pass(pass),_poolsize(poolsize),_schema(schema),_url(url),_b_stop(false)
{		
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

		std::unique_ptr<sql::PreparedStatement> stmt(con->_con->prepareStatement("UPDATE user SET pwd=? WHERE email=? "));
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

bool MySqlDao::CheckPass(std::string email, std::string passwd, UserInfo &userInfo) {
	auto con = _pool->Getsqlconn();
	Defer defer([this, &con]() {
		_pool->returnconnect(std::move(con));
		});
	if (con==nullptr) {
		return false;
	}
	try {
		std::unique_ptr<sql::PreparedStatement>stmt(con->_con->prepareStatement("SELECT * FROM user WHERE email=?"));
			stmt->setString(1, email);
			std::unique_ptr<sql::ResultSet>res(stmt->executeQuery());
			std::string orgin_pass = "";
			while (res->next()) {
				orgin_pass = res->getString("pwd");
				std::cout << "pwd is " << orgin_pass << std::endl;
				break;
			}

			if (passwd != orgin_pass) {
				return false;
			}
			userInfo.email= res->getString("email");
			userInfo.name = res->getString("name");
			userInfo.pwd = orgin_pass;
			userInfo.uid = res->getInt("uid");
			std::cout << "uid is  " << userInfo.uid << std::endl;
			return true;
	}
	catch (sql::SQLException e) {
		std::cout << "error CheckPass " << e.what() << std::endl;
		return false;
	}
	
}

bool MySqlDao::GetApplyList(int to_uid, std::vector<std::shared_ptr<ApplyInfo>> &list, int begin, int end) {
	auto con = _pool->Getsqlconn();
	try {
		if (con == nullptr) {
			_pool->returnconnect(std::move(con));
			return false;
		}

		Defer defer([this, &con]() {
			_pool->returnconnect(std::move(con));
			});

		std::unique_ptr<sql::PreparedStatement> ptmta(con->_con->prepareStatement("SELECT apply.from_uid,apply.status,user.name,user.sex,user.icon,user.nick FROM friend_apply as apply join user on apply.from_uid = user.uid where apply.to_uid = ? "
			"and apply.id > ? order by apply.id ASC LIMIT ? "));

		ptmta->setInt(1, to_uid); 
		ptmta->setInt(2, begin); 
		ptmta->setInt(3, end); 

		std::unique_ptr<sql::ResultSet> res(ptmta->executeQuery());
		while(res->next()) {
			auto name= res->getString("name");
			auto uid = res->getInt("from_uid");
			auto status = res->getInt("status");
			auto sex= res->getInt("sex");
			auto nick= res->getString("nick");
			auto icon= res->getString("icon");
			std::cout << "icon is " << std::endl;
			auto apply = std::make_shared<ApplyInfo>(uid, name, "", icon, nick, sex,status);
			list.push_back(apply);
		}
		return true;

	}
	catch (sql::SQLException e) {
		_pool->returnconnect(std::move(con));
		std::cout << "error dasasdas " << e.what() << std::endl;
		std::cout << "error sqlconnect " << e.what() << std::endl;
		return false;
	}


}


bool MySqlDao::GetFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list) {
	auto con = _pool->Getsqlconn();
	try {
		if (con == nullptr) {
			_pool->returnconnect(std::move(con));
			return false;
		}

		Defer defer([this, &con]() {
			_pool->returnconnect(std::move(con));
		});

		std::unique_ptr<sql::PreparedStatement> ptmst(con->_con->prepareStatement("select * from friend where self_id = ? "));
		ptmst->setInt(1, uid);
		std::unique_ptr <sql::ResultSet>res(ptmst->executeQuery());
		while(res->next()){
			auto uid = res->getInt("friend_id");
			auto back= res->getString("back");
			auto user_info = GetUser(uid);
			if (user_info == nullptr) {
				continue;
			}
			user_info->back = user_info->name;
			list.push_back(user_info);

		}

		return true;
	}
	catch (sql::SQLException e) {
		_pool->returnconnect(std::move(con));
		std::cout << "error sqlconnect " << e.what() << std::endl;
		return false;
	}
	return true;
}


std::shared_ptr<UserInfo> MySqlDao::GetUser(std::string name) {
	auto con = _pool->Getsqlconn();
	try {
		if (con == nullptr) {
			_pool->returnconnect(std::move(con));
			return nullptr;
		}

		Defer defer([this, &con]() {
			_pool->returnconnect(std::move(con));
			});

		std::unique_ptr<sql::PreparedStatement> stam(con->_con->prepareStatement("SELECT * FROM user WHERE name = ?"));
		stam->setString(1, name);
		std::unique_ptr<sql::ResultSet>ret(stam->executeQuery());
		std::unique_ptr<UserInfo> userinfo = nullptr;
		while (ret->next()) {
			userinfo.reset(new UserInfo);
			userinfo->pwd = ret->getString("pwd");
			userinfo->email = ret->getString("email");
			userinfo->name = ret->getString("name");
			userinfo->nick = ret->getString("nick");
			userinfo->desc = ret->getString("desc");
			userinfo->sex = ret->getInt("sex");
			userinfo->icon = ret->getString("icon");
			userinfo->uid = ret->getInt("uid");
			break;
		}
		return userinfo;
	}
	catch (sql::SQLException e) {
		_pool->returnconnect(std::move(con));
		std::cout << "error sqlconnect " << e.what() << std::endl;
		return nullptr;
	}
}

std::shared_ptr<UserInfo> MySqlDao::GetUser(int uid) {
	auto con = _pool->Getsqlconn();
	try {
		if (con == nullptr) {
			_pool->returnconnect(std::move(con));
			return nullptr;
		}

		Defer defer([this, &con]() {
			_pool->returnconnect(std::move(con));
			});

		std::unique_ptr<sql::PreparedStatement> stam(con->_con->prepareStatement("SELECT * FROM user WHERE uid = ?"));
		stam->setInt(1, uid);
		std::unique_ptr<sql::ResultSet>ret(stam->executeQuery());
		std::unique_ptr<UserInfo> userinfo = nullptr;
		while(ret->next()) {
			userinfo.reset(new UserInfo);
			userinfo->pwd = ret->getString("pwd");
			userinfo->email = ret->getString("email");
			userinfo->name = ret->getString("name");
			userinfo->nick = ret->getString("nick");
			userinfo->desc = ret->getString("desc");
			userinfo->sex = ret->getInt("sex");
			userinfo->icon = ret->getString("icon");
			userinfo->uid = uid;
			break;
		}
		return userinfo;
	}
	catch (sql::SQLException e) {
		_pool->returnconnect(std::move(con));
		std::cout << "error sqlconnect " << e.what() << "uid is"<<uid<< std::endl;
		return nullptr;
	}
}


bool MySqlDao::AuthFriendApply(const int& uid, const int& touid) {
	auto con = _pool->Getsqlconn();
	if (con == nullptr) {
		return false;
	}
	Defer defer([this,&con]() {
		_pool->returnconnect(std::move(con));
		});
	try {
		std::unique_ptr<sql::PreparedStatement> ptmts(con->_con->prepareStatement("UPDATE friend_apply SET status=1 WHERE from_uid=? and to_uid=?"));
		ptmts->setInt(1, uid);
		ptmts->setInt(2, touid);

		int row=ptmts->executeUpdate();
		if (row<0) {
			con->_con->rollback();
			return false;
		}
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
	}

}


bool MySqlDao::AddFriend(const int& from, const int& to, std::string back_name) {
	auto con = _pool->Getsqlconn();
	if(con == nullptr) {
		return false;
	}
	Defer defer([this, &con]() {
		_pool->returnconnect(std::move(con));
		});
	try {
		con->_con->setAutoCommit(false);
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
			"VALUES (?, ?, ?) "
		));
		pstmt->setInt(1, from); // from id
		pstmt->setInt(2, to);
		pstmt->setString(3, back_name);

		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0) {
			con->_con->rollback();
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> pstmt2(con->_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
			"VALUES (?, ?, ?) "
		));

		pstmt2->setInt(1, to); // from id
		pstmt2->setInt(2, from);
		pstmt2->setString(3, "");

		int rowAffected2 = pstmt2->executeUpdate();
		if (rowAffected2 < 0) {
			con->_con->rollback();
			return false;
		}


		con->_con->commit();
		std::cout << "addfriend insert friends success" << std::endl;

		return true;
	}
	catch (sql::SQLException& e) {
		if (con) {
			con->_con->rollback();
		}
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}


	return true;
}


bool MySqlDao::AddFriendReply(int uid, int touid) {
	auto con=_pool->Getsqlconn();
	if (!con) {
		return false;
	}
	Defer defer([this,&con]() {
		_pool->returnconnect(std::move(con));
		});

	try {
		std::unique_ptr<sql::PreparedStatement> psmtm(con->_con->prepareStatement("INSERT INTO friend_apply (from_uid, to_uid) values (?,?) "
			"ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"));
		psmtm->setInt(1, uid); 
		psmtm->setInt(2, touid);

		auto success = psmtm->executeUpdate();
		if (success < 0) {
			return false;
		}
		return true;
	}
	catch (sql::SQLException e) {
		std::cout << "error is " << e.what() << std::endl;
		return false;
	}
	return true;
}

MySqlDao::~MySqlDao() {
	_pool->Close();
}