#ifndef TCPMGR_H
#define TCPMGR_H
#include<QTcpSocket>
#include"Singelton.h"
#include "global.h"
#include<QMap>
#include <functional>
#include"userdata.h"
class TcpMgr:public QObject ,public Singelton<TcpMgr>,public std::enable_shared_from_this<TcpMgr>
{
    friend class Singelton<TcpMgr>;
    Q_OBJECT
public:
    ~TcpMgr();
private:
    TcpMgr();
    uint16_t _port;
    QString _host;
    quint16 message_id;
    quint16 message_len;
    bool head_recv_fina;
    QTcpSocket _socket;
    QByteArray _buffer;
    QMap<Repid,std::function<void(Repid id,quint16 len,QByteArray data)>> _handlers;
    void inithandlers();
    void handleMsg(Repid id,quint16 len,QByteArray data);
signals:
    void sig_fail_login(int err);
    void sig_con_success(bool issueccess);
    void sig_send_meg(Repid id,QByteArray jsonstr);
    void sig_swich_chatdlg();
    void sig_user_search(std::shared_ptr<SearchInfo>);
    void sig_friend_apply(std::shared_ptr<AddFriendApply>);
    void sig_auth_rsp(std::shared_ptr<AuthRsp>);
    void sig_add_auth_friend(std::shared_ptr<AuthInfo>);
    void sig_text_chat_msg(std::shared_ptr<TextChatMsg>);
public slots:
    void slot_tcp_con(SeverInfo si);
    void slot_send_meg(Repid,QByteArray jsonstr);

};

#endif // TCPMGR_H
