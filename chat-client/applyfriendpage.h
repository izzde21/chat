#ifndef APPLYFRIENDPAGE_H
#define APPLYFRIENDPAGE_H

#include <QWidget>
#include<memory>
#include"userdata.h"
#include<unordered_map>
#include"applyfrienditem.h"
#include"applyfriendlist.h"
#include "clickedbtn.h"
namespace Ui {
class ApplyFriendPage;
}

class ApplyFriendPage : public QWidget
{
    Q_OBJECT

public:
    explicit ApplyFriendPage(QWidget *parent = nullptr);
    ~ApplyFriendPage();
    void AddNewApply(std::shared_ptr<AddFriendApply> apply);
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::ApplyFriendPage *ui;
    void loadApplyList();
    std::unordered_map<int, ApplyFriendItem*> _unauth_items;
    bool hasNewApply=false;
signals:
    void sig_show_search(bool);
    void sig_have_apply();
public slots:

    void slot_auth_rsp(std::shared_ptr<AuthRsp>);
};

#endif // APPLYFRIENDPAGE_H
