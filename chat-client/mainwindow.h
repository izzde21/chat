#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"resetdialog.h"
#include <QMainWindow>
#include"logindialog.h"
#include"registerdialog.h"
#include"ChatDialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void switchRegister();
    void switchlongic();
    void switchfordig();
    void forreturnlog();
    void slot_swich_chatdlg();
private:
    Ui::MainWindow *ui;
    loginDialog * login_dialog;
    registerDialog * register_dialog;
    ResetDialog * forget_dialog;
    ChatDialog * chat_dialog;
};


#endif // MAINWINDOW_H
