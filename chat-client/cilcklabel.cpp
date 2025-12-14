#include "cilcklabel.h"

void cilcklabel::mousePressEvent(QMouseEvent *ev){
    if(ev->button()==Qt::LeftButton){
        if(_curstate==Normal){
            _curstate = ClickLbState::Selected;
            this->setProperty("state",select_press_);
            repolish(this);
            update();
        }else{
            _curstate = ClickLbState::Normal;
            this->setProperty("state",normal_press);
            repolish(this);
            update();
        }
        return;
    }
    QLabel::mousePressEvent(ev);
}

void cilcklabel::mouseReleaseEvent(QMouseEvent *ev){
    if(ev->button()==Qt::LeftButton){
        if(_curstate==Normal){
            this->setProperty("state",normal_hover);
            repolish(this);
            update();
        }
        else{
            this->setProperty("state",select_hover_);
            repolish(this);
            update();
        }
        emit clicked(this->text(),_curstate);
    }
    QLabel::mouseReleaseEvent(ev);
}

void cilcklabel::enterEvent(QEnterEvent *event) {
    if(_curstate==Normal){
        this->setProperty("state",normal_hover);
        repolish(this);
        update();
    }else{
        this->setProperty("state",select_hover_);
        repolish(this);
        update();
    }
     QLabel::enterEvent(event);
}
void cilcklabel::leaveEvent(QEvent *event) {
    if(_curstate==Normal){
        this->setProperty("state",normal_);
        repolish(this);
        update();
    }else{
        this->setProperty("state",select_);
        repolish(this);
        update();
    }
    QLabel::leaveEvent(event);
}
cilcklabel::cilcklabel(QWidget *parent):QLabel(parent),_curstate(Normal){

}
void cilcklabel::setstatu(QString normal, QString hover, QString press,
                                QString select, QString select_hover, QString select_press){
    normal_ = normal;
    normal_hover = hover;
    normal_press = press;
    select_ = select;
    select_hover_ = select_hover;
    select_press_ = select_press;
    setProperty("state",normal);
    repolish(this);
}
ClickLbState cilcklabel::GetState(){
    return _curstate;
}
bool cilcklabel::SetCurState(ClickLbState state)
{
    _curstate = state;
    if (_curstate == ClickLbState::Normal) {
        setProperty("state", normal_);
        repolish(this);
    }
    else if (_curstate == ClickLbState::Selected) {
        setProperty("state", select_);
        repolish(this);
    }

    return true;
}


void cilcklabel::ResetNormalState()
{
    _curstate = ClickLbState::Normal;
    setProperty("state", normal_);
    repolish(this);
}
