#include "findfaildlg.h"
#include "ui_findfaildlg.h"

FindFailDlg::FindFailDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindFailDlg)
{
    ui->setupUi(this);
    setWindowTitle("查找失败");
    setWindowFlag(Qt::FramelessWindowHint);
    setModal(true);
    ui->fail_sure_btn->SetStatu("normal","hover","press");
    show();
}

FindFailDlg::~FindFailDlg()
{
    delete ui;
}

void FindFailDlg::on_fail_sure_btn_clicked()
{
    hide();
    deleteLater();
}

