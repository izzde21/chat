#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H

#include <QLineEdit>

class CustomizeEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomizeEdit(QWidget *parent = nullptr);
    ~CustomizeEdit();
    virtual void focusOutEvent(QFocusEvent *event);
    void setmaxlen(int maxlen);
signals:
    void sig_fous_out();
private:
    int max_len;
    void limitTextLength(QString text);
};

#endif // CUSTOMIZEEDIT_H
