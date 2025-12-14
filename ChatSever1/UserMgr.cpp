#include "UserMgr.h"
UserMgr::UserMgr() {

}
void UserMgr::SetUserSession(int uid, std::shared_ptr<CSession>session) {
	std::unique_lock<std::mutex> lock(mutex_);
	_uid_to_session[uid] = session;
}

std::shared_ptr<CSession> UserMgr::GetSession(int uid) {
	auto itea = _uid_to_session.find(uid);
	if (itea == _uid_to_session.end()) {
		return nullptr;
	}
	return itea->second;
		
}

void UserMgr::RmvUserSession(int uid,std::string) {

}

UserMgr::~UserMgr() {
	_uid_to_session.clear();
}
