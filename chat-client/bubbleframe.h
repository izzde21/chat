#ifndef BUBBLEFRAME_H
#define BUBBLEFRAME_H

#include <QFrame>
#include<QHBoxLayout>
#include"global.h"
class BubbleFrame : public QFrame
{
    Q_OBJECT
public:
    void setWidget(QWidget *w);
    BubbleFrame(ChatRole role,QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *) override;
private:
    int m_margin;
    QHBoxLayout *m_pHLayout;
    ChatRole m_role;
};

#endif // BUBBLEFRAME_H
