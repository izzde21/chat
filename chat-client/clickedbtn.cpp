#include "clickedbtn.h"
#include"global.h"
#include<QEvent>
Clickedbtn::Clickedbtn(QWidget *parent):QPushButton(parent){
    setCursor(Qt::PointingHandCursor);
}

Clickedbtn::~Clickedbtn(){

}

void Clickedbtn::enterEvent(QEnterEvent *event){
    setProperty("state",_hover);
    repolish(this);
    update();
    QPushButton::enterEvent(event);
}

void Clickedbtn::leaveEvent(QEvent *event){
    setProperty("state",_normal);
    repolish(this);
    update();
    QPushButton::leaveEvent(event);
}

void Clickedbtn::mousePressEvent(QMouseEvent *event){
    setProperty("state",_press);
    repolish(this);
    update();
    QPushButton::mousePressEvent(event);
}

void Clickedbtn::mouseReleaseEvent(QMouseEvent *event){
    setProperty("state",_hover);
    repolish(this);
    update();
    QPushButton::mouseReleaseEvent(event);
}

void Clickedbtn::SetStatu(QString normal,QString hover,QString press){
    _normal=normal;
    _hover=hover;
    _press=press;
    setProperty("state","normal");
    repolish(this);
    update();
}
