#ifndef FRIENDLABEL_H
#define FRIENDLABEL_H

#include <QWidget>
namespace Ui {
class FriendLabel;
}

class FriendLabel : public QWidget
{
    Q_OBJECT

public:
    explicit FriendLabel(QWidget *parent = nullptr);
    int width();
    void settext(QString text);
    ~FriendLabel();
    int height();
    QString text();
private:
    Ui::FriendLabel *ui;
    QString _text;
    int _width;
    int _height;

signals:
    void sig_close(QString text);
public slots:
    void slot_close();

};

#endif // FRIENDLABEL_H
