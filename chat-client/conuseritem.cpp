#include "conuseritem.h"
#include "ui_conuseritem.h"

ConUserItem::ConUserItem(QWidget *parent)
    : Listitme(parent)
    , ui(new Ui::ConUserItem)
{
    ui->setupUi(this);
    seticontype(CONTACT_USER_ITEM);
    ShowRidpoint(false);
    ui->red_point->raise();
}

QSize ConUserItem::Getsize(){
    return QSize(250,70);
}

void ConUserItem::SetInfo(std::shared_ptr<FriendInfo> friendinfo)
{
    auto info=std::make_shared<UserInfo>(friendinfo);
    user_info=info;
    ui->user_name_lb->setText(info->_name);

    QPixmap pix(info->_icon);
    pix=pix.scaled(ui->icon_lb->width(),ui->icon_lb->height(),Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->icon_lb->setScaledContents(true);
    ui->icon_lb->setPixmap(pix);
}

void ConUserItem::SetInfo(std::shared_ptr<AuthInfo> addly){
    auto info=std::make_shared<UserInfo>(addly);
    user_info=info;
    ui->user_name_lb->setText(info->_name);

    QPixmap pix(info->_icon);
    pix=pix.scaled(ui->icon_lb->width(),ui->icon_lb->height(),Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->icon_lb->setScaledContents(true);
    ui->icon_lb->setPixmap(pix);

}

void ConUserItem::SetInfo(std::shared_ptr<AuthRsp> addly){
    auto info=std::make_shared<UserInfo>(addly);
    user_info=info;
    ui->user_name_lb->setText(info->_name);

    QPixmap pix(info->_icon);
    pix=pix.scaled(ui->icon_lb->width(),ui->icon_lb->height(),Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->icon_lb->setScaledContents(true);
    ui->icon_lb->setPixmap(pix);
}


void ConUserItem::SetInfo(int uid,QString name,QString icon){
    user_info=std::make_shared<UserInfo>(uid,name, "", icon, 0, "", "");
    ui->user_name_lb->setText(name);
    QPixmap pix(icon);
    pix=pix.scaled(ui->icon_lb->width(),ui->icon_lb->height(),Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->icon_lb->setScaledContents(true);
    ui->icon_lb->setPixmap(pix);
}

void ConUserItem::ShowRidpoint(bool is){
    if(is==true){
        ui->red_point->show();
    }
    else{
        ui->red_point->hide();
    }
}

std::shared_ptr<UserInfo> ConUserItem::GetInfo()
{
    return user_info;
}

ConUserItem::~ConUserItem()
{
    delete ui;
}
