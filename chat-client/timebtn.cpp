#include "timebtn.h"
#include<QMouseEvent>
TimeBtn::TimeBtn(QWidget *parent):QPushButton(parent),count_(10){
    this->setStyleSheet("QPushButton:disabled { color: gray; }");
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[this](){
        count_--;
        if(count_<=0){
            count_=10;
            timer->stop();
            this->setText("获取验证码");
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(count_));
    });
}


TimeBtn::~TimeBtn(){
    timer->stop();
}


void TimeBtn::mouseReleaseEvent(QMouseEvent *e){
    if(e->button()==Qt::LeftButton){
        this->setEnabled(false);
        timer->start(1000);
        this->setText(QString::number(count_));


        emit clicked();
    }
    QPushButton::mouseReleaseEvent(e);
}
