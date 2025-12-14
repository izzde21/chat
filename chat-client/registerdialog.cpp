#include "registerdialog.h"
#include "ui_registerdialog.h"
#include"global.h"
#include"httpmgr.h"
registerDialog::registerDialog(QWidget *parent)
    : QDialog(parent),count_(5)
    , ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    ui->pass_Edit->setEchoMode(QLineEdit::Password);
    ui->confrim_Edit->setEchoMode(QLineEdit::Password);
    setFixedSize(300,500);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,&registerDialog::slot_reg_mod_finish);
    ui->get_num_btn->setEnabled(false);
    initHttpHandles();
    ui->err_tip->clear();

    connect(ui->user_Edit,&QLineEdit::editingFinished,this,[this](){
        checkuser();
    });

    connect(ui->pass_Edit,&QLineEdit::editingFinished,this,[this](){
        checkpass();
    });

    connect(ui->confrim_Edit,&QLineEdit::editingFinished,this,[this](){
        checkconfrim();
    });

    connect(ui->email_Edit,&QLineEdit::editingFinished,this,[this](){
        checkemail();
    });

    connect(ui->num_Edit, &QLineEdit::editingFinished, this, [this](){
        checkVarify();
    });

    ui->pass_visible->setCursor(Qt::PointingHandCursor);
    ui->confirm_visible->setCursor(Qt::PointingHandCursor);
    ui->pass_visible->setstatu("unvisible","unvisible_hover","","visible",
                               "visible_hover","");
    ui->confirm_visible->setstatu("unvisible","unvisible_hover","","visible",
                               "visible_hover","");

    connect(ui->pass_visible,&cilcklabel::clicked,this,[this](){
        auto state = ui->pass_visible->GetState();
        if(state == ClickLbState::Normal){
            ui->pass_Edit->setEchoMode(QLineEdit::Password);
        }else{
            ui->pass_Edit->setEchoMode(QLineEdit::Normal);
        }
    });


    connect(ui->confirm_visible,&cilcklabel::clicked,this,[this](){
        auto state = ui->confirm_visible->GetState();
        if(state == ClickLbState::Normal){
            ui->confrim_Edit->setEchoMode(QLineEdit::Password);
        }else{
            ui->confrim_Edit->setEchoMode(QLineEdit::Normal);
        }
    });

    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[this](){
        if(count_<=0){
            timer->stop();
            count_=5;
            emit returnlogin();
        }
        count_--;
        auto str=QString("注册成功，%1 s后返回登录").arg(count_);
        ui->tip1->setText(str);
    });

}


void registerDialog::changepage(){
    timer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    timer->start(1000);
}

bool registerDialog::checkuser(){
    if(ui->user_Edit->text()==" "){
        AddErr(TIP_USER_ERR,"用户不能为空");
        return false;
    }
    DelErr(TIP_USER_ERR);
    return true;
}

bool registerDialog::checkpass(){
    auto pass=ui->pass_Edit->text();
    if(pass.length()< 5||pass.length()>15){
        AddErr(TIP_PWD_ERR,"密码长度为6-15");
        return false;
    }

    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        AddErr(TIP_PWD_ERR,"密码格式错误");
        return false;
    }

    DelErr(TipErr::TIP_PWD_ERR);
    return true;
}

bool registerDialog::checkconfrim(){
    auto confrim=ui->confrim_Edit->text();
    auto pass=ui->pass_Edit->text();
    if(confrim!=pass){
        AddErr(TIP_PWD_CONFIRM,"确认密码与密码不符");
        return false;
    }
    DelErr(TipErr::TIP_PWD_CONFIRM);
    return true;
}

bool registerDialog::checkemail(){
    auto email=ui->email_Edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+)))");
    bool match=regex.match(email).hasMatch();
    if(!match){
       AddErr(TIP_EMAIL_ERR,"邮箱格式错误");
        return false;
    }
    ui->get_num_btn->setEnabled(true);
    DelErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool registerDialog::checkVarify(){
    auto num=ui->num_Edit->text();
    if(num==""){
        ui->get_num_btn->setEnabled(false);
        AddErr(TIP_VARIFY_ERR,"验证码不能为空");
        return false;
    }
    DelErr(TipErr::TIP_VARIFY_ERR);
    return true;
}


void registerDialog::AddErr(TipErr err,QString str){
    err_map[err]=str;
    showTip(str,false);
}

void registerDialog::DelErr(TipErr err){
    err_map.remove(err);
    if(err_map.empty()){
        ui->err_tip->clear();
        return;
    }
    showTip(err_map.first(),false);
}


registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_get_num_btn_clicked()
{
    auto email=ui->email_Edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+)))");
    bool match=regex.match(email).hasMatch();

    if(match){
        //http服务器响应
        QJsonObject json_obj;
        json_obj["email"]=email;
        qDebug()<<gate_url_prefix+"/get_varifycode";
        HttpMgr::GetInstance()->PostHttpRep(QUrl(gate_url_prefix+"/get_varifycode"),  //向GateSever服务器发送请求
        json_obj,Repid::ID_GET_VARIFY_CODE,Moduls::REGISTERMOD);
    }else{
        showTip("邮箱地址不正确",false);
    }
}

void registerDialog::initHttpHandles(){
    //创建ID_GET_VARIFY_CODE(获取验证码)id和其回调函数
    _handles.insert(Repid::ID_GET_VARIFY_CODE,[this](const QJsonObject&jsonobj){
        int error=jsonobj["error"].toInt();       //把错误信息转成int传给error
        if(error!=SUCCESS){
            showTip(tr("参数错误"),false);
            qDebug()<<"error is:"<<error;
            return;
        }

        auto email=jsonobj["email"].toString();
        showTip(tr("验证码已发送到您的邮箱，注意查收"),true);
        qDebug()<<"email is:"<<email;
    });


    _handles.insert(Repid::ID_USER_REG,[this](const QJsonObject&jsonobj){
        int error=jsonobj["error"].toInt();       //把错误信息转成int传给error
        if(error!=SUCCESS){
            showTip(tr("参数错误"),false);
            qDebug()<<"error is:"<<error;
            return;
        }

        auto email=jsonobj["email"].toString();
        showTip(tr("用户注册成功"),true);
        qDebug()<<"email is:"<<email;
        changepage();
    });
}

void registerDialog::slot_reg_mod_finish(Repid id, QString res, Error error)
{
    if(error!=SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    QJsonDocument JsonDoc=QJsonDocument::fromJson(res.toUtf8());
    //它代表一个完整的JSON文档可以理解为JSON数据在内存中的结构化对象
    if(JsonDoc.isNull()){
        showTip(tr("Json解析错误"),false);
        return;
    }

    if(!JsonDoc.isObject()){
        showTip(tr("Json解析错误"),false);
        return;
    }
    _handles[id](JsonDoc.object());     //存到一个map中，根据id来回调对应的函数，函数参数是QJsonObject
}



void registerDialog::showTip(QString str,bool ok){

    if(ok){
        ui->err_tip->setProperty("state","normal");
    }
    else{
        ui->err_tip->setProperty("state","err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);

}

void registerDialog::on_confrim_btn_clicked()
{

    bool varify=checkuser();
    if(!varify){
        return;
    }
    varify=checkemail();
    if(!varify){
        return;
    }
    varify=checkpass();
    if(!varify){
        return;
    }
    varify=checkVarify();
    if(!varify){
        return;
    }


    QJsonObject Json_obj;
    Json_obj["user"]=ui->user_Edit->text();
    Json_obj["email"]=ui->email_Edit->text();
    Json_obj["pass"]=xorstring(ui->pass_Edit->text());
    Json_obj["confrim"]=xorstring(ui->confrim_Edit->text());
    Json_obj["varifycode"]=ui->num_Edit->text();
    qDebug()<<xorstring(ui->pass_Edit->text());
    HttpMgr::GetInstance()->PostHttpRep(QUrl(gate_url_prefix+"/user_register"),Json_obj,ID_USER_REG,REGISTERMOD);
}


void registerDialog::on_returnButton_clicked()
{
    timer->stop();
    emit returnlogin();
}


void registerDialog::on_cancel_btn_clicked()
{
    timer->stop();
    emit returnlogin();
}

