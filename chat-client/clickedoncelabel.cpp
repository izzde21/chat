#include "clickedoncelabel.h"
#include<QMouseEvent>
ClickedOnceLabel::ClickedOnceLabel(QWidget *parent):QLabel(parent){
    setCursor(Qt::PointingHandCursor);
}
void ClickedOnceLabel::mousePressEvent(QMouseEvent *ev){
    if(ev->button()==Qt::LeftButton){
        emit clicked(this->text());
        return;
    }
    QLabel::mousePressEvent(ev);
}
