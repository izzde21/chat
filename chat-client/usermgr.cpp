#include "usermgr.h"
#include<QJsonArray>
UserMgr::UserMgr():_userinfo(nullptr), _chat_loaded(0),_contact_loaded(0) {

}
void UserMgr::setuserinfo(std::shared_ptr<UserInfo> userinfo){
    _userinfo=userinfo;
}

std::shared_ptr<UserInfo> UserMgr::Getuserinfo(){
    return _userinfo;
}

void UserMgr::Settoken(QString token){
     _token=token;
}
void UserMgr::Setname(QString name){
    _name=name;
}
void UserMgr::Setid(int id){
    _id=id;
}

void UserMgr::AddApplyList(std::shared_ptr<ApplyInfo> apply){
    _apply_list.push_back(apply);
}

void UserMgr::AppendApplyList(QJsonArray array)
{
    for(const QJsonValue &value:array){
        auto uid=value["uid"].toInt();
        qDebug()<<"uid"<<uid;
        auto name=value["name"].toString();
        auto nick=value["nick"].toString();
        auto desc=value["desc"].toString();
        auto icon=value["icon"].toString();
        auto sex=value["sex"].toInt();
        auto status=value["status"].toInt();
        qDebug() << "icon is"<<icon;
        auto applyinfo=std::make_shared<ApplyInfo>(uid,name,desc,icon,nick,sex,status);
        _apply_list.push_back(applyinfo);
    }
}

void UserMgr::AddFriendList(QJsonArray friend_list)
{
    for(const QJsonValue &value:friend_list){
        auto uid=value["uid"].toInt();
        auto name=value["name"].toString();
        auto nick=value["nick"].toString();
        auto desc=value["desc"].toString();
        auto icon=value["icon"].toString();
        auto sex=value["sex"].toInt();
        auto back=value["back"].toString();
        auto friend_info=std::make_shared<FriendInfo>(uid, name,nick,icon, sex,desc,back,"");
        _friend_list.push_back(friend_info);
        _friend_map.insert(uid, friend_info);
    }
}

std::vector<std::shared_ptr<FriendInfo>> UserMgr::GetFriendlist()
{
    return _friend_list;
}

bool UserMgr::CheckFriendById(int uid)
{
    auto itea=_friend_map.find(uid);
    if(itea==_friend_map.end()){
        return false;
    }
    return true;
}

void UserMgr::AddFriend(std::shared_ptr<AuthInfo> auth_info)
{
    auto friendinfo=std::make_shared<FriendInfo>(auth_info);
    _friend_map[friendinfo->_uid]=friendinfo;
}

void UserMgr::AddFriend(std::shared_ptr<AuthRsp> auth_info)
{
    auto friendinfo=std::make_shared<FriendInfo>(auth_info);
    _friend_map[friendinfo->_uid]=friendinfo;
}


bool UserMgr::AlreadyApply(int uid){
    for(auto& a:_apply_list){
        a->_uid=uid;
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<ApplyInfo>> UserMgr::GetApplyList()
{
    return _apply_list;
}

bool UserMgr::IsLoadChatFin(){
    if(_chat_loaded>=_friend_list.size()){
        return true;
    }
    return false;
}
void UserMgr::UpdateChatLoadedCount(){
    int begin=_chat_loaded;
    int end=begin+CHAT_COUNT_PER_PAGE;
    if(begin >= _friend_list.size()){
        return;
    }

    if(end >= _friend_list.size()){
        _chat_loaded=_friend_list.size();
        return;
    }
    _chat_loaded=end;
}


void UserMgr::UpdateContactLoadedCount(){
    int begin=_contact_loaded;
    int end=begin+CHAT_COUNT_PER_PAGE;
    if(begin >= _friend_list.size()){
        return;
    }

    if(end >= _friend_list.size()){
        _contact_loaded=_friend_list.size();
        return;
    }
    _contact_loaded=end;
}

bool UserMgr::IsLoadConFin(){
    if(_contact_loaded>=_friend_list.size()){
        return true;
    }
    return false;
}

void UserMgr::AppendFriendChatMsg(int uis, std::vector<std::shared_ptr<TextChatData>> msgs)
{
    qDebug()<<"AppendFriendChatMsg";
    auto itea=_friend_map.find(uis);
    if(itea==_friend_map.end()){
        return;
    }
    itea.value()->AppendChatMsgs(msgs);
}


std::vector<std::shared_ptr<FriendInfo>> UserMgr::GetConListPerPage() {
    std::vector<std::shared_ptr<FriendInfo>> friend_list;
    int begin = _contact_loaded;
    int end = begin + CHAT_COUNT_PER_PAGE;

    if (begin >= _friend_list.size()) {
        return friend_list;
    }

    if (end > _friend_list.size()) {
        friend_list = std::vector<std::shared_ptr<FriendInfo>>(_friend_list.begin() + begin, _friend_list.end());
        return friend_list;
    }


    friend_list = std::vector<std::shared_ptr<FriendInfo>>(_friend_list.begin() + begin, _friend_list.begin() + end);
    return friend_list;
}

std::shared_ptr<FriendInfo> UserMgr::GetFriendById(int uid)
{
    auto itea=_friend_map.find(uid);
    if(itea==_friend_map.end()){
        return nullptr;
    }
    auto friend_info=itea.value();
        return friend_info;
}


std::vector<std::shared_ptr<FriendInfo>> UserMgr::GetChatListPerPage(){

    std::vector<std::shared_ptr<FriendInfo>> friend_list;
    int begin = _chat_loaded;
    int end = begin + CHAT_COUNT_PER_PAGE;
    if (begin >= _friend_list.size()) {
        return friend_list;
    }
    if (end > _friend_list.size()) {
        friend_list = std::vector<std::shared_ptr<FriendInfo>>(_friend_list.begin() + begin, _friend_list.end());
        return friend_list;
    }
    friend_list = std::vector<std::shared_ptr<FriendInfo>>(_friend_list.begin() + begin, _friend_list.begin()+ end);
    return friend_list;
}
