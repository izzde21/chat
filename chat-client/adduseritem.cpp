#include "adduseritem.h"
#include "ui_adduseritem.h"
AddUserItem::AddUserItem(QWidget *parent)
    : Listitme(parent)
    , ui(new Ui::AddUserItem)
{
    ui->setupUi(this);
    seticontype(ListItemType::ADD_USER_TIP_ITEM);
}

AddUserItem::~AddUserItem()
{
    delete ui;
}
