/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>
#include <statewidget.h>
#include "applyfriendpage.h"
#include "chatpage.h"
#include "chatuserlist.h"
#include "conuserlist.h"
#include "customizeedit.h"
#include "friendinfopage.h"
#include "searchlist.h"

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *side_bar;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *side_head;
    StateWidget *side_contact_lb;
    StateWidget *side_chat_lb;
    QSpacerItem *verticalSpacer;
    QWidget *chat_user_wid;
    QVBoxLayout *verticalLayout_3;
    QWidget *seach_wid;
    QHBoxLayout *horizontalLayout_2;
    CustomizeEdit *seach_edit;
    QSpacerItem *horizontalSpacer;
    Clickedbtn *add_btn;
    ChatUserList *chat_user_list;
    SearchList *search_list;
    ConUserList *con_user_list;
    QStackedWidget *stackedWidget;
    ChatPage *chat_page;
    FriendInfoPage *friend_info_page;
    ApplyFriendPage *friend_apply_page;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName("ChatDialog");
        ChatDialog->resize(580, 451);
        horizontalLayout = new QHBoxLayout(ChatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        side_bar = new QWidget(ChatDialog);
        side_bar->setObjectName("side_bar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(side_bar->sizePolicy().hasHeightForWidth());
        side_bar->setSizePolicy(sizePolicy);
        side_bar->setMinimumSize(QSize(50, 0));
        side_bar->setMaximumSize(QSize(50, 16777215));
        verticalLayout = new QVBoxLayout(side_bar);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(side_bar);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(8, 8, 6, 0);
        side_head = new QLabel(widget);
        side_head->setObjectName("side_head");
        side_head->setMinimumSize(QSize(35, 35));
        side_head->setMaximumSize(QSize(35, 35));
        side_head->setStyleSheet(QString::fromUtf8("border-radius: 17px;\n"
"\n"
""));
        side_head->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(side_head);

        side_contact_lb = new StateWidget(widget);
        side_contact_lb->setObjectName("side_contact_lb");
        side_contact_lb->setMinimumSize(QSize(30, 30));
        side_contact_lb->setMaximumSize(QSize(30, 30));

        verticalLayout_2->addWidget(side_contact_lb);

        side_chat_lb = new StateWidget(widget);
        side_chat_lb->setObjectName("side_chat_lb");
        side_chat_lb->setMinimumSize(QSize(30, 30));
        side_chat_lb->setMaximumSize(QSize(30, 30));

        verticalLayout_2->addWidget(side_chat_lb);

        side_contact_lb->raise();
        side_chat_lb->raise();
        side_head->raise();

        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(side_bar);

        chat_user_wid = new QWidget(ChatDialog);
        chat_user_wid->setObjectName("chat_user_wid");
        sizePolicy.setHeightForWidth(chat_user_wid->sizePolicy().hasHeightForWidth());
        chat_user_wid->setSizePolicy(sizePolicy);
        chat_user_wid->setMinimumSize(QSize(250, 0));
        chat_user_wid->setMaximumSize(QSize(250, 16777215));
        chat_user_wid->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(chat_user_wid);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        seach_wid = new QWidget(chat_user_wid);
        seach_wid->setObjectName("seach_wid");
        horizontalLayout_2 = new QHBoxLayout(seach_wid);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 5, 0, 3);
        seach_edit = new CustomizeEdit(seach_wid);
        seach_edit->setObjectName("seach_edit");
        seach_edit->setMinimumSize(QSize(200, 25));
        seach_edit->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(seach_edit);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        add_btn = new Clickedbtn(seach_wid);
        add_btn->setObjectName("add_btn");
        add_btn->setMinimumSize(QSize(25, 25));
        add_btn->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(add_btn);


        verticalLayout_3->addWidget(seach_wid);

        chat_user_list = new ChatUserList(chat_user_wid);
        chat_user_list->setObjectName("chat_user_list");

        verticalLayout_3->addWidget(chat_user_list);

        search_list = new SearchList(chat_user_wid);
        search_list->setObjectName("search_list");

        verticalLayout_3->addWidget(search_list);

        con_user_list = new ConUserList(chat_user_wid);
        con_user_list->setObjectName("con_user_list");

        verticalLayout_3->addWidget(con_user_list);


        horizontalLayout->addWidget(chat_user_wid);

        stackedWidget = new QStackedWidget(ChatDialog);
        stackedWidget->setObjectName("stackedWidget");
        chat_page = new ChatPage();
        chat_page->setObjectName("chat_page");
        stackedWidget->addWidget(chat_page);
        friend_info_page = new FriendInfoPage();
        friend_info_page->setObjectName("friend_info_page");
        stackedWidget->addWidget(friend_info_page);
        friend_apply_page = new ApplyFriendPage();
        friend_apply_page->setObjectName("friend_apply_page");
        stackedWidget->addWidget(friend_apply_page);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ChatDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Dialog", nullptr));
        side_head->setText(QString());
        add_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
