#include "chatpage.h"
#include "ui_chatpage.h"
#include<QStyleOption>
#include<QPainter>
#include"ChatItemBase.h"
#include"TextBubble.h"
#include"PictureBubble.h"
#include"tcpmgr.h"
ChatPage::ChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    ui->emo_lb->setCursor(Qt::PointingHandCursor);
    ui->file_lb->setCursor(Qt::PointingHandCursor);
    ui->emo_lb->setstatu("normal","hover","press","normal","hover","press");
    ui->file_lb->setstatu("normal","hover","press","normal","hover","press");

    ui->receive_btn->SetStatu("normal","hover","press");
    ui->send_btn->SetStatu("normal","hover","press");
}

void ChatPage::paintEvent(QPaintEvent *event){
    QStyleOption op;
    op.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,&op,&painter,this);
}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::SetUserInfo(std::shared_ptr<UserInfo> user)
{
    _user_info=user;
    ui->title_lb->setText(user->_name);
    ui->chat_data_list->removeAllItem();
    for(auto & msg:user->_chat_msgs){
        AppendChatMsg(msg);
    }
}

void ChatPage::AppendChatMsg(std::shared_ptr<TextChatData> chat_msg)
{
    auto self_info=UserMgr::GetInstance()->Getuserinfo();
    ChatRole role;
    if(self_info->_uid==chat_msg->_from_uid){
        role=ChatRole::Self;
        ChatItemBase* chatitem=new ChatItemBase(role);
        chatitem->setUserIcon(self_info->_icon);
        chatitem->setUserName(self_info->_name);

        QWidget* pBubble = nullptr;
        pBubble=new TextBubble(role,chat_msg->_msg_content);
        chatitem->setWidget(pBubble);
        ui->chat_data_list->appendChatItem(chatitem);
    }
    else{
        role=ChatRole::Other;
        ChatItemBase* chatitem=new ChatItemBase(role);
        auto friend_info=UserMgr::GetInstance()->GetFriendById(chat_msg->_from_uid);
        chatitem->setUserIcon(friend_info->_icon);
        chatitem->setUserName(friend_info->_name);

        QWidget* pBubble = nullptr;
        pBubble=new TextBubble(role,chat_msg->_msg_content);
        chatitem->setWidget(pBubble);
        ui->chat_data_list->appendChatItem(chatitem);
    }
}



void ChatPage::on_send_btn_clicked()
{
    if(!_user_info){
        return;
    }
    auto user_info=UserMgr::GetInstance()->Getuserinfo();
    auto ptext=ui->chat_edit;
    QString name=user_info->_name;
    QString icon=user_info->_icon;
    ChatRole role;
    role=ChatRole::Self;
    const QVector<MsgInfo>& msgList=ptext->getMsgList();
    QJsonArray textArray;
    QJsonObject textobj;
    int text_size=0;
    for(int i=0;i<msgList.size();i++){
        if(msgList[i].content.length()>1024){
            continue;
        }

        auto type=msgList[i].msgFlag;
        auto pcharitembase=new ChatItemBase(role);
        pcharitembase->setUserIcon(icon);
        pcharitembase->setUserName(name);

        QWidget *pBubble = nullptr;
        if(type=="text"){
            QUuid uuid = QUuid::createUuid();
            QString uuidString = uuid.toString();
            pBubble=new TextBubble(role,msgList[i].content);
            if(text_size+msgList[i].content.length()>1024){
                textobj["touid"]=_user_info->_uid;
                textobj["fromuid"]=user_info->_uid;
                qDebug()<<"on_send_btn_clicked fromuid is "<<user_info->_uid;
                textobj["text_array"]=textArray;

                QJsonDocument doc(textobj);
                QByteArray arr=doc.toJson(QJsonDocument::Compact);
                text_size=0;
                textArray = QJsonArray();
                textobj = QJsonObject();

                emit TcpMgr::GetInstance()->sig_send_meg(ID_TEXT_CHAT_MSG_REQ,arr);
            }

            text_size+=msgList[i].content.length();
            QJsonObject obj;
            QByteArray utf8=msgList[i].content.toUtf8();
            obj["content"]=QString::fromUtf8(utf8);
            obj["msgid"]=uuidString;
            textArray.append(obj);
            auto txt_msg =std::make_shared<TextChatData>(uuidString,obj["content"].toString(),user_info->_uid,_user_info->_uid);
            emit sig_append_send_chat_msg(txt_msg);
        }
        else if(type == "image")
        {
            pBubble = new PictureBubble(QPixmap(msgList[i].content) , role);
        }
        else if(type == "file")
        {

        }

        if(pBubble){
            qDebug() << "pBubble is not null" << textArray;
            pcharitembase->setWidget(pBubble);
            ui->chat_data_list->appendChatItem(pcharitembase);
        }
    }
    qDebug() << "textArray is " << textArray;
    textobj["touid"]=_user_info->_uid;
    textobj["fromuid"]=user_info->_uid;
     qDebug()<<"pBubble is not null is and uid "<<user_info->_uid;
    textobj["text_array"]=textArray;

    QJsonDocument doc(textobj);
    QByteArray arr=doc.toJson(QJsonDocument::Compact);
    text_size=0;
    textArray = QJsonArray();
    textobj = QJsonObject();

    emit TcpMgr::GetInstance()->sig_send_meg(ID_TEXT_CHAT_MSG_REQ,arr);
}


void ChatPage::on_receive_btn_clicked()
{

}

