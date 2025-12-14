#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QObject>
#include "Singelton.h"
#include "QUrl"
#include"QString"
#include"QNetworkAccessManager"
#include"QJsonObject"
#include"QJsonDocument"
#include"QNetworkReply"
class HttpMgr:public QObject,public Singelton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpRep(QUrl url,QJsonObject Json,Repid id,Moduls moduls);  //发送请求
private:
    friend class Singelton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
private slots:
    void slot_http_finish(Repid id,QString res,Error error,Moduls moduls);//发送请求完成后触发
signals:
    void sig_http_finish(Repid id,QString res,Error error,Moduls moduls);//发送请求完成
    void sig_reg_mod_finish(Repid id,QString res,Error error);
    void sig_reset_mod_finish(Repid id,QString res,Error error);
    void sig_login_mod_finish(Repid id,QString res,Error error);
};

#endif // HTTPMGR_H
