#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include"global.h"
#include<QList>
#include"statewidget.h"
#include<QEvent>
#include<QMouseEvent>
#include"userdata.h"
#include<QListWidgetItem>
namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
    void ShowSearch(bool bsearch);
    void addChatUserList();
protected:
    bool eventFilter(QObject *object, QEvent *event) override{
        if(event->type()==QEvent::MouseButtonPress){
            QMouseEvent * mouseEvent=static_cast<QMouseEvent*>(event);
            handleGlobalMousePress(mouseEvent);
        }
        return QDialog::eventFilter(object,event);
    }
private:
    void Claerlist(StateWidget* w);
    void AddlbGroud(StateWidget* w);
    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    QList<StateWidget*> list_lb;
    void handleGlobalMousePress(QMouseEvent* me);
    QMap<int, QListWidgetItem*> _chat_items_added;
    void loadMoreChatUser();
    void loadMoreConUser();
    int _cur_chat_uid;
    QWidget* _last_page;
    void SetSelectChatPage(int uid);
    void SetSelectChatItem(int uid);
    void UpdateChatMsg(std::vector<std::shared_ptr<TextChatData>> text);
public slots:
    void slot_have_apply();
    void slot_loading_chat_user();
    void slot_chat_lb_click();
    void slot_contact_lb_click();
    void slot_text_changed(const QString &str);
    void slot_apply_friend(std::shared_ptr<AddFriendApply>);
    void slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp);
    void slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info);
    void slot_jump_chat_item(std::shared_ptr<SearchInfo> si);
    void slot_loading_contact_user();
    void slot_switch_friend_info_page(std::shared_ptr<UserInfo> user_info);
    void slot_switch_apply_friend_page();
    void slot_item_clicked(QListWidgetItem *item);
    void slot_jump_chat_item_from_infopage(std::shared_ptr<UserInfo> user_info);
    void slot_append_send_chat_msg(std::shared_ptr<TextChatData> text);
    void slot_text_chat_msg(std::shared_ptr<TextChatMsg>msg);
};

#endif // CHATDIALOG_H
