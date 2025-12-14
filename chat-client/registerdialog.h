#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#include"QMap"
#include <QDialog>
#include"global.h"
#include<QTimer>
namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();

private slots:
    void on_get_num_btn_clicked();
    void slot_reg_mod_finish(Repid id,QString res,Error error);

    void on_confrim_btn_clicked();

    void on_returnButton_clicked();

    void on_cancel_btn_clicked();

private:
    bool checkuser();
    bool checkpass();
    bool checkconfrim();
    bool checkemail();
    bool checkVarify();
    void AddErr(TipErr err,QString str);
    void DelErr(TipErr err);
    QMap<TipErr,QString>err_map;
    Ui::registerDialog *ui;
    void initHttpHandles();
    void showTip(QString str,bool ok=true);
    QMap<Repid,std::function<void(const QJsonObject&)>> _handles;
    int count_;
    QTimer *timer;
    void changepage();
signals:
    void returnlogin();
};

#endif // REGISTERDIALOG_H
