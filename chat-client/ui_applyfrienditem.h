/********************************************************************************
** Form generated from reading UI file 'applyfrienditem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLYFRIENDITEM_H
#define UI_APPLYFRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>

QT_BEGIN_NAMESPACE

class Ui_ApplyFriendItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *icon_lb;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *user_name_lb;
    QLabel *user_chat_lb;
    Clickedbtn *add_btn2;
    QLabel *already_add_lb;

    void setupUi(QWidget *ApplyFriendItem)
    {
        if (ApplyFriendItem->objectName().isEmpty())
            ApplyFriendItem->setObjectName("ApplyFriendItem");
        ApplyFriendItem->resize(400, 52);
        ApplyFriendItem->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(ApplyFriendItem);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(4, 5, 4, 2);
        icon_lb = new QLabel(ApplyFriendItem);
        icon_lb->setObjectName("icon_lb");
        icon_lb->setMinimumSize(QSize(45, 45));
        icon_lb->setMaximumSize(QSize(45, 45));
        icon_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(icon_lb);

        widget = new QWidget(ApplyFriendItem);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 15, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMaximumSize(QSize(16777215, 50));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 0, -1, 2);
        user_name_lb = new QLabel(widget_2);
        user_name_lb->setObjectName("user_name_lb");
        user_name_lb->setMinimumSize(QSize(0, 30));
        user_name_lb->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(user_name_lb);

        user_chat_lb = new QLabel(widget_2);
        user_chat_lb->setObjectName("user_chat_lb");
        user_chat_lb->setMinimumSize(QSize(0, 30));
        user_chat_lb->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(user_chat_lb);


        horizontalLayout_2->addWidget(widget_2);

        add_btn2 = new Clickedbtn(widget);
        add_btn2->setObjectName("add_btn2");
        add_btn2->setMaximumSize(QSize(120, 30));

        horizontalLayout_2->addWidget(add_btn2);

        already_add_lb = new QLabel(widget);
        already_add_lb->setObjectName("already_add_lb");
        already_add_lb->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(already_add_lb);


        horizontalLayout->addWidget(widget);


        retranslateUi(ApplyFriendItem);

        QMetaObject::connectSlotsByName(ApplyFriendItem);
    } // setupUi

    void retranslateUi(QWidget *ApplyFriendItem)
    {
        ApplyFriendItem->setWindowTitle(QCoreApplication::translate("ApplyFriendItem", "Form", nullptr));
        icon_lb->setText(QCoreApplication::translate("ApplyFriendItem", "TextLabel", nullptr));
        user_name_lb->setText(QCoreApplication::translate("ApplyFriendItem", "TextLabel", nullptr));
        user_chat_lb->setText(QCoreApplication::translate("ApplyFriendItem", "TextLabel", nullptr));
        add_btn2->setText(QCoreApplication::translate("ApplyFriendItem", "\346\267\273\345\212\240", nullptr));
        already_add_lb->setText(QCoreApplication::translate("ApplyFriendItem", "\345\267\262\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplyFriendItem: public Ui_ApplyFriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLYFRIENDITEM_H
