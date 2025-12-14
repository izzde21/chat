#ifndef AUTHENFRIEND_H
#define AUTHENFRIEND_H

#include <QDialog>
#include"cilcklabel.h"
#include"userdata.h"
#include "friendlabel.h"
namespace Ui {
class AuthenFriend;
}

class AuthenFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenFriend(QWidget *parent = nullptr);
    ~AuthenFriend();
    void AddTipLBS(cilcklabel*,QPoint cur_point,QPoint &next_point,int text_width,int text_hight);
    bool eventFilter(QObject *obj, QEvent *event);
    void SetSearchInfo(std::shared_ptr<ApplyInfo> si);
    void resetLabels();
private:
    Ui::AuthenFriend *ui;
    void InitTipLbs();
    QMap<QString,cilcklabel*>_add_labels;
    std::vector<QString> _add_labels_key;
    QPoint _label_point;
    QMap<QString,FriendLabel*> _friend_labels;
    std::vector<QString> _friend_labels_key;
    std::vector<QString> _tip_data;
    void addlabel(QString name);
    QPoint _tip_cur_point;
    std::shared_ptr<ApplyInfo> _si;
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

#endif // AUTHENFRIEND_H
