#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include"global.h"
#include <QDialog>
#include<QMap>
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private:
    Ui::loginDialog *ui;
    void init();
    bool checkpass();
    bool checknuer();
    void showTip(QString str,bool ok);
    void Adderrmap(TipErr err,QString str);
    void delerrmap(TipErr err);
    QMap<Repid,std::function<void(const QJsonObject& )>> _handle;
    QMap<TipErr,QString> err_map;
    void inithandle();
    QString _token;
    int _uid;
    void enablebtn(bool can);
signals:
    void sigwsitchfordig();
    void switchRegister();
    void sig_tcp_con(SeverInfo si);
public slots:
    void slot_login_mod_finish(Repid id, QString res, Error error);
    void slot_con_final(bool is);
    void slot_fail_login(int err);
private slots:
    void on_login_btn_clicked();
};

#endif // LOGINDIALOG_H
