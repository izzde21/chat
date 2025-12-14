#include "charuserlist.h"
#include "ui_charuserlist.h"
#include<QLabel>
#include<QFontMetrics>
#include"userdata.h"
CharUserList::CharUserList(QWidget *parent)
    :ui(new Ui::CharUserList),Listitme(parent)
{
    ui->setupUi(this);
    seticontype(CHAT_USER_ITEM);
}

CharUserList::~CharUserList()
{
    delete ui;
}

void CharUserList::SetInfo(std::shared_ptr<UserInfo> user_info_){
     _user_info=user_info_;
    _name=user_info_->_name;
    _head=user_info_->_icon;
    _msg=user_info_->_last_msg;

    QPixmap pixmap(_head);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);

    ui->user_name_lb->setText(_name);

    ui->char_lb->setText(_msg);

    ui->char_lb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 设置文本对齐方式
    QString text = ui->char_lb->text();
    QFontMetrics metrics(ui->char_lb->font());
    QString ellidedText = metrics.elidedText(text, Qt::ElideRight, ui->char_lb->width());
    ui->char_lb->setText(ellidedText);

}

void CharUserList::SetInfo(std::shared_ptr<FriendInfo> friend_info){
    auto user_info=std::make_shared<UserInfo>(friend_info);
    _user_info=user_info;
    _name=friend_info->_name;
    _head=friend_info->_icon;
    _msg=friend_info->_last_msg;

    QPixmap pixmap(_head);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);

    ui->user_name_lb->setText(_name);

    ui->char_lb->setText(_msg);

    ui->char_lb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 设置文本对齐方式
    QString text = ui->char_lb->text();
    QFontMetrics metrics(ui->char_lb->font());
    QString ellidedText = metrics.elidedText(text, Qt::ElideRight, ui->char_lb->width());
    ui->char_lb->setText(ellidedText);

}


std::shared_ptr<UserInfo> CharUserList::Getuser()
{
    return _user_info;
}

void CharUserList::updateLastMsg(std::vector<std::shared_ptr<TextChatData>> msgs)
{
    QString last_msg="";
    for(auto& msg:msgs){
        qDebug()<<"auto& msg:msgs";
        last_msg=msg->_msg_content;
        _user_info->_chat_msgs.push_back(msg);
    }
    _user_info->_last_msg=last_msg;
    ui->char_lb->setText(last_msg);
}



