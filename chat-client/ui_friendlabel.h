/********************************************************************************
** Form generated from reading UI file 'friendlabel.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLABEL_H
#define UI_FRIENDLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "cilcklabel.h"

QT_BEGIN_NAMESPACE

class Ui_FriendLabel
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *close_wid;
    QHBoxLayout *horizontalLayout_2;
    QLabel *tip_lb;
    cilcklabel *close_lb;

    void setupUi(QWidget *FriendLabel)
    {
        if (FriendLabel->objectName().isEmpty())
            FriendLabel->setObjectName("FriendLabel");
        FriendLabel->resize(50, 37);
        FriendLabel->setMinimumSize(QSize(50, 0));
        FriendLabel->setMaximumSize(QSize(70, 16777215));
        horizontalLayout = new QHBoxLayout(FriendLabel);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        close_wid = new QWidget(FriendLabel);
        close_wid->setObjectName("close_wid");
        close_wid->setMinimumSize(QSize(0, 25));
        close_wid->setMaximumSize(QSize(60, 25));
        horizontalLayout_2 = new QHBoxLayout(close_wid);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tip_lb = new QLabel(close_wid);
        tip_lb->setObjectName("tip_lb");
        tip_lb->setMaximumSize(QSize(50, 30));

        horizontalLayout_2->addWidget(tip_lb);

        close_lb = new cilcklabel(close_wid);
        close_lb->setObjectName("close_lb");
        close_lb->setMinimumSize(QSize(25, 19));
        close_lb->setMaximumSize(QSize(15, 19));
        close_lb->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        close_lb->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        horizontalLayout_2->addWidget(close_lb);


        horizontalLayout->addWidget(close_wid);


        retranslateUi(FriendLabel);

        QMetaObject::connectSlotsByName(FriendLabel);
    } // setupUi

    void retranslateUi(QWidget *FriendLabel)
    {
        FriendLabel->setWindowTitle(QCoreApplication::translate("FriendLabel", "Form", nullptr));
        tip_lb->setText(QString());
        close_lb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendLabel: public Ui_FriendLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLABEL_H
