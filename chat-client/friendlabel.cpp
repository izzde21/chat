#include "friendlabel.h"
#include "ui_friendlabel.h"
#include"cilcklabel.h"
#include<QFontMetrics>
FriendLabel::FriendLabel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FriendLabel)
{
    ui->setupUi(this);
    ui->close_lb->setstatu("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    connect(ui->close_lb,&cilcklabel::clicked,this,&FriendLabel::slot_close);
}

FriendLabel::~FriendLabel()
{
    delete ui;
}

int FriendLabel::width(){
    return _width;
}

void FriendLabel::settext(QString text){
    _text=text;
    ui->tip_lb->setText(_text);
    ui->tip_lb->adjustSize();
    QFontMetrics font(ui->tip_lb->font());
    auto width=font.lineWidth();
    auto height=font.height();

    setFixedWidth(ui->close_lb->width()+ui->tip_lb->width()+10);
    setFixedHeight(height+15);

    _height=height;
    _width=width;
}

int FriendLabel::height(){
     return _height;
}

QString FriendLabel::text(){
    return _text;
}

void FriendLabel::slot_close(){
    emit sig_close(_text);
}
