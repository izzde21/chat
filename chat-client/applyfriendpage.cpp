#include "applyfriendpage.h"
#include "ui_applyfriendpage.h"
#include"tcpmgr.h"
#include<QRandomGenerator>
#include<QPainter>
#include"usermgr.h"
#include"authenfriend.h"
std::vector<QString> headsq = {
    ":/res/6888.jpg",
    ":/res/6903.jpg",
    ":/res/6909.jpg",
    ":/res/6912.jpg",
    ":/res/6919.jpg",
};

std::vector<QString>  strsy ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};

std::vector<QString> namesy = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};
ApplyFriendPage::ApplyFriendPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ApplyFriendPage)
{
    ui->setupUi(this);
    connect(ui->apply_friend_list, &ApplyFriendList::sig_show_search, this, &ApplyFriendPage::sig_show_search);
    loadApplyList();

   connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_auth_rsp, this, &ApplyFriendPage::slot_auth_rsp);
}

ApplyFriendPage::~ApplyFriendPage()
{
    delete ui;
}
void ApplyFriendPage::AddNewApply(std::shared_ptr<AddFriendApply> apply){
    auto apply_info=std::make_shared<ApplyInfo>(apply->_from_uid,apply->_name,apply->_desc,
                                                  apply->_icon,apply->_nick,apply->_sex,0);
    qDebug()<<apply->_icon;
    ApplyFriendItem * apply_item =new ApplyFriendItem();
    apply_item->SetInfo(apply_info);
    QListWidgetItem * item=new QListWidgetItem;
    item->setSizeHint(apply_item->sizeHint());

    item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    ui->apply_friend_list->insertItem(0,item);
    ui->apply_friend_list->setItemWidget(item, apply_item);
    apply_item->ShowBtn(true);
    _unauth_items[apply->_from_uid] = apply_item;
    //当点击ApplyFriendItem里面的添加按钮的时候触发
    connect(apply_item, &ApplyFriendItem::sig_auth_friend, [this](std::shared_ptr<ApplyInfo> apply_info) {
                auto* authFriend = new AuthenFriend(this);
                authFriend->setModal(true);
                authFriend->SetSearchInfo(apply_info);
                authFriend->show();
    });
}
void ApplyFriendPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ApplyFriendPage::loadApplyList(){
    auto apply_list =UserMgr::GetInstance()->GetApplyList();
    for(auto & apply:apply_list){

        apply->SetIcon(apply->_icon);
        auto* add_apply=new ApplyFriendItem();
        add_apply->SetInfo(apply);

        auto item=new QListWidgetItem();
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        item->setSizeHint(add_apply->sizeHint());

        ui->apply_friend_list->insertItem(0,item);
        ui->apply_friend_list->setItemWidget(item,add_apply);
        if(apply->_status){
            add_apply->ShowBtn(false);
        }else{
            add_apply->ShowBtn(true);
            auto uid = add_apply->GetUid();
            _unauth_items[uid] = add_apply;
            hasNewApply=true;
        }

        if (hasNewApply){
            emit sig_have_apply();
            qDebug() << "sig_have_apply emitted";
        }
        connect(add_apply, &ApplyFriendItem::sig_auth_friend, [this](std::shared_ptr<ApplyInfo> apply_info) {
            auto* authFriend = new AuthenFriend(this);
            authFriend->setModal(true);
            authFriend->SetSearchInfo(apply_info);
            authFriend->show();
        });
    }

    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strsy.size();
        int head_i = randomValue%headsq.size();
        int name_i = randomValue%namesy.size();
        auto *apply_item = new ApplyFriendItem();
        auto apply = std::make_shared<ApplyInfo>(0, namesy[name_i], strsy[str_i],
                                                 headsq[head_i], namesy[name_i], 0, 1);
        apply_item->SetInfo(apply);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(apply_item->sizeHint());
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        ui->apply_friend_list->addItem(item);
        ui->apply_friend_list->setItemWidget(item, apply_item);
        //收到审核好友信号
        connect(apply_item, &ApplyFriendItem::sig_auth_friend, [this](std::shared_ptr<ApplyInfo> apply_info){
            auto* authFriend = new AuthenFriend(this);
            authFriend->setModal(true);
            authFriend->SetSearchInfo(apply_info);
            authFriend->show();
        });
    }
}

void ApplyFriendPage::slot_auth_rsp(std::shared_ptr<AuthRsp> rsp)
{
    qDebug()<<"slot_auth_rsp";
    auto uid = rsp->_uid;
    auto find_iter = _unauth_items.find(uid);
    if (find_iter == _unauth_items.end()) {
        return;
    }
    find_iter->second->ShowBtn(false);

}
