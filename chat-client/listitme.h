#ifndef LISTITME_H
#define LISTITME_H
#include<QWidget>
#include"global.h"
class Listitme : public QWidget
{
    Q_OBJECT
public:
    explicit Listitme(QWidget *parent = nullptr);
    void seticontype(ListItemType icontype);
    ListItemType Geticontype();
protected:
    //virtual void paintEvent(QPaintEvent *event) override;
private:
    ListItemType _icontype;
signals:
};

#endif // LISTITME_H
