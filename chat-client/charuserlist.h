#ifndef CHARUSERLIST_H
#define CHARUSERLIST_H

#include <QWidget>
#include"listitme.h"
#include"userdata.h"
namespace Ui {
class CharUserList;
}

class CharUserList : public Listitme
{
    Q_OBJECT

public:
    explicit CharUserList(QWidget *parent = nullptr);
    ~CharUserList();
    QSize SetHint()const{
         return QSize(250, 100);
    }
    void SetInfo(std::shared_ptr<FriendInfo> friend_info);
    void SetInfo(std::shared_ptr<UserInfo> auth_info);
    std::shared_ptr<UserInfo> Getuser();
    void updateLastMsg(std::vector<std::shared_ptr<TextChatData>>);
private:
    std::shared_ptr<UserInfo> _user_info;
    Ui::CharUserList *ui;
    QString _name;
    QString _head;
    QString _msg;
};

#endif // CHARUSERLIST_H
