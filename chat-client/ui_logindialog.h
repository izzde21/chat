/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "cilcklabel.h"

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *err_tip;
    QLabel *head_pic;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *enail_label;
    QLineEdit *email_Edit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pass_label;
    QLineEdit *pass_Edit;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    cilcklabel *forget_label;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *login_btn;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *regie_btn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName("loginDialog");
        loginDialog->resize(300, 500);
        loginDialog->setMinimumSize(QSize(300, 500));
        loginDialog->setMaximumSize(QSize(543, 706));
        verticalLayout_2 = new QVBoxLayout(loginDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        err_tip = new QLabel(loginDialog);
        err_tip->setObjectName("err_tip");
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(err_tip);

        head_pic = new QLabel(loginDialog);
        head_pic->setObjectName("head_pic");
        head_pic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(head_pic);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 8);

        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        enail_label = new QLabel(loginDialog);
        enail_label->setObjectName("enail_label");

        horizontalLayout->addWidget(enail_label);

        email_Edit = new QLineEdit(loginDialog);
        email_Edit->setObjectName("email_Edit");

        horizontalLayout->addWidget(email_Edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pass_label = new QLabel(loginDialog);
        pass_label->setObjectName("pass_label");

        horizontalLayout_3->addWidget(pass_label);

        pass_Edit = new QLineEdit(loginDialog);
        pass_Edit->setObjectName("pass_Edit");

        horizontalLayout_3->addWidget(pass_Edit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        forget_label = new cilcklabel(loginDialog);
        forget_label->setObjectName("forget_label");

        horizontalLayout_6->addWidget(forget_label);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        login_btn = new QPushButton(loginDialog);
        login_btn->setObjectName("login_btn");
        login_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(login_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        regie_btn = new QPushButton(loginDialog);
        regie_btn->setObjectName("regie_btn");
        regie_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_7->addWidget(regie_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);

        verticalLayout_2->addLayout(verticalLayout_4);


        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QCoreApplication::translate("loginDialog", "Dialog", nullptr));
        err_tip->setText(QCoreApplication::translate("loginDialog", "\350\257\267\350\276\223\345\205\245\351\202\256\347\256\261\345\222\214\345\257\206\347\240\201", nullptr));
        head_pic->setText(QString());
        enail_label->setText(QCoreApplication::translate("loginDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        pass_label->setText(QCoreApplication::translate("loginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        forget_label->setText(QCoreApplication::translate("loginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        login_btn->setText(QCoreApplication::translate("loginDialog", "\347\231\273\345\275\225", nullptr));
        regie_btn->setText(QCoreApplication::translate("loginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
