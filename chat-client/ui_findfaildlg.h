/********************************************************************************
** Form generated from reading UI file 'findfaildlg.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFAILDLG_H
#define UI_FINDFAILDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>

QT_BEGIN_NAMESPACE

class Ui_FindFailDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *fail_tip;
    QLabel *fail_tip2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    Clickedbtn *fail_sure_btn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *FindFailDlg)
    {
        if (FindFailDlg->objectName().isEmpty())
            FindFailDlg->setObjectName("FindFailDlg");
        FindFailDlg->resize(250, 200);
        FindFailDlg->setMinimumSize(QSize(250, 200));
        FindFailDlg->setMaximumSize(QSize(250, 200));
        verticalLayout_2 = new QVBoxLayout(FindFailDlg);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(FindFailDlg);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        fail_tip = new QLabel(widget);
        fail_tip->setObjectName("fail_tip");

        verticalLayout->addWidget(fail_tip);

        fail_tip2 = new QLabel(widget);
        fail_tip2->setObjectName("fail_tip2");

        verticalLayout->addWidget(fail_tip2);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(FindFailDlg);
        widget_2->setObjectName("widget_2");
        widget_2->setMaximumSize(QSize(16777215, 80));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        fail_sure_btn = new Clickedbtn(widget_2);
        fail_sure_btn->setObjectName("fail_sure_btn");
        fail_sure_btn->setMinimumSize(QSize(150, 0));
        fail_sure_btn->setMaximumSize(QSize(150, 30));

        horizontalLayout->addWidget(fail_sure_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(FindFailDlg);

        QMetaObject::connectSlotsByName(FindFailDlg);
    } // setupUi

    void retranslateUi(QDialog *FindFailDlg)
    {
        FindFailDlg->setWindowTitle(QCoreApplication::translate("FindFailDlg", "Dialog", nullptr));
        fail_tip->setText(QCoreApplication::translate("FindFailDlg", "\346\234\252\346\211\276\345\210\260\350\257\245\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        fail_tip2->setText(QCoreApplication::translate("FindFailDlg", "\350\257\267\346\243\200\346\237\245\350\276\223\345\205\245\350\264\246\345\217\267\346\230\257\345\220\246\346\255\243\347\241\256", nullptr));
        fail_sure_btn->setText(QCoreApplication::translate("FindFailDlg", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindFailDlg: public Ui_FindFailDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFAILDLG_H
