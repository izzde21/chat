#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"resetdialog.h"
#include"tcpmgr.h"
/******************************************************************************
 *
 * @file       mainwindow.cpp
 * @brief      主窗口
 *
 * @author     yangjintian
 * @date       2025/08/07
 * @history
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(300,500);
    setWindowTitle("chat");
    login_dialog=new loginDialog(this); //创建登录界面
    setCentralWidget(login_dialog);
    //login_dialog->show();
    connect(login_dialog,&loginDialog::switchRegister,this,&MainWindow::switchRegister);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //register_dialog->hide();
    connect(login_dialog,&loginDialog::sigwsitchfordig,this,&MainWindow::switchfordig);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_swich_chatdlg,this,&MainWindow::slot_swich_chatdlg);

    //emit TcpMgr::GetInstance()->sig_swich_chatdlg();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::switchRegister(){


    register_dialog=new registerDialog(this);  //创建注册界面
    connect(register_dialog,&registerDialog::returnlogin,this,&MainWindow::switchlongic);

    register_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    login_dialog->hide();
    setCentralWidget(register_dialog);
    register_dialog->show();
}


void MainWindow::switchlongic(){
    login_dialog=new loginDialog(this); //创建登录界面
    setCentralWidget(login_dialog);
    connect(login_dialog,&loginDialog::switchRegister,this,&MainWindow::switchRegister);
    connect(login_dialog,&loginDialog::sigwsitchfordig,this,&MainWindow::switchfordig);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    register_dialog->hide();
    login_dialog->show();
}

void MainWindow::forreturnlog(){
    login_dialog=new loginDialog(this); //创建登录界面
    setCentralWidget(login_dialog);
    connect(login_dialog,&loginDialog::switchRegister,this,&MainWindow::switchRegister);
    connect(login_dialog,&loginDialog::sigwsitchfordig,this,&MainWindow::switchfordig);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    forget_dialog->hide();
    login_dialog->show();
}

void MainWindow::switchfordig(){
    forget_dialog=new ResetDialog(this);
    setCentralWidget(forget_dialog);
    forget_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(forget_dialog,&ResetDialog::sigreturnlog,this,&MainWindow::forreturnlog);
    login_dialog->hide();
    forget_dialog->show();
}

void MainWindow::slot_swich_chatdlg(){
    chat_dialog=new ChatDialog(this);
    setCentralWidget(chat_dialog);
    chat_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    chat_dialog->show();
    login_dialog->hide();
    this->setMinimumSize(QSize(950,800));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}
