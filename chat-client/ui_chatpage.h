/********************************************************************************
** Form generated from reading UI file 'chatpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATPAGE_H
#define UI_CHATPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>
#include "chatview.h"
#include "cilcklabel.h"
#include "messagetextedit.h"

QT_BEGIN_NAMESPACE

class Ui_ChatPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *chat_data_wid;
    QVBoxLayout *verticalLayout_4;
    QWidget *titel_wid;
    QVBoxLayout *verticalLayout_5;
    QWidget *wiget_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *title_lb;
    ChatView *chat_data_list;
    QVBoxLayout *verticalLayout_3;
    QWidget *tool_wid;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    cilcklabel *emo_lb;
    QSpacerItem *horizontalSpacer_4;
    cilcklabel *file_lb;
    QSpacerItem *horizontalSpacer_3;
    MessageTextEdit *chat_edit;
    QWidget *rece_and_sendwig;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    Clickedbtn *receive_btn;
    QSpacerItem *horizontalSpacer_6;
    Clickedbtn *send_btn;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QWidget *ChatPage)
    {
        if (ChatPage->objectName().isEmpty())
            ChatPage->setObjectName("ChatPage");
        ChatPage->resize(408, 540);
        verticalLayout = new QVBoxLayout(ChatPage);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        chat_data_wid = new QWidget(ChatPage);
        chat_data_wid->setObjectName("chat_data_wid");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chat_data_wid->sizePolicy().hasHeightForWidth());
        chat_data_wid->setSizePolicy(sizePolicy);
        chat_data_wid->setMinimumSize(QSize(400, 0));
        chat_data_wid->setMaximumSize(QSize(400, 16777215));
        verticalLayout_4 = new QVBoxLayout(chat_data_wid);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        verticalLayout_4->setContentsMargins(0, 4, 0, 0);
        titel_wid = new QWidget(chat_data_wid);
        titel_wid->setObjectName("titel_wid");
        titel_wid->setMinimumSize(QSize(0, 30));
        titel_wid->setMaximumSize(QSize(16777215, 60));
        verticalLayout_5 = new QVBoxLayout(titel_wid);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(8, 0, 2, 2);
        wiget_2 = new QWidget(titel_wid);
        wiget_2->setObjectName("wiget_2");
        wiget_2->setSizeIncrement(QSize(0, 0));
        verticalLayout_6 = new QVBoxLayout(wiget_2);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(2, 0, 2, 2);
        title_lb = new QLabel(wiget_2);
        title_lb->setObjectName("title_lb");
        title_lb->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_6->addWidget(title_lb);


        verticalLayout_5->addWidget(wiget_2);


        verticalLayout_4->addWidget(titel_wid);

        chat_data_list = new ChatView(chat_data_wid);
        chat_data_list->setObjectName("chat_data_list");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chat_data_list->sizePolicy().hasHeightForWidth());
        chat_data_list->setSizePolicy(sizePolicy1);
        chat_data_list->setMinimumSize(QSize(0, 250));
        chat_data_list->setMaximumSize(QSize(16777215, 530));
        chat_data_list->setSizeIncrement(QSize(0, 1));
        verticalLayout_3 = new QVBoxLayout(chat_data_list);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);

        verticalLayout_4->addWidget(chat_data_list);

        tool_wid = new QWidget(chat_data_wid);
        tool_wid->setObjectName("tool_wid");
        tool_wid->setMinimumSize(QSize(0, 30));
        tool_wid->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(tool_wid);
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(1, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        emo_lb = new cilcklabel(tool_wid);
        emo_lb->setObjectName("emo_lb");
        emo_lb->setMinimumSize(QSize(25, 25));
        emo_lb->setMaximumSize(QSize(25, 25));

        horizontalLayout_3->addWidget(emo_lb);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        file_lb = new cilcklabel(tool_wid);
        file_lb->setObjectName("file_lb");
        file_lb->setMinimumSize(QSize(25, 25));
        file_lb->setMaximumSize(QSize(25, 25));

        horizontalLayout_3->addWidget(file_lb);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_4->addWidget(tool_wid);

        chat_edit = new MessageTextEdit(chat_data_wid);
        chat_edit->setObjectName("chat_edit");
        chat_edit->setMinimumSize(QSize(0, 150));
        chat_edit->setMaximumSize(QSize(16777215, 150));
        chat_edit->setSizeIncrement(QSize(150, 100));

        verticalLayout_4->addWidget(chat_edit);

        rece_and_sendwig = new QWidget(chat_data_wid);
        rece_and_sendwig->setObjectName("rece_and_sendwig");
        rece_and_sendwig->setMaximumSize(QSize(16777215, 40));
        rece_and_sendwig->setSizeIncrement(QSize(0, 40));
        horizontalLayout_4 = new QHBoxLayout(rece_and_sendwig);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 2, 0, 10);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        receive_btn = new Clickedbtn(rece_and_sendwig);
        receive_btn->setObjectName("receive_btn");
        receive_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(receive_btn);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        send_btn = new Clickedbtn(rece_and_sendwig);
        send_btn->setObjectName("send_btn");
        send_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(send_btn);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        verticalLayout_4->addWidget(rece_and_sendwig);


        verticalLayout->addWidget(chat_data_wid);


        retranslateUi(ChatPage);

        QMetaObject::connectSlotsByName(ChatPage);
    } // setupUi

    void retranslateUi(QWidget *ChatPage)
    {
        ChatPage->setWindowTitle(QCoreApplication::translate("ChatPage", "Form", nullptr));
        title_lb->setText(QCoreApplication::translate("ChatPage", "\344\272\232\347\264\242", nullptr));
        emo_lb->setText(QString());
        file_lb->setText(QString());
        receive_btn->setText(QCoreApplication::translate("ChatPage", "\346\216\245\346\224\266", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatPage", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatPage: public Ui_ChatPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATPAGE_H
