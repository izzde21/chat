#ifndef USERMGR_H
#define USERMGR_H
#include"Singelton.h"
#include"userdata.h"
#include<memory>
#include<vector>
#include<QJsonArray>
#include<QMap>
class UserMgr:public Singelton<UserMgr>
{
public:
    UserMgr();
    void Settoken(QString token);
    void Setname(QString name);
    void Setid(int id);
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
    void setuserinfo(std::shared_ptr<UserInfo> userinfo);
    std::shared_ptr<UserInfo> Getuserinfo();
    bool AlreadyApply(int uid);
    void AddApplyList(std::shared_ptr<ApplyInfo> apply);
    void AppendApplyList(QJsonArray array);
    void AddFriendList(QJsonArray _friend_list);
    std::vector<std::shared_ptr<FriendInfo>> GetFriendlist();
    bool CheckFriendById(int uid);
    void AddFriend(std::shared_ptr<AuthInfo> auth_info);
    void AddFriend(std::shared_ptr<AuthRsp> auth_info);
    bool IsLoadChatFin();
    void UpdateChatLoadedCount();
    void UpdateContactLoadedCount();
    bool IsLoadConFin();
    void AppendFriendChatMsg(int uis,std::vector<std::shared_ptr<TextChatData>>);
    std::vector<std::shared_ptr<FriendInfo>> GetChatListPerPage();
    std::vector<std::shared_ptr<FriendInfo>> GetConListPerPage();
    std::shared_ptr<FriendInfo> GetFriendById(int uid);
private:
    std::shared_ptr<UserInfo>_userinfo;
    QString _token;
    QString _name;
    int _id;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    QMap<int,std::shared_ptr<FriendInfo>>_friend_map;
    std::vector<std::shared_ptr<FriendInfo>> _friend_list;
    int _chat_loaded;
    int _contact_loaded;
};

#endif // USERMGR_H
