#ifndef CONUSERLIST_H
#define CONUSERLIST_H
#include "grouptipitem.h"
#include <QListWidget>
#include "conuseritem.h"
class ConUserList : public QListWidget
{
    Q_OBJECT
public:
    ConUserList(QWidget *parent = nullptr);
    void init();
    void ShowRedPoint(bool bshow = true);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;
private:
    ConUserItem * _add_frednd_item;
    QListWidgetItem* _groupitem;
    bool _load_pending;
signals:
    void sig_loading_contact_user();
    void sig_switch_friend_info_page(std::shared_ptr<UserInfo> user_info);
    void sig_switch_apply_friend_page();
public slots:
    void slot_item_clicked(QListWidgetItem *item);
    void slot_auth_rsp(std::shared_ptr<AuthRsp> rsp);
    void slot_add_auth_friend(std::shared_ptr<AuthInfo> info);
};

#endif // CONUSERLIST_H
