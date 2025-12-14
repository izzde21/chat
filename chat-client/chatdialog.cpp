#include "chatdialog.h"
#include "ui_chatdialog.h"
#include"charuserlist.h"
#include<QRandomGenerator>
#include"loadingdlg.h"
#include"searchlist.h"
#include"tcpmgr.h"
#include"usermgr.h"
#include<QPainter>
#include<QBrush>
ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent),_mode(ChatMode), _state(ChatMode),ui(new Ui::ChatDialog),_b_loading(false),_last_page(nullptr)
{
    ui->setupUi(this);
    ui->add_btn->SetStatu("normal","hover","press");
    ui->seach_edit->setmaxlen(15);

    connect(ui->friend_apply_page, &ApplyFriendPage::sig_have_apply,
            this, [this]() {
                qDebug() << "Lambda slot triggered!";
                this->slot_have_apply(); // 然后调用原来的槽函数
            });

    QAction * seach_close=new QAction(ui->seach_edit);
    seach_close->setIcon(QIcon(":/res/close_transparent.png"));
    ui->seach_edit->addAction(seach_close,QLineEdit::TrailingPosition);
    connect(ui->seach_edit,&QLineEdit::textChanged,seach_close,[seach_close](const QString &text){
        if(!text.isEmpty()){
            seach_close->setIcon(QIcon(":/res/close_search.png"));
        }else{
            seach_close->setIcon(QIcon(":/res/close_transparent.png"));
        }
    });

    connect(seach_close,&QAction::triggered,[this](){
        ui->seach_edit->clear();
    });

    connect(ui->chat_user_list,&ChatUserList::sig_loading_chat_user,this,&ChatDialog::slot_loading_chat_user);
    QAction * seach=new QAction(ui->seach_edit);
    seach->setIcon(QIcon(":/res/search.png"));
    ui->seach_edit->addAction(seach,QLineEdit::LeadingPosition);
    ui->seach_edit->setPlaceholderText(QStringLiteral("搜索"));

    ShowSearch(false);
    addChatUserList();

    QPixmap pix(":/res/login.png");
    QPixmap pix2(ui->side_head->width(),ui->side_head->height());
    pix2.fill(Qt::transparent);
    QPainter painter(&pix2);
    painter.setBrush(QBrush(pix.scaled(30,30,Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(0,0,30,30);
    ui->side_head->setPixmap(pix);
    ui->side_head->setScaledContents(true);
    ui->side_chat_lb->setProperty("state","normal");

    ui->side_chat_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    ui->side_contact_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    AddlbGroud(ui->side_chat_lb);
    AddlbGroud(ui->side_contact_lb);
    connect(ui->side_chat_lb,&StateWidget::clicked,this,&ChatDialog::slot_chat_lb_click);
    connect(ui->side_contact_lb,&StateWidget::clicked,this,&ChatDialog::slot_contact_lb_click);

    SetSelectChatItem(0);
    SetSelectChatPage(0);
    connect(ui->con_user_list,&ConUserList::sig_switch_friend_info_page,this,&ChatDialog::slot_switch_friend_info_page);
    connect(ui->con_user_list,&ConUserList::sig_switch_apply_friend_page,this,&ChatDialog::slot_switch_apply_friend_page);

    connect(ui->chat_user_list,&QListWidget::itemClicked,this,&ChatDialog::slot_item_clicked);
    connect(ui->friend_info_page, &FriendInfoPage::sig_jump_chat_item, this,&ChatDialog::slot_jump_chat_item_from_infopage);
    connect(ui->seach_edit,&QLineEdit::textChanged,this, &ChatDialog::slot_text_changed);
    this->installEventFilter(this);
    ui->side_chat_lb->SetSelected(true);
    ui->search_list->SetSearchEdit(ui->seach_edit);
    connect(ui->con_user_list,&ConUserList::sig_loading_contact_user,this,&ChatDialog::slot_loading_contact_user);
    connect(ui->search_list, &SearchList::sig_jump_chat_item, this, &ChatDialog::slot_jump_chat_item);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_friend_apply, this, &ChatDialog::slot_apply_friend);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_auth_rsp, this, &ChatDialog::slot_auth_rsp);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_add_auth_friend, this, &ChatDialog::slot_add_auth_friend);

    connect(ui->chat_page, &ChatPage::sig_append_send_chat_msg, this, &ChatDialog::slot_append_send_chat_msg);

    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_text_chat_msg,this, &ChatDialog::slot_text_chat_msg);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);

}


void ChatDialog::AddlbGroud(StateWidget* w){
    list_lb.push_back(w);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent *me)
{
    if(_mode!=SearchMode){
        return;
    }
    QPoint posInSearchList =(ui->search_list->mapFromGlobal(me->globalPosition())).toPoint();

    if(!ui->search_list->rect().contains(posInSearchList)){
        ui->seach_edit->clear();
        ShowSearch(false);
    }
}

void ChatDialog::loadMoreChatUser()
{
    auto freidn_list=UserMgr::GetInstance()->GetChatListPerPage();
    if(freidn_list.empty()!=false){
        for(auto & friend_ele:freidn_list){
            auto itea=_chat_items_added.find(friend_ele->_uid);
            if(itea !=_chat_items_added.end()){
                continue;
            }

            auto *chat_user_wid = new CharUserList();
            chat_user_wid->SetInfo(std::make_shared<UserInfo>(friend_ele));
            QListWidgetItem * item=new QListWidgetItem();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->chat_user_list->addItem(item);
            ui->chat_user_list->setItemWidget(item,chat_user_wid);
            _chat_items_added.insert(friend_ele->_uid,item);
        }
        UserMgr::GetInstance()->UpdateChatLoadedCount();
    }
}


void ChatDialog::loadMoreConUser()
{
    auto friend_list = UserMgr::GetInstance()->GetConListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto *chat_user_wid = new ConUserItem();
            chat_user_wid->SetInfo(friend_ele->_uid,friend_ele->_name,
                                   friend_ele->_icon);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->con_user_list->addItem(item);
            ui->con_user_list->setItemWidget(item, chat_user_wid);
        }

        //更新已加载条目
        UserMgr::GetInstance()->UpdateContactLoadedCount();
    }
}

void ChatDialog::Claerlist(StateWidget* w){
    for(auto & lb:list_lb){
        if(lb==w){
            continue;
        }
        else{
            lb->ClearState();
        }
    }
}

void ChatDialog::slot_chat_lb_click(){
    Claerlist(ui->side_chat_lb);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state=ChatMode;
    ShowSearch(false);
}

void ChatDialog::slot_contact_lb_click(){
    Claerlist(ui->side_contact_lb);
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
    _state=ContactMode;
    ShowSearch(false);
}

void ChatDialog::slot_text_changed(const QString &str)
{
    if (!str.isEmpty()) {
        ShowSearch(true);
    }
}

void ChatDialog::slot_apply_friend(std::shared_ptr<AddFriendApply>apply)
{
    qDebug()<<"slot_apply_friend";
    bool res=UserMgr::GetInstance()->AlreadyApply(apply->_from_uid);
    if(res){
        return;
    }

    ui->side_contact_lb->ShowRedPoint(true);
    ui->con_user_list->ShowRedPoint();
    ui->friend_apply_page->AddNewApply(apply);

}

void ChatDialog::slot_have_apply(){
    qDebug()<<"slot_have_apply";
    ui->side_contact_lb->ShowRedPoint(true);
    ui->con_user_list->ShowRedPoint();
}

void ChatDialog::ShowSearch(bool bsearch){
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode=SearchMode;
    }else if(_state==ChatMode){
        ui->chat_user_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode=ChatMode;
    }else if(_state==ContactMode){
        ui->chat_user_list->hide();
        ui->con_user_list->show();
        ui->search_list->hide();
        _mode=ContactMode;
    }
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::slot_loading_chat_user(){
    if(_b_loading){
        return;
    }
    _b_loading=true;
    LoadingDlg * loaddialog=new LoadingDlg(this);
    loaddialog->setModal(true);
    loaddialog->show();
    loadMoreChatUser();
    loaddialog->deleteLater();
    _b_loading=false;
}

std::vector<QString>  strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};
std::vector<QString> heads = {
    ":/res/6888.jpg",
    ":/res/6903.jpg",
    ":/res/6909.jpg",
    ":/res/6912.jpg",
    ":/res/6919.jpg",
};
std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};


void ChatDialog::SetSelectChatItem(int uid)
{
    if(ui->chat_user_list->count() <= 0){
        return;
    }

    if(uid == 0){
        ui->chat_user_list->setCurrentRow(0);
        QListWidgetItem *firstItem = ui->chat_user_list->item(0);
        if(!firstItem){
            return;
        }

        //转为widget
        QWidget *widget = ui->chat_user_list->itemWidget(firstItem);
        if(!widget){
            return;
        }

        auto con_item = qobject_cast<CharUserList*>(widget);
        if(!con_item){
            return;
        }

        _cur_chat_uid = con_item->Getuser()->_uid;

        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        qDebug() << "uid " <<uid<< " not found, set curent row 0";
        ui->chat_user_list->setCurrentRow(0);
        return;
    }

    ui->chat_user_list->setCurrentItem(find_iter.value());

    _cur_chat_uid = uid;
}

void ChatDialog::UpdateChatMsg(std::vector<std::shared_ptr<TextChatData> > text)
{   qDebug()<<"UpdateChatMsg";
    for(auto &aarr:text){
        if(aarr->_from_uid!=_cur_chat_uid){
            break;
        }
        ui->chat_page->AppendChatMsg(aarr);
    }
}



void ChatDialog::SetSelectChatPage(int uid)
{
    if( ui->chat_user_list->count() <= 0){
        return;
    }

    if (uid == 0) {
        auto item = ui->chat_user_list->item(0);
        //转为widget
        QWidget* widget = ui->chat_user_list->itemWidget(item);
        if (!widget) {
            return;
        }

        auto con_item = qobject_cast<CharUserList*>(widget);
        if (!con_item) {
            return;
        }

        //设置信息
        auto user_info = con_item->Getuser();
        ui->chat_page->SetUserInfo(user_info);
        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        return;
    }

    //转为widget
    QWidget *widget = ui->chat_user_list->itemWidget(find_iter.value());
    if(!widget){
        return;
    }

    //判断转化为自定义的widget
    // 对自定义widget进行操作， 将item 转化为基类ListItemBase
    Listitme *customItem = qobject_cast<Listitme*>(widget);
    if(!customItem){
        qDebug()<< "qobject_cast<ListItemBase*>(widget) is nullptr";
        return;
    }

    auto itemType = customItem->Geticontype();
    if(itemType == CHAT_USER_ITEM){
        auto con_item = qobject_cast<CharUserList*>(customItem);
        if(!con_item){
            return;
        }

        //设置信息
        auto user_info = con_item->Getuser();
        ui->chat_page->SetUserInfo(user_info);

        return;
    }

}

void ChatDialog::addChatUserList()
{
    auto friend_list=UserMgr::GetInstance()->GetFriendlist();
    /*if(friend_list.empty()){
        return;
    }*/
    qDebug()<<"addChatUserList()";
    for(auto friend_info:friend_list){
        if(friend_info==nullptr){
            continue;
        }
        auto user_info=std::make_shared<UserInfo>(friend_info);
        qDebug()<<"friend_info is not nill";
        auto *chat_user_wid = new CharUserList();
        chat_user_wid->SetInfo(user_info);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item, chat_user_wid);
        _chat_items_added.insert(friend_info->_uid, item);
    }

    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto user_info = std::make_shared<UserInfo>(0,names[name_i],
                                                    names[name_i],heads[head_i],0,strs[str_i]);
        auto *chat_user_wid = new CharUserList();
        chat_user_wid->SetInfo(user_info);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item, chat_user_wid);
    }
}


void ChatDialog::slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp){
    qDebug() << "receive slot_add_auth__friend uid is " << auth_rsp->_uid
             << " name is " << auth_rsp->_name << " nick is " << auth_rsp->_nick;

    bool sifriend=UserMgr::GetInstance()->CheckFriendById(auth_rsp->_uid);
    if(sifriend){
        return;
    }

    UserMgr::GetInstance()->AddFriend(auth_rsp);

    auto chatuserlist=new CharUserList();
    auto user_info = std::make_shared<UserInfo>(auth_rsp);
    chatuserlist->SetInfo(user_info);
    QListWidgetItem * item=new QListWidgetItem;
    item->setSizeHint(chatuserlist->sizeHint());
    ui->chat_user_list->insertItem(0,item);
    ui->chat_user_list->setItemWidget(item,chatuserlist);
    _chat_items_added.insert(auth_rsp->_uid, item);
}

void ChatDialog::slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info){
    qDebug() << "receive slot_add_auth__friend uid is " << auth_info->_uid
             << " name is " << auth_info->_name << " nick is " << auth_info->_nick;

    bool sifriend=UserMgr::GetInstance()->CheckFriendById(auth_info->_uid);
    if(sifriend){
        return;
    }

    UserMgr::GetInstance()->AddFriend(auth_info);

    auto chatuserlist=new CharUserList();
    auto user_info = std::make_shared<UserInfo>(auth_info);
    chatuserlist->SetInfo(user_info);
    QListWidgetItem * item=new QListWidgetItem;
    item->setSizeHint(chatuserlist->sizeHint());
    ui->chat_user_list->insertItem(0,item);
    ui->chat_user_list->setItemWidget(item,chatuserlist);
    _chat_items_added.insert(auth_info->_uid, item);
}

void ChatDialog::slot_jump_chat_item(std::shared_ptr<SearchInfo> si)
{

}

void ChatDialog::slot_loading_contact_user()
{
    if(_b_loading){
        return;
    }

    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    loadMoreConUser();
    loadingDialog->deleteLater();
    _b_loading = false;
}

void ChatDialog::slot_switch_friend_info_page(std::shared_ptr<UserInfo> user_info)
{
    _last_page=ui->friend_info_page;
    ui->friend_info_page->SetInfo(user_info);
    ui->stackedWidget->setCurrentWidget(ui->friend_info_page);
}

void ChatDialog::slot_switch_apply_friend_page()
{
    _last_page=ui->friend_apply_page;
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
}

void ChatDialog::slot_item_clicked(QListWidgetItem *item)
{
    QWidget * wid=ui->chat_user_list->itemWidget(item);
    if(!wid){
        qDebug()<< "slot item clicked widget is nullptr";
        return;
    }
    Listitme * list=qobject_cast<Listitme*>(wid);
    if(!list){
        return;
    }
    auto type=list->Geticontype();
    if(type==INVALID_ITEM  || type== ListItemType::GROUP_TIP_ITEM){
        qDebug()<< "slot invalid item clicked ";
        return;
    }

    if(type==CHAT_USER_ITEM){
        qDebug()<< "contact user item clicked ";
        auto chatwid=qobject_cast<CharUserList*>(list);
        auto user=chatwid->Getuser();
        _cur_chat_uid=user->_uid;
        ui->chat_page->SetUserInfo(user);
        return;
    }
}

void ChatDialog::slot_jump_chat_item_from_infopage(std::shared_ptr<UserInfo> user_info)
{
    auto info=_chat_items_added.find(user_info->_uid);
    if(info!=_chat_items_added.end()){
        ui->chat_user_list->scrollToItem(info.value());
        ui->side_chat_lb->SetSelected(true);
        SetSelectChatItem(user_info->_uid);
        //更新聊天界面信息
        SetSelectChatPage(user_info->_uid);
        slot_chat_lb_click();
        return;
    }

    auto* chat_user_wid = new CharUserList();
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chat_user_list->insertItem(0, item);
    ui->chat_user_list->setItemWidget(item, chat_user_wid);

    _chat_items_added.insert(user_info->_uid, item);

    ui->side_chat_lb->SetSelected(true);
    SetSelectChatItem(user_info->_uid);
    //更新聊天界面信息
    SetSelectChatPage(user_info->_uid);
    slot_chat_lb_click();
}

void ChatDialog::slot_append_send_chat_msg(std::shared_ptr<TextChatData> text)
{
    if(_cur_chat_uid==0){
        return;
    }

    auto itea=_chat_items_added.find(_cur_chat_uid);
    if(itea==_chat_items_added.end()){
        return;
    }

    QWidget * wid=ui->chat_user_list->itemWidget(itea.value());
    if(!wid){
        return;
    }

    Listitme * list=qobject_cast<Listitme*>(wid);
    auto type=list->Geticontype();
    if (type == CHAT_USER_ITEM) {
        auto con_item = qobject_cast<CharUserList*>(list);
        if (!con_item) {
            return;
        }

        //设置信息
        auto user_info = con_item->Getuser();
        user_info->_chat_msgs.push_back(text);
        //std::vector<std::shared_ptr<TextChatData>> msg_vec;
        //msg_vec.push_back(text);
        //UserMgr::GetInstance()->AppendFriendChatMsg(_cur_chat_uid,msg_vec);
        return;
    }




}

void ChatDialog::slot_text_chat_msg(std::shared_ptr<TextChatMsg> msg)
{
    qDebug()<<"slot_text_chat_msg";
    auto find_iter=_chat_items_added.find(msg->_from_uid);
    if(find_iter!=_chat_items_added.end()){
        qDebug() << "set chat item msg, uid is " << msg->_from_uid;
        QWidget * wid=ui->chat_user_list->itemWidget(find_iter.value());
        auto con_itea=qobject_cast<CharUserList*>(wid);
        if(!con_itea){
            qDebug()<<"con_itea is null";
            return;
        }
        qDebug()<<"con_itea is not null";
        con_itea->updateLastMsg(msg->_chat_msgs);
        UpdateChatMsg(msg->_chat_msgs);
        UserMgr::GetInstance()->AppendFriendChatMsg(msg->_from_uid,msg->_chat_msgs);
        return;
    }

    auto* chat_user_wid = new CharUserList();
    //查询好友信息
    auto fi_ptr = UserMgr::GetInstance()->GetFriendById(msg->_from_uid);
    chat_user_wid->SetInfo(fi_ptr);
    QListWidgetItem* item = new QListWidgetItem;
    qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    chat_user_wid->updateLastMsg(msg->_chat_msgs);
    UserMgr::GetInstance()->AppendFriendChatMsg(msg->_from_uid,msg->_chat_msgs);
    ui->chat_user_list->insertItem(0, item);
    ui->chat_user_list->setItemWidget(item, chat_user_wid);
    _chat_items_added.insert(msg->_from_uid, item);
}

