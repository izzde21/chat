#include "customizeedit.h"

CustomizeEdit::CustomizeEdit(QWidget *parent):QLineEdit(parent) {
    connect(this, &QLineEdit::textChanged, this, &CustomizeEdit::limitTextLength);
}

CustomizeEdit::~CustomizeEdit(){

}

void CustomizeEdit::setmaxlen(int maxlen){
    max_len=maxlen;
}

void CustomizeEdit::focusOutEvent(QFocusEvent *event){
    QLineEdit::focusOutEvent(event);
    emit sig_fous_out();
}

void CustomizeEdit::limitTextLength(QString text){
    if(max_len<=0){
        return;
    }
    QByteArray bytearray=text.toUtf8();

    if(bytearray.size()>max_len){
        bytearray=bytearray.left(max_len);
        this->setText(QString::fromUtf8(bytearray));
    }
}
