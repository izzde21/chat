#ifndef GROUPTIPITEM_H
#define GROUPTIPITEM_H

#include <QWidget>
#include "listitme.h"
#include<QListWidgetItem>
namespace Ui {
class GroupTipItem;
}

class GroupTipItem : public Listitme
{
    Q_OBJECT

public:
    explicit GroupTipItem(QWidget *parent = nullptr);
    ~GroupTipItem();
    void settip(QString tip);
    QSize GetSize();
private:
    Ui::GroupTipItem *ui;
};

#endif // GROUPTIPITEM_H
