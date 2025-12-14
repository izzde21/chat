#include "applyfrienditem.h"
#include "ui_applyfrienditem.h"
#include"global.h"
ApplyFriendItem::ApplyFriendItem(QWidget *parent)
    : Listitme(parent)
    , ui(new Ui::ApplyFriendItem)
{
    ui->setupUi(this);
    ShowBtn(false);
    seticontype(APPLY_FRIEND_ITEM);
    ui->add_btn2->SetStatu("normal","hover","press");

    connect(ui->add_btn2,&Clickedbtn::clicked,this,[this](){
        emit this->sig_auth_friend(_add_info);
    });
}

ApplyFriendItem::~ApplyFriendItem()
{
    delete ui;
}


void ApplyFriendItem::SetInfo(std::shared_ptr<ApplyInfo> add_info){
    _add_info=add_info;
    ui->user_name_lb->setText(_add_info->_name);
    ui->user_chat_lb->setText(_add_info->_desc);
    QPixmap pix(_add_info->_icon);
    pix=pix.scaled(ui->icon_lb->width(),ui->icon_lb->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->icon_lb->setScaledContents(true);
    ui->icon_lb->setPixmap(pix);

}

void ApplyFriendItem::ShowBtn(bool isshow){
    if (isshow) {
        ui->add_btn2->show();
        ui->already_add_lb->hide();
        _added = false;
    }
    else {
        ui->add_btn2->hide();
        ui->already_add_lb->show();
        _added = true;
    }
}

int ApplyFriendItem::GetUid(){
    return _add_info->_uid;
}
