#include "findsuccessdlg.h"
#include "ui_findsuccessdlg.h"
#include<QDir>
#include "addfriend.h"
FindSuccessDlg::FindSuccessDlg(QWidget *parent)
    : QDialog(parent),_parent(parent)
    , ui(new Ui::FindSuccessDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("添加");
    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    QString app_path = QCoreApplication::applicationDirPath();
    QString pix_path = QDir::toNativeSeparators(app_path +
                                                QDir::separator() + "static"+QDir::separator()+"OIP-C.jpg");

    QPixmap pix(pix_path);
    pix=pix.scaled(ui->head_lb->width(),ui->head_lb->height());
    ui->head_lb->setPixmap(pix);
    ui->add_friend_btn->SetStatu("normal","hover","press");
    this->setModal(true);
}

FindSuccessDlg::~FindSuccessDlg()
{
    delete ui;
}

void FindSuccessDlg::SetSearchInfo(std::shared_ptr<SearchInfo> si){

    ui->name_lb->setText(si->_name);
    _si=si;
}

void FindSuccessDlg::on_add_friend_btn_clicked()
{
    this->hide();
    //弹出加好友界面
    auto applyFriend = new AddFriend(_parent);
    applyFriend->SetSearchInfo(_si);
    applyFriend->setModal(true);
    applyFriend->show();
}

