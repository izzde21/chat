/********************************************************************************
** Form generated from reading UI file 'findsuccessdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDSUCCESSDLG_H
#define UI_FINDSUCCESSDLG_H

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

class Ui_FindSuccessDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *head_lb;
    QLabel *name_lb;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    Clickedbtn *add_friend_btn;

    void setupUi(QDialog *FindSuccessDlg)
    {
        if (FindSuccessDlg->objectName().isEmpty())
            FindSuccessDlg->setObjectName("FindSuccessDlg");
        FindSuccessDlg->setMinimumSize(QSize(300, 250));
        FindSuccessDlg->setMaximumSize(QSize(421, 250));
        verticalLayout = new QVBoxLayout(FindSuccessDlg);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(15, -1, -1, -1);
        widget = new QWidget(FindSuccessDlg);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        head_lb = new QLabel(widget);
        head_lb->setObjectName("head_lb");
        head_lb->setMinimumSize(QSize(90, 90));
        head_lb->setMaximumSize(QSize(90, 90));
        head_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(head_lb);

        name_lb = new QLabel(widget);
        name_lb->setObjectName("name_lb");
        name_lb->setMinimumSize(QSize(90, 90));
        name_lb->setMaximumSize(QSize(90, 90));
        name_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(name_lb);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(FindSuccessDlg);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(400, 0));
        widget_2->setMaximumSize(QSize(400, 16777215));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        add_friend_btn = new Clickedbtn(widget_2);
        add_friend_btn->setObjectName("add_friend_btn");
        add_friend_btn->setMinimumSize(QSize(180, 40));
        add_friend_btn->setMaximumSize(QSize(180, 16777215));

        horizontalLayout->addWidget(add_friend_btn);


        verticalLayout->addWidget(widget_2);


        retranslateUi(FindSuccessDlg);

        QMetaObject::connectSlotsByName(FindSuccessDlg);
    } // setupUi

    void retranslateUi(QDialog *FindSuccessDlg)
    {
        FindSuccessDlg->setWindowTitle(QCoreApplication::translate("FindSuccessDlg", "Dialog", nullptr));
        head_lb->setText(QString());
        name_lb->setText(QString());
        add_friend_btn->setText(QCoreApplication::translate("FindSuccessDlg", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindSuccessDlg: public Ui_FindSuccessDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDSUCCESSDLG_H
