#ifndef CONUSERITEM_H
#define CONUSERITEM_H

#include <QWidget>
#include "listitme.h"
#include"userdata.h"
#include<memory>
namespace Ui {
class ConUserItem;
}

class ConUserItem : public Listitme
{
    Q_OBJECT

public:
    explicit ConUserItem(QWidget *parent = nullptr);
    ~ConUserItem();
    QSize Getsize();
    void SetInfo(std::shared_ptr<FriendInfo> friendinfo);
    void SetInfo(std::shared_ptr<AuthInfo> addly);
    void SetInfo(std::shared_ptr<AuthRsp> addly);
    void SetInfo(int uid,QString name,QString icon);
    void ShowRidpoint(bool is);
    std::shared_ptr<UserInfo> GetInfo();
private:
    Ui::ConUserItem *ui;
    std::shared_ptr<UserInfo> user_info;
};

#endif // CONUSERITEM_H
