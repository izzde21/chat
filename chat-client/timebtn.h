#ifndef TIMEBTN_H
#define TIMEBTN_H
#include<QTimer>
#include <QPushButton>

class TimeBtn : public QPushButton
{
public:
    TimeBtn(QWidget *parent = nullptr);
    ~TimeBtn();
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QTimer * timer;
    int count_;
};

#endif // TIMEBTN_H
