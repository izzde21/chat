/********************************************************************************
** Form generated from reading UI file 'grouptipitem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPTIPITEM_H
#define UI_GROUPTIPITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupTipItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *tip_lb;

    void setupUi(QWidget *GroupTipItem)
    {
        if (GroupTipItem->objectName().isEmpty())
            GroupTipItem->setObjectName("GroupTipItem");
        GroupTipItem->resize(400, 30);
        GroupTipItem->setMaximumSize(QSize(16777215, 30));
        horizontalLayout = new QHBoxLayout(GroupTipItem);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        tip_lb = new QLabel(GroupTipItem);
        tip_lb->setObjectName("tip_lb");

        horizontalLayout->addWidget(tip_lb);


        retranslateUi(GroupTipItem);

        QMetaObject::connectSlotsByName(GroupTipItem);
    } // setupUi

    void retranslateUi(QWidget *GroupTipItem)
    {
        GroupTipItem->setWindowTitle(QCoreApplication::translate("GroupTipItem", "Form", nullptr));
        tip_lb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GroupTipItem: public Ui_GroupTipItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPTIPITEM_H
