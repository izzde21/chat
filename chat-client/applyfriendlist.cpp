#include "applyfriendlist.h"
#include<QScrollArea>
#include<QMouseEvent>
#include<QEvent>
#include<QWheelEvent>
#include<QScrollBar>
ApplyFriendList::ApplyFriendList(QWidget *parent):QListWidget(parent){
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);
}

bool ApplyFriendList::eventFilter(QObject *object, QEvent *event){
    if(object==this->viewport()){
        if(event->type()==QMouseEvent::Enter){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }
        if(event->type()==QMouseEvent::Leave){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    if(object==this->viewport()){
        if(event->type()== QEvent::MouseButtonPress){
            emit sig_show_search(false);
        }
    }

    if(object==this->viewport() && event->type()==QEvent::Wheel){
        auto wheel=static_cast<QWheelEvent*>(event);
        int numdegger=wheel->angleDelta().y()/15;
        int steps=numdegger/8;

        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - steps);
        return true;
    }
    return QListWidget::eventFilter(object,event);
}
