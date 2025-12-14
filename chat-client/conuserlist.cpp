#include "conuserlist.h"
#include<QRandomGenerator>
#include<QEvent>
#include<QMoveEvent>
#include<QWheelEvent>
#include<QScrollBar>
#include"tcpmgr.h"
#include"usermgr.h"
#include<QListWidgetItem>
#include<QTimer>
ConUserList::ConUserList(QWidget *parent) :QListWidget(parent),_load_pending(false){
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);
    init();
    connect(this, &QListWidget::itemClicked, this, &ConUserList::slot_item_clicked);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_auth_rsp, this, &ConUserList::slot_auth_rsp);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_add_auth_friend, this, &ConUserList::slot_add_auth_friend);
}

std::vector<QString>  _strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};
std::vector<QString> _heads = {
    ":/res/6888.jpg",
    ":/res/6903.jpg",
    ":/res/6909.jpg",
    ":/res/6912.jpg",
    ":/res/6919.jpg",
};
std::vector<QString> _names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

void ConUserList::init(){
    auto item=new QListWidgetItem;
    GroupTipItem *grou=new GroupTipItem();
    grou->settip(tr("添加好友"));
    item->setSizeHint(grou->sizeHint());
    this->addItem(item);
    this->setItemWidget(item,grou);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);


    _add_frednd_item = new ConUserItem();
    _add_frednd_item->setObjectName("new_friend_item");
    _add_frednd_item->seticontype(APPLY_FRIEND_ITEM);
    _add_frednd_item->SetInfo(0,tr("新的朋友"),":/res/add_friend.png");

    auto new_item=new QListWidgetItem;
    new_item->setSizeHint(_add_frednd_item->sizeHint());
    this->addItem(new_item);
    this->setItemWidget(new_item,_add_frednd_item);

    auto * groupCon = new GroupTipItem();
    groupCon->settip(tr("联系人"));
    _groupitem = new QListWidgetItem;
    _groupitem->setSizeHint(groupCon->sizeHint());
    this->addItem(_groupitem);
    this->setItemWidget(_groupitem, groupCon);
    _groupitem->setFlags(_groupitem->flags() & ~Qt::ItemIsSelectable);

    auto friend_list=UserMgr::GetInstance()->GetFriendlist();
    /*if(friend_list.empty()){
        return;
    }*/
    qDebug()<<"friend_list is ";
    for(auto friend_info:friend_list){
        if(friend_info==nullptr){
            continue;
        }
        qDebug()<<"friend_info is not nill";
        auto * con_user_list=new ConUserItem();
        con_user_list->SetInfo(friend_info);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(con_user_list->sizeHint());
        this->addItem(item);
        this->setItemWidget(item, con_user_list);
    }

        UserMgr::GetInstance()->UpdateContactLoadedCount();
    for(int i=0;i<13;i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%_strs.size();
        int head_i = randomValue%_heads.size();
        int name_i = randomValue%_names.size();
        auto *con_user_wid = new ConUserItem();
        con_user_wid->SetInfo(0,_names[name_i], _heads[head_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(con_user_wid->sizeHint());
        this->addItem(item);
        this->setItemWidget(item, con_user_wid);
    }

}
void ConUserList::ShowRedPoint(bool bshow){
    _add_frednd_item->ShowRidpoint(true);
}
void ConUserList::slot_item_clicked(QListWidgetItem *item){
    QWidget * wid=this->itemWidget(item);
    if(!wid){
        return;
    }

    Listitme * liitem=dynamic_cast<Listitme*>(wid);
    if(liitem==nullptr){
        return;
    }
    auto itemType = liitem->Geticontype();
    if(itemType == ListItemType::INVALID_ITEM
        || itemType == ListItemType::GROUP_TIP_ITEM){
        qDebug()<< "slot invalid item clicked ";
        return;
    }

    if(itemType == ListItemType::APPLY_FRIEND_ITEM){
        emit sig_switch_apply_friend_page();
        return;
    }

    if(itemType == ListItemType::CONTACT_USER_ITEM){
        qDebug()<< "slot CONTACT_USER_ITEM item clicked ";
        auto con_item = qobject_cast<ConUserItem*>(liitem);
        auto user_info = con_item->GetInfo();
        emit sig_switch_friend_info_page(user_info);
        return;
    }
}
bool ConUserList::eventFilter(QObject *object, QEvent *event) {
    if(object==this->viewport()){
        if(event->type()==QMoveEvent::Enter){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }
        if(event->type()==QMoveEvent::Leave){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    if(object==this->viewport() && event->type() == QEvent::Wheel){
        QWheelEvent * wh=static_cast<QWheelEvent*>(event);
        int numdegger=wh->angleDelta().y()/8;
        int numdesp=numdegger/15;

        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numdesp);

        QScrollBar* scrollvar=this->verticalScrollBar();

        int max=scrollvar->maximum();
        int value=scrollvar->value();

        if(max-value<=0){
            auto b_loaded = UserMgr::GetInstance()->IsLoadChatFin();
            if(b_loaded){
                return true;
            }

            if(_load_pending){
                return true;
            }

            _load_pending = true;

            QTimer::singleShot(100, [this](){
                _load_pending = false;
                //QCoreApplication::quit(); // 完成后退出应用程序
            });
            emit sig_loading_contact_user();
        }
        return true;
    }
        return QListWidget::eventFilter(object, event);
}


void ConUserList::slot_auth_rsp(std::shared_ptr<AuthRsp> rsp)
{
    qDebug()<<"slot_auth_rsp in conuserlist";
    bool isfriend=UserMgr::GetInstance()->CheckFriendById(rsp->_uid);
    if(isfriend){
        return;
    }
    int index=this->row(_groupitem);
    qDebug()<<"index is"<<index;

    auto conuseritem=new ConUserItem();
    conuseritem->SetInfo(rsp);
    auto item=new QListWidgetItem();
    item->setSizeHint(conuseritem->sizeHint());
    this->insertItem(index+1,item);
    this->setItemWidget(item,conuseritem);
}

void ConUserList::slot_add_auth_friend(std::shared_ptr<AuthInfo> info)
{
    qDebug()<<"slot_auth_rsp in conuserlist";
    bool isfriend=UserMgr::GetInstance()->CheckFriendById(info->_uid);
    if(isfriend){
        return;
    }
    int index=this->row(_groupitem);
    qDebug()<<"index is"<<index;

    auto conuseritem=new ConUserItem();
    conuseritem->SetInfo(info);
    auto item=new QListWidgetItem();
    item->setSizeHint(conuseritem->sizeHint());
    this->insertItem(index+1,item);
    this->setItemWidget(item,conuseritem);
}
