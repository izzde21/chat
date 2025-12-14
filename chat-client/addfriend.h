#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>
#include"cilcklabel.h"
#include"userdata.h"
#include "friendlabel.h"
namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    ~AddFriend();
    void AddTipLBS(cilcklabel*,QPoint cur_point,QPoint &next_point,int text_width,int text_hight);
    bool eventFilter(QObject *obj, QEvent *event);
    void SetSearchInfo(std::shared_ptr<SearchInfo> si);
    void resetLabels();
private:
    Ui::AddFriend *ui;
    void InitTipLbs();
    QMap<QString,cilcklabel*>_add_labels;
    std::vector<QString> _add_labels_key;
    QPoint _label_point;
    QMap<QString,FriendLabel*> _friend_labels;
    std::vector<QString> _friend_labels_key;
    std::vector<QString> _tip_data;
    void addlabel(QString name);
    QPoint _tip_cur_point;
    std::shared_ptr<SearchInfo> _si;
signals:
public slots:
    void Slotpressenter();
    void Slottextchange(const QString& text);
    void Sloteditfinish();
    void Slottipclick(QString text);
    void Slotmoretip();
    void Slotsurebtnclick();
    void Slotcancelbtnclick();
    void SlotChangeFriendLabelByTip(QString lbtext, ClickLbState state);
    void SlotRemoveFriendLabel(QString name);
};

#endif // ADDFRIEND_H
