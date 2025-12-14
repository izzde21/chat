#include "listitme.h"
#include<QStyleOption>
#include<QPainter>
#include<QPaintEvent>
Listitme::Listitme(QWidget *parent):QWidget(parent){

}
void Listitme::seticontype(ListItemType icontype){
    _icontype=icontype;
}
ListItemType Listitme::Geticontype(){
    return _icontype;
}

/*void Listitme::paintEvent(QPaintEvent *event){
    QStyleOption op;
    op.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,&op,&painter,this);
}*/
