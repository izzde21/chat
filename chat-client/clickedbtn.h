#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H

#include <QPushButton>
#include<QMouseEvent>
class Clickedbtn : public QPushButton
{
    Q_OBJECT
public:
    Clickedbtn(QWidget *parent = nullptr);
    ~Clickedbtn();
    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void SetStatu(QString normal,QString hover,QString press);
private:
    QString _normal;
    QString _hover;
    QString _press;
};

#endif // CLICKEDBTN_H
