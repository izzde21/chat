#include "logindialog.h"
#include "ui_logindialog.h"
#include<QPainter>
#include<QPixmap>
#include<QPainterPath>
#include<QJsonObject>
#include"httpmgr.h"
#include"TcpMgr.h"
loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    connect(ui->regie_btn,&QPushButton::clicked,this,&loginDialog::switchRegister);
    setFixedSize(300,500);
    connect(ui->forget_label,&cilcklabel::clicked,this,&loginDialog::sigwsitchfordig);
    ui->forget_label->setCursor(Qt::PointingHandCursor);
    ui->forget_label->setstatu("normal","hover","","selected","selected_hover","");
    ui->pass_Edit->setEchoMode(QLineEdit::Password);
    showTip("    ",false);
    connect(ui->email_Edit,&QLineEdit::editingFinished,this,[this](){
        checknuer();
    });

    connect(ui->pass_Edit,&QLineEdit::editingFinished,this,[this](){
        checkpass();
    });

    connect(this,&loginDialog::sig_tcp_con,TcpMgr::GetInstance().get(),&TcpMgr::slot_tcp_con);//tcp连接
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_con_success,this,&loginDialog::slot_con_final);//tcp连接成功
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_fail_login,this,&loginDialog::slot_fail_login);//tcp连接失败

    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_login_mod_finish,this,&loginDialog::slot_login_mod_finish);
    init();
    inithandle();
}

void loginDialog::inithandle(){
    _handle.insert(ID_LOGIN_USER,[this](const QJsonObject&jsonobj){
        auto error=jsonobj["error"];
        if(error!=SUCCESS){
            qDebug()<<"参数错误";
            showTip(tr("参数错误"), false);
            enablebtn(true);
            return;

        }
        SeverInfo si;
        si.uid = jsonobj["uid"].toInt();
        si.host = jsonobj["host"].toString();
        si.token=jsonobj["token"].toString();
        si.port=jsonobj["port"].toString();

        std::shared_ptr<UserInfo> userinfo;

        _token=si.token;
        _uid=si.uid;
        showTip(tr("登录成功"), true);
        enablebtn(true);

        emit sig_tcp_con(si);
    });

}

void loginDialog::enablebtn(bool can){
    ui->login_btn->setEnabled(can);
    ui->regie_btn->setEnabled(can);
}


loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::init(){
    QPixmap pixmap(":/res/login.png");
    pixmap=pixmap.scaled(284,309,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QPixmap roundpixmap(pixmap.size());
    roundpixmap.fill(Qt::transparent);

    QPainter painter(&roundpixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(0,0,roundpixmap.width(),roundpixmap.height(),10,10);
    painter.setClipPath(path);

    painter.drawPixmap(0,0,pixmap);
    ui->head_pic->setPixmap(roundpixmap);
}

void loginDialog::Adderrmap(TipErr err,QString str){
    err_map[err]=str;
    showTip(str,false);
}


void loginDialog::delerrmap(TipErr err){
    err_map.remove(err);
    if(err_map.empty()){
        ui->err_tip->clear();
        return;
    }
    showTip(err_map.first(),false);
}

bool loginDialog::checkpass(){
    auto pass=ui->pass_Edit->text();
    if(pass.length()<6||pass.length()>15){
        Adderrmap(TIP_PWD_ERR,"密码格式错误");
        return false;
    }
    delerrmap(TIP_PWD_ERR);
    return true;
}

bool loginDialog::checknuer(){
    auto email=ui->email_Edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+)))");
    bool match=regex.match(email).hasMatch();
    if(!match){
        Adderrmap(TIP_EMAIL_ERR,"邮箱格式错误");
        return false;
    }
    delerrmap(TipErr::TIP_EMAIL_ERR);
    return true;
}

void loginDialog::showTip(QString str,bool ok){

    if(ok){
        ui->err_tip->setProperty("state","normal");
    }
    else{
        ui->err_tip->setProperty("state","err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}


void loginDialog::slot_login_mod_finish(Repid id, QString res, Error error){
    if(error!=SUCCESS){
        showTip("网络请求错误",false);
        qDebug()<<"error!=SUCCESS";
        enablebtn(true);
        return;

    }

    QJsonDocument jsondoc=QJsonDocument::fromJson(res.toUtf8());
    if(!jsondoc.isObject()){
        showTip("JSON解析错误",false);
        qDebug()<<"error!=SUCCESS";
        enablebtn(true);
        return;
    }

    if(jsondoc.isNull()){
        showTip("JSON解析错误",false);
        enablebtn(true);
        return;
    }
    _handle[id](jsondoc.object());
}


void loginDialog::slot_con_final(bool is){
    if(is){
        showTip("聊天服务连接成功，正在登录...",true);
        QJsonObject jsonobj;
        jsonobj["token"]=_token;
        jsonobj["uid"]=_uid;

        QJsonDocument doc(jsonobj);
        QByteArray jsonstr=doc.toJson(QJsonDocument::Indented);

        emit TcpMgr::GetInstance()->sig_send_meg(ID_CHAT_LOGIN,jsonstr);
    }
    else{
        showTip("网络异常",false);
        enablebtn(true);
        return;
    }
}

void loginDialog::slot_fail_login(int err){
    QString result = QString("登录失败, err is %1").arg(err);
    showTip(result,false);
    enablebtn(true);
}






void loginDialog::on_login_btn_clicked()
{
    bool vaify=checknuer();
    if(!vaify){
        return;
    }
    vaify=checkpass();
    if(!vaify){
        return;
    }
    enablebtn(false);
    QJsonObject jsonobj;
    jsonobj["email"]=ui->email_Edit->text();
    jsonobj["pass"]=xorstring(ui->pass_Edit->text());
    //发送用户登录请求
    HttpMgr::GetInstance()->PostHttpRep(QUrl(gate_url_prefix+"/user_login"),jsonobj,ID_LOGIN_USER,LOGINMOD);
}

