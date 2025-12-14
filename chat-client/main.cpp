#include "mainwindow.h"
#include<QFile>
#include <QApplication>
#include<QDir>
#include<QSettings>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile qss(":/style/stylesheet.qss");

    if(qss.open(QFile::ReadOnly)){
        qDebug("open success!");
        QString style=QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("open failed!");}

    QString filename="config.ini";
    QString app_path=QCoreApplication::applicationDirPath();
    QString config_path=QDir::toNativeSeparators(app_path+QDir::separator()+filename);
    QSettings setting(config_path,QSettings::IniFormat);
    QString gate_host=setting.value("GateSever/host").toString();
    QString gate_port=setting.value("GateSever/port").toString();
    gate_url_prefix="http://"+gate_host+":"+gate_port;  //构造Url
    MainWindow w;
    w.show();
    return a.exec();
}
