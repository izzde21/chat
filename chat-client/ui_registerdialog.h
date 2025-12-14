/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cilcklabel.h"
#include "timebtn.h"

QT_BEGIN_NAMESPACE

class Ui_registerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_4;
    QLabel *tip1;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *returnButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_7;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_user;
    QLabel *user_label;
    QLineEdit *user_Edit;
    QHBoxLayout *horizontalLayout_emila;
    QLabel *email_label;
    QLineEdit *email_Edit;
    QHBoxLayout *horizontalLayout_pass;
    QLabel *pass_label;
    QLineEdit *pass_Edit;
    cilcklabel *pass_visible;
    QHBoxLayout *horizontalLayout_confrim;
    QLabel *label;
    QLineEdit *confrim_Edit;
    cilcklabel *confirm_visible;
    QHBoxLayout *horizontalLayout_num;
    QLabel *num_label;
    QLineEdit *num_Edit;
    TimeBtn *get_num_btn;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_confrimorc;
    QPushButton *confrim_btn;
    QPushButton *cancel_btn;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *registerDialog)
    {
        if (registerDialog->objectName().isEmpty())
            registerDialog->setObjectName("registerDialog");
        registerDialog->resize(400, 303);
        verticalLayout_2 = new QVBoxLayout(registerDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(registerDialog);
        stackedWidget->setObjectName("stackedWidget");
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        tip1 = new QLabel(page_2);
        tip1->setObjectName("tip1");
        tip1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(tip1);

        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        widget = new QWidget(page_2);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        returnButton = new QPushButton(widget);
        returnButton->setObjectName("returnButton");

        horizontalLayout_2->addWidget(returnButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addWidget(widget);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_7);

        stackedWidget->addWidget(page_2);
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        err_tip = new QLabel(page);
        err_tip->setObjectName("err_tip");
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(err_tip);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_user = new QHBoxLayout();
        horizontalLayout_user->setObjectName("horizontalLayout_user");
        user_label = new QLabel(page);
        user_label->setObjectName("user_label");

        horizontalLayout_user->addWidget(user_label);

        user_Edit = new QLineEdit(page);
        user_Edit->setObjectName("user_Edit");

        horizontalLayout_user->addWidget(user_Edit);


        verticalLayout_4->addLayout(horizontalLayout_user);

        horizontalLayout_emila = new QHBoxLayout();
        horizontalLayout_emila->setObjectName("horizontalLayout_emila");
        email_label = new QLabel(page);
        email_label->setObjectName("email_label");

        horizontalLayout_emila->addWidget(email_label);

        email_Edit = new QLineEdit(page);
        email_Edit->setObjectName("email_Edit");

        horizontalLayout_emila->addWidget(email_Edit);


        verticalLayout_4->addLayout(horizontalLayout_emila);

        horizontalLayout_pass = new QHBoxLayout();
        horizontalLayout_pass->setSpacing(4);
        horizontalLayout_pass->setObjectName("horizontalLayout_pass");
        pass_label = new QLabel(page);
        pass_label->setObjectName("pass_label");

        horizontalLayout_pass->addWidget(pass_label);

        pass_Edit = new QLineEdit(page);
        pass_Edit->setObjectName("pass_Edit");

        horizontalLayout_pass->addWidget(pass_Edit);

        pass_visible = new cilcklabel(page);
        pass_visible->setObjectName("pass_visible");
        pass_visible->setMinimumSize(QSize(20, 20));
        pass_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_pass->addWidget(pass_visible);


        verticalLayout_4->addLayout(horizontalLayout_pass);

        horizontalLayout_confrim = new QHBoxLayout();
        horizontalLayout_confrim->setSpacing(4);
        horizontalLayout_confrim->setObjectName("horizontalLayout_confrim");
        label = new QLabel(page);
        label->setObjectName("label");

        horizontalLayout_confrim->addWidget(label);

        confrim_Edit = new QLineEdit(page);
        confrim_Edit->setObjectName("confrim_Edit");

        horizontalLayout_confrim->addWidget(confrim_Edit);

        confirm_visible = new cilcklabel(page);
        confirm_visible->setObjectName("confirm_visible");
        confirm_visible->setMinimumSize(QSize(20, 20));
        confirm_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_confrim->addWidget(confirm_visible);


        verticalLayout_4->addLayout(horizontalLayout_confrim);

        horizontalLayout_num = new QHBoxLayout();
        horizontalLayout_num->setObjectName("horizontalLayout_num");
        num_label = new QLabel(page);
        num_label->setObjectName("num_label");

        horizontalLayout_num->addWidget(num_label);

        num_Edit = new QLineEdit(page);
        num_Edit->setObjectName("num_Edit");

        horizontalLayout_num->addWidget(num_Edit);

        get_num_btn = new TimeBtn(page);
        get_num_btn->setObjectName("get_num_btn");
        get_num_btn->setMinimumSize(QSize(25, 25));

        horizontalLayout_num->addWidget(get_num_btn);


        verticalLayout_4->addLayout(horizontalLayout_num);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        horizontalLayout_confrimorc = new QHBoxLayout();
        horizontalLayout_confrimorc->setObjectName("horizontalLayout_confrimorc");
        confrim_btn = new QPushButton(page);
        confrim_btn->setObjectName("confrim_btn");
        confrim_btn->setMinimumSize(QSize(25, 25));

        horizontalLayout_confrimorc->addWidget(confrim_btn);

        cancel_btn = new QPushButton(page);
        cancel_btn->setObjectName("cancel_btn");
        cancel_btn->setMinimumSize(QSize(25, 25));

        horizontalLayout_confrimorc->addWidget(cancel_btn);


        verticalLayout_4->addLayout(horizontalLayout_confrimorc);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(registerDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(registerDialog);
    } // setupUi

    void retranslateUi(QDialog *registerDialog)
    {
        registerDialog->setWindowTitle(QCoreApplication::translate("registerDialog", "Dialog", nullptr));
        tip1->setText(QCoreApplication::translate("registerDialog", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\2145\347\247\222\345\220\216\350\277\224\345\233\236\347\231\273\351\231\206", nullptr));
        label_3->setText(QCoreApplication::translate("registerDialog", "\347\202\271\345\207\273\346\214\211\351\222\256\347\233\264\346\216\245\350\277\224\345\233\236\347\231\273\351\231\206\347\225\214\351\235\242", nullptr));
        returnButton->setText(QCoreApplication::translate("registerDialog", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        err_tip->setText(QCoreApplication::translate("registerDialog", "\351\224\231\350\257\257\344\277\241\346\201\257", nullptr));
        user_label->setText(QCoreApplication::translate("registerDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        email_label->setText(QCoreApplication::translate("registerDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        pass_label->setText(QCoreApplication::translate("registerDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        pass_visible->setText(QString());
        label->setText(QCoreApplication::translate("registerDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        confirm_visible->setText(QString());
        num_label->setText(QCoreApplication::translate("registerDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        get_num_btn->setText(QCoreApplication::translate("registerDialog", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", nullptr));
        confrim_btn->setText(QCoreApplication::translate("registerDialog", "\347\241\256\350\256\244", nullptr));
        cancel_btn->setText(QCoreApplication::translate("registerDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerDialog: public Ui_registerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
