/********************************************************************************
** Form generated from reading UI file 'conuseritem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONUSERITEM_H
#define UI_CONUSERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConUserItem
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLabel *icon_lb;
    QLabel *red_point;
    QLabel *user_name_lb;

    void setupUi(QWidget *ConUserItem)
    {
        if (ConUserItem->objectName().isEmpty())
            ConUserItem->setObjectName("ConUserItem");
        ConUserItem->resize(400, 70);
        ConUserItem->setMinimumSize(QSize(0, 70));
        ConUserItem->setMaximumSize(QSize(16777215, 72));
        horizontalLayout = new QHBoxLayout(ConUserItem);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(3, 4, 3, 4);
        widget = new QWidget(ConUserItem);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 60));
        widget->setMaximumSize(QSize(60, 60));
        icon_lb = new QLabel(widget);
        icon_lb->setObjectName("icon_lb");
        icon_lb->setGeometry(QRect(7, 8, 60, 50));
        icon_lb->setMinimumSize(QSize(50, 50));
        icon_lb->setMaximumSize(QSize(50, 50));
        icon_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);
        red_point = new QLabel(widget);
        red_point->setObjectName("red_point");
        red_point->setGeometry(QRect(40, 10, 15, 15));
        red_point->setMinimumSize(QSize(15, 15));
        red_point->setMaximumSize(QSize(15, 15));
        red_point->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(widget);

        user_name_lb = new QLabel(ConUserItem);
        user_name_lb->setObjectName("user_name_lb");

        horizontalLayout->addWidget(user_name_lb);


        retranslateUi(ConUserItem);

        QMetaObject::connectSlotsByName(ConUserItem);
    } // setupUi

    void retranslateUi(QWidget *ConUserItem)
    {
        ConUserItem->setWindowTitle(QCoreApplication::translate("ConUserItem", "Form", nullptr));
        icon_lb->setText(QString());
        red_point->setText(QString());
        user_name_lb->setText(QCoreApplication::translate("ConUserItem", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConUserItem: public Ui_ConUserItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONUSERITEM_H
