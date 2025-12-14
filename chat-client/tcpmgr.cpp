#include "tcpmgr.h"
#include<QJsonDocument>
#include<QJsonObject>
#include"usermgr.h"
TcpMgr::TcpMgr():_host(""),_port(0),head_recv_fina(false),message_id(0),message_len(0),_buffer(0) {
    connect(&_socket,&QTcpSocket::connected,[&](){
        qDebug()<<"连接成功";
        emit sig_con_success(true);
    });


    connect(&_socket,&QTcpSocket::readyRead,[&](){
        _buffer.append(_socket.readAll());

        QDataStream out(&_buffer,QIODevice::ReadOnly);

        out.setVersion(QDataStream::Qt_6_9);
        forever
        {
            if(!head_recv_fina){
                //quint16 2个字节，强转成int适配_buffer.size()
                if(_buffer.size()<static_cast<int>(sizeof(quint16)*2)){
                    return;
                }

                out>>message_id>>message_len;
                qDebug()<<"message_id  is "<<message_id<<"   "<<"message_len is "<<message_len;
                _buffer=_buffer.mid(sizeof(quint16) * 2);
            }

            if(_buffer.size()<message_len){
                head_recv_fina=true;
                return;
            }
            head_recv_fina=false;
            QByteArray body=_buffer.mid(0,message_len);
            qDebug()<<"body is "<<body;
            _buffer=_buffer.mid(message_len);
            handleMsg(Repid(message_id),message_len,body);
        }
    });


    QObject::connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
        Q_UNUSED(socketError)
        qDebug() << "Error:" << _socket.errorString();
    });

    connect(&_socket,&QTcpSocket::disconnected,[](){
        qDebug()<<"Disconnected from server";
    });

    inithandlers();

    connect(this,&TcpMgr::sig_send_meg,this,&TcpMgr::slot_send_meg);
}
void TcpMgr::slot_tcp_con(SeverInfo si){
    _host=si.host;
    _port=static_cast<uint16_t>(si.port.toUInt());
    _socket.connectToHost(_host,_port);
}


void TcpMgr::slot_send_meg(Repid repid,QByteArray jsonstr){
    qDebug() << "jsonstr:" << jsonstr;
    qDebug() << "jsonstr as string:" << QString::fromUtf8(jsonstr);
    uint16_t id=repid;
    quint16 len=static_cast<quint16>(jsonstr.size());//返回字符数
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::BigEndian);
    qDebug()<<"len is"<<len;
    out<< id<<len;
    block.append(jsonstr);
    _socket.write(block);
}



void TcpMgr::inithandlers(){
    _handlers.insert(ID_CHAT_LOGIN_RSP,[this](Repid id,quint16 len,QByteArray data){
        Q_UNUSED(len);
        QJsonDocument jsondoc=QJsonDocument::fromJson(data);

        if(jsondoc.isNull()){
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsondoc.object();
        if(!jsonObj.contains("error")){
            int err=ERR_JSON;
            qDebug() << "Failed to json " <<ERR_JSON;
            emit sig_fail_login(err);
            return;
        }

        int error=jsonObj["error"].toInt();
        if(error!=SUCCESS){
            qDebug() << "Failed to json " <<error;
            emit sig_fail_login(error);
            return;
        }


        auto uid = jsonObj["uid"].toInt();
        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        auto desc = jsonObj["desc"].toString();
        auto user_info = std::make_shared<UserInfo>(uid, name, nick, icon, sex,"",desc);

        UserMgr::GetInstance()->setuserinfo(user_info);
        UserMgr::GetInstance()->Settoken(jsonObj["token"].toString());

        if(jsonObj.contains("apply_list")){
            qDebug() << "jsonObj.contains is true ";

            UserMgr::GetInstance()->AppendApplyList(jsonObj["apply_list"].toArray());
        }


        if(jsonObj.contains("friend_list")){
             qDebug() << "jsonObj.contains friend_list is true ";
            UserMgr::GetInstance()->AddFriendList(jsonObj["friend_list"].toArray());
        }

        qDebug() << "uid is  " <<uid<<"name is  " <<name;

        emit sig_swich_chatdlg();
    });


    _handlers.insert(ID_ADD_FRIEND_RSP, [this](Repid id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ERR_JSON;
            qDebug() << "Add Friend Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != SUCCESS) {
            qDebug() << "Add Friend Failed, err is " << err;
            return;
        }

        qDebug() << "Add Friend Success " ;
    });


    _handlers.insert(ID_SEARCH_USER_RSP,[this](Repid id,quint16 len,QByteArray data){
        QJsonDocument jsondoc=QJsonDocument::fromJson(data);
        if(jsondoc.isNull()){
            qDebug()<<"jsondoc.isNull";
            return;

        }

        QJsonObject obj=jsondoc.object();
        if(!obj.contains("error")){
             qDebug()<<"obj.contains";
            return;


        }

        auto error=obj["error"];
        if(error!=SUCCESS){
           qDebug()<<"SUCCESS";
            return;
        }
        auto si=std::make_shared<SearchInfo>(obj["uid"].toInt(),obj["name"].toString(),obj["nike"].toString(),
                                                       obj["desc"].toString(),obj["sex"].toInt(),obj["icon"].toString());

        emit sig_user_search(si);
    });

    _handlers.insert(ID_NOTIFY_ADD_FRIEND_REQ,[this](Repid id,quint16 len,QByteArray data){
        qDebug()<<"ID_NOTIFY_ADD_FRIEND_REQ";
        QJsonDocument jsondoc=QJsonDocument::fromJson(data);
        if(jsondoc.isNull()){
            qDebug()<<"jsondoc.isNull";
            return;

        }

        QJsonObject obj=jsondoc.object();
        if(!obj.contains("error")){
            qDebug()<<"obj.contains";
            return;


        }

        auto error=obj["error"];
        if(error!=SUCCESS){
            qDebug()<<"SUCCESS";
            return;
        }
        qDebug()<<"sig_friend_apply";
        auto name=obj["name"].toString();
        auto applyuid=obj["applyuid"].toInt();
        auto sex=obj["sex"].toInt();
        auto desc=obj["desc"].toString();
        auto icon=obj["icon"].toString();
        auto nike=obj["nike"].toString();
        auto apply_info=std::make_shared<AddFriendApply>(applyuid,name,desc,icon,nike,sex);
        emit sig_friend_apply(apply_info);
        qDebug() << "sig_friend_apply " ;
    });

    _handlers.insert(ID_AUTH_FRIEND_RSP,[this](Repid id,quint16 len,QByteArray data){
        qDebug()<<"ID_AUTH_FRIEND_RSP";
        QJsonDocument jsondoc=QJsonDocument::fromJson(data);
        if(jsondoc.isNull()){
            qDebug()<<"jsondoc.isNull";
            return;

        }

        QJsonObject obj=jsondoc.object();
        if(!obj.contains("error")){
            qDebug()<<"obj.contains";
            return;


        }

        auto error=obj["error"];
        if(error!=SUCCESS){
            qDebug()<<"SUCCESS";
            return;
        }
        auto name=obj["name"].toString();
        auto applyuid=obj["uid"].toInt();
        auto icon=obj["icon"].toString();
        auto sex=obj["sex"].toInt();
        auto nick=obj["nick"].toString();
        auto auth_rsp=std::make_shared<AuthRsp>(applyuid,name,nick,icon,sex);
        emit sig_auth_rsp(auth_rsp);
        qDebug() << "sig_auth_rsp " ;
    });

    _handlers.insert(ID_NOTIFY_AUTH_FRIEND_REQ,[this](Repid id,quint16 len,QByteArray data){
        qDebug()<<"ID_NOTIFY_ADD_FRIEND_REQ";
        QJsonDocument jsondoc=QJsonDocument::fromJson(data);
        if(jsondoc.isNull()){
            qDebug()<<"jsondoc.isNull";
            return;

        }

        QJsonObject obj=jsondoc.object();
        if(!obj.contains("error")){
            qDebug()<<"obj.contains";
            return;


        }

        auto error=obj["error"];
        if(error!=SUCCESS){
            qDebug()<<"SUCCESS";
            return;
        }
        auto name=obj["name"].toString();
        auto fromuid=obj["fromuid"].toInt();
        auto icon=obj["icon"].toString();
        auto nick=obj["nick"].toString();
        auto auth_info=std::make_shared<AuthInfo>(fromuid,name,nick,icon,0);
        emit sig_add_auth_friend(auth_info);
        qDebug() << "sig_add_auth_friend" ;
    });


    _handlers.insert(ID_TEXT_CHAT_MSG_RSP, [this](Repid id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ERR_JSON;
            qDebug() << "Chat Msg Rsp Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != SUCCESS) {
            qDebug() << "Chat Msg Rsp Failed, err is " << err;
            return;
        }

        qDebug() << "Receive Text Chat Rsp Success " ;
        //ui设置送达等标记 todo...
    });


    _handlers.insert(ID_NOTIFY_TEXT_CHAT_MSG_REQ, [this](Repid id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ERR_JSON;
            qDebug() << "Notify Chat Msg Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != SUCCESS) {
            qDebug() << "Notify Chat Msg Failed, err is " << err;
            return;
        }

        qDebug() << "Receive Text Chat Notify Success " ;
        auto msg_ptr = std::make_shared<TextChatMsg>(jsonObj["fromuid"].toInt(),
                                                     jsonObj["touid"].toInt(),jsonObj["text_array"].toArray());
        qDebug() << "fromuid is  " <<jsonObj["fromuid"].toInt();
        qDebug() << "uid is "<<jsonObj["touid"].toInt() ;
        emit sig_text_chat_msg(msg_ptr);
    });
}


void TcpMgr::handleMsg(Repid id, quint16 len, QByteArray data)
{
    auto itea=_handlers.find(id);
    if(itea==_handlers.end()){
        qDebug() << "No Found id is " <<id;
        return;
    }
    itea.value()(id,len,data);
}

TcpMgr::~TcpMgr()
{

}
