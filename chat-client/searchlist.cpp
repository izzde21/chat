#include "searchlist.h"
#include"tcpmgr.h"
#include"adduseritem.h"
#include"findsuccessdlg.h""
#include "customizeedit.h"
#include<QJsonObject>
#include "findfaildlg.h"
#include"usermgr.h"
SearchList::SearchList(QWidget *parent):QListWidget(parent),_send_pending(false),_find_dlg(nullptr),
 _search_edit(nullptr)
{
    _loadingDialog=nullptr;
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);

    connect(this, &QListWidget::itemClicked, this, &SearchList::slot_item_clicked);
    //添加条目
    addTipItem();
    //连接搜索条目
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_user_search, this, &SearchList::slot_user_search);
}

void SearchList::waitPending(bool pending){
    if(pending){
        _loadingDialog=new LoadingDlg(this);
        _loadingDialog->setModal(true);
        _loadingDialog->show();
        _send_pending=pending;
    }
    else{
        _loadingDialog->hide();
        _loadingDialog->deleteLater();
        _send_pending=pending;
    }
}

void SearchList::addTipItem(){
    QWidget* invalid_item =new QWidget;
    QListWidgetItem * item_tmp=new QListWidgetItem;
    item_tmp->setSizeHint(QSize(250,10));
    this->addItem(item_tmp);
    invalid_item->setObjectName("invalid_item");
    this->setItemWidget(item_tmp,invalid_item);
    item_tmp->setFlags(item_tmp->flags() & ~Qt::ItemIsSelectable);



    auto * add_user_item =new AddUserItem();
    QListWidgetItem * item=new QListWidgetItem;
    item->setSizeHint(add_user_item->size());
    this->addItem(item);
    this->setItemWidget(item,add_user_item);
}
void SearchList::SetSearchEdit(QWidget* edit){
    _search_edit=edit;
}

void SearchList::slot_item_clicked(QListWidgetItem *item){
    QWidget * widget =itemWidget(item);
    if(!item){
        return;
    }
    auto type=static_cast<Listitme*>(widget)->Geticontype();
    if(type==INVALID_ITEM){
        return;
    }

    if(type==ADD_USER_TIP_ITEM){
        if(_send_pending){
            return;
        }
        if(!_search_edit){
            return;
        }
        waitPending(true);
        auto search_edit=dynamic_cast<CustomizeEdit*>(_search_edit);
        if(!search_edit){
            return;
        }
        auto str=search_edit->text();
        QJsonObject jsonobj;
        jsonobj["uid"]=str;
        QJsonDocument doc(jsonobj);
        QByteArray data=doc.toJson(QJsonDocument::Compact);
        emit TcpMgr::GetInstance()->sig_send_meg(ID_SEARCH_USER_REQ,data);
        return;
    }
    CloseFinDig();
}

void SearchList::CloseFinDig()
{
    if(_find_dlg){
        _find_dlg->hide();
        _find_dlg = nullptr;
    }
}

void SearchList::slot_user_search(std::shared_ptr<SearchInfo> si){
    waitPending(false);
    if(si==nullptr){
        _find_dlg=std::make_shared<FindFailDlg>(this);
    }
    else{
        auto self_uid=UserMgr::GetInstance()->Getuserinfo()->_uid;
        if(si->_uid==self_uid){
            return;
        }
        bool ex=UserMgr::GetInstance()->CheckFriendById(si->_uid);
        if(ex){
            emit sig_jump_chat_item(si);
            return;
        }
        _find_dlg=std::make_shared<FindSuccessDlg>(this);
        std::dynamic_pointer_cast<FindSuccessDlg>(_find_dlg)->SetSearchInfo(si);
    }
    _find_dlg->show();
}
