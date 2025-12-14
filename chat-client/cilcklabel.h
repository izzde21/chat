#ifndef CILCKLABEL_H
#define CILCKLABEL_H
#include"global.h"
#include <QLabel>
#include<QEnterEvent>
#include<QEvent>
class cilcklabel : public QLabel
{
    Q_OBJECT
public:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    cilcklabel(QWidget *parent=nullptr);
    void setstatu(QString normal="", QString hover="", QString press="",
                  QString select="", QString select_hover="", QString select_press="");
    ClickLbState GetState();
    bool SetCurState(ClickLbState state);
    void ResetNormalState();
private:
    QString normal_;
    QString normal_press;
    QString normal_hover;

    ClickLbState _curstate;
    QString select_;
    QString select_press_;
    QString select_hover_;
signals:
    void clicked(QString lbtext, ClickLbState state);
};


#endif // CILCKLABEL_H
