#ifndef APPLYFRIENDITEM_H
#define APPLYFRIENDITEM_H

#include <QWidget>
#include<QListWidgetItem>
#include"listitme.h"
#include<userdata.h>
#include"memory"
namespace Ui {
class ApplyFriendItem;
}

class ApplyFriendItem : public Listitme
{
    Q_OBJECT

public:
    explicit ApplyFriendItem(QWidget *parent = nullptr);
    ~ApplyFriendItem();
    void SetInfo(std::shared_ptr<ApplyInfo> add_info);
    void ShowBtn(bool isshow);
    int GetUid();
    QSize sizeHint() const override {
        return QSize(250, 80); // 返回自定义的尺寸
    }
private:
    Ui::ApplyFriendItem *ui;
    std::shared_ptr<ApplyInfo> _add_info;
    bool _added;

signals:
    void sig_auth_friend(std::shared_ptr<ApplyInfo> addinfo);//当按下添加按钮的时候触发
public slots:

};

#endif // APPLYFRIENDITEM_H
