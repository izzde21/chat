#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr() {
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpRep(QUrl url, QJsonObject Json, Repid id, Moduls moduls)
{
    QByteArray data=QJsonDocument(Json).toJson();   //自动处理大端序小端序问题
    QNetworkRequest request(url);                   //url是http头部的域名，必须要设置域名
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");   //声明请求体的数据格式为 JSON
    request.setHeader(QNetworkRequest::ContentLengthHeader,data.length());      //声明请求体的字节长度（这里是 data 的二进制大小）
    auto self=shared_from_this();

    QNetworkReply *reply=_manager.post(request,data);       //发送请求

    //处理HTTP请求完成后的响应结果，reply是一个结果
    QObject::connect(reply, &QNetworkReply::finished,[self,reply,id,moduls](){
        //请求失败
        if(reply->error()!=QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            emit self->sig_http_finish(id,"",Error::ERR_NETWORK,moduls);
            return;
        }//请求成功
        else{
            QString res=reply->readAll();
            emit self->sig_http_finish(id,res,Error::SUCCESS,moduls);//发送请求完成
            reply->deleteLater();
            return;
        }
    });
}

void HttpMgr::slot_http_finish(Repid id, QString res, Error error, Moduls moduls)
{
    //注册模块
    if(moduls==REGISTERMOD){
        emit sig_reg_mod_finish(id,  res,  error);
    }

    if(moduls==RESETMOD){
        emit sig_reset_mod_finish(id,  res, error);
    }

    if(moduls==LOGINMOD){
        emit sig_login_mod_finish(id,  res, error);
    }
}
