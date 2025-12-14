/********************************************************************************
** Form generated from reading UI file 'charuserlist.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARUSERLIST_H
#define UI_CHARUSERLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CharUserList
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *icon_wid;
    QVBoxLayout *verticalLayout;
    QLabel *icon_lb;
    QWidget *user_info_wid;
    QVBoxLayout *verticalLayout_2;
    QLabel *user_name_lb;
    QLabel *char_lb;
    QLabel *time_lb;

    void setupUi(QWidget *CharUserList)
    {
        if (CharUserList->objectName().isEmpty())
            CharUserList->setObjectName("CharUserList");
        CharUserList->setEnabled(true);
        CharUserList->resize(250, 51);
        horizontalLayout = new QHBoxLayout(CharUserList);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 6, 3, 0);
        icon_wid = new QWidget(CharUserList);
        icon_wid->setObjectName("icon_wid");
        icon_wid->setMaximumSize(QSize(50, 50));
        verticalLayout = new QVBoxLayout(icon_wid);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        icon_lb = new QLabel(icon_wid);
        icon_lb->setObjectName("icon_lb");
        icon_lb->setMinimumSize(QSize(45, 45));
        icon_lb->setMaximumSize(QSize(45, 45));

        verticalLayout->addWidget(icon_lb);


        horizontalLayout->addWidget(icon_wid);

        user_info_wid = new QWidget(CharUserList);
        user_info_wid->setObjectName("user_info_wid");
        user_info_wid->setMaximumSize(QSize(120, 16777215));
        verticalLayout_2 = new QVBoxLayout(user_info_wid);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(3, 2, 0, 3);
        user_name_lb = new QLabel(user_info_wid);
        user_name_lb->setObjectName("user_name_lb");

        verticalLayout_2->addWidget(user_name_lb);

        char_lb = new QLabel(user_info_wid);
        char_lb->setObjectName("char_lb");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(char_lb->sizePolicy().hasHeightForWidth());
        char_lb->setSizePolicy(sizePolicy);
        char_lb->setMaximumSize(QSize(200, 16777215));
        char_lb->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    max-width: 200px;  /* \351\231\220\345\210\266\346\234\200\345\244\247\345\256\275\345\272\246 */\n"
"    qproperty-wordWrap: false;  /* \347\246\201\346\255\242\350\207\252\345\212\250\346\215\242\350\241\214 */\n"
"    qproperty-alignment: 'AlignLeft | AlignVCenter';  /* \345\267\246\345\257\271\351\275\220 + \345\236\202\347\233\264\345\261\205\344\270\255 */\n"
"}"));
        char_lb->setWordWrap(false);

        verticalLayout_2->addWidget(char_lb);


        horizontalLayout->addWidget(user_info_wid);

        time_lb = new QLabel(CharUserList);
        time_lb->setObjectName("time_lb");
        time_lb->setMinimumSize(QSize(45, 45));
        time_lb->setMaximumSize(QSize(45, 45));
        time_lb->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(time_lb);

        horizontalLayout->setStretch(0, 1);

        retranslateUi(CharUserList);

        QMetaObject::connectSlotsByName(CharUserList);
    } // setupUi

    void retranslateUi(QWidget *CharUserList)
    {
        CharUserList->setWindowTitle(QCoreApplication::translate("CharUserList", "Form", nullptr));
        icon_lb->setText(QString());
        user_name_lb->setText(QCoreApplication::translate("CharUserList", "name", nullptr));
        char_lb->setText(QCoreApplication::translate("CharUserList", "hello", nullptr));
        time_lb->setText(QCoreApplication::translate("CharUserList", "13:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CharUserList: public Ui_CharUserList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARUSERLIST_H
