/********************************************************************************
** Form generated from reading UI file 'applyfriendpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLYFRIENDPAGE_H
#define UI_APPLYFRIENDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "applyfriendlist.h"

QT_BEGIN_NAMESPACE

class Ui_ApplyFriendPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *friend_apply_wid;
    QHBoxLayout *horizontalLayout;
    QLabel *friend_apply_lb;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    ApplyFriendList *apply_friend_list;

    void setupUi(QWidget *ApplyFriendPage)
    {
        if (ApplyFriendPage->objectName().isEmpty())
            ApplyFriendPage->setObjectName("ApplyFriendPage");
        ApplyFriendPage->resize(400, 300);
        verticalLayout = new QVBoxLayout(ApplyFriendPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        friend_apply_wid = new QWidget(ApplyFriendPage);
        friend_apply_wid->setObjectName("friend_apply_wid");
        friend_apply_wid->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(friend_apply_wid);
        horizontalLayout->setObjectName("horizontalLayout");
        friend_apply_lb = new QLabel(friend_apply_wid);
        friend_apply_lb->setObjectName("friend_apply_lb");
        friend_apply_lb->setMaximumSize(QSize(16777215, 40));

        horizontalLayout->addWidget(friend_apply_lb);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(friend_apply_wid);

        widget = new QWidget(ApplyFriendPage);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        apply_friend_list = new ApplyFriendList(widget);
        apply_friend_list->setObjectName("apply_friend_list");

        verticalLayout_2->addWidget(apply_friend_list);


        verticalLayout->addWidget(widget);


        retranslateUi(ApplyFriendPage);

        QMetaObject::connectSlotsByName(ApplyFriendPage);
    } // setupUi

    void retranslateUi(QWidget *ApplyFriendPage)
    {
        ApplyFriendPage->setWindowTitle(QCoreApplication::translate("ApplyFriendPage", "Form", nullptr));
        friend_apply_lb->setText(QCoreApplication::translate("ApplyFriendPage", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplyFriendPage: public Ui_ApplyFriendPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLYFRIENDPAGE_H
