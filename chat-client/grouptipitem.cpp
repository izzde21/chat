#include "grouptipitem.h"
#include "ui_grouptipitem.h"

GroupTipItem::GroupTipItem(QWidget *parent)
    : Listitme(parent)
    , ui(new Ui::GroupTipItem)
{
    ui->setupUi(this);
    seticontype(GROUP_TIP_ITEM);

}

GroupTipItem::~GroupTipItem()
{
    delete ui;
}

void GroupTipItem::settip(QString tip)
{
    ui->tip_lb->setText(tip);
}

QSize GroupTipItem::GetSize()
{
    return QSize(250,70);
}
