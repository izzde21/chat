#include"authenfriend.h"
#include "ui_authenfriend.h"
#include "customizeedit.h"
#include <QScrollBar>
#include"global.h"
#include"cilcklabel.h"
#include<QJsonObject>
#include "usermgr.h"
#include "tcpmgr.h"
AuthenFriend::AuthenFriend(QWidget *parent)
    : QDialog(),_label_point(2,2)
    , ui(new Ui::AuthenFriend)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("ApplyFriend");
    this->setModal(true);
    ui->name_ed->setPlaceholderText("薇古丝");
    ui->back_ed->setPlaceholderText("friend");
    //ui->lb_ed->setPlaceholderText("搜索、添加标签");

    ui->lb_ed->move(2, 2);
    ui->lb_ed->setFixedHeight(20);
    ui->lb_ed->setMaxLength(10);
    ui->input_tip_wid->hide();
    ui->input_tip_wid->hide();
    _tip_cur_point=QPoint(5,5);

    _tip_data = { "同学","家人","菜鸟教程","C++ Primer","Rust 程序设计",
                 "父与子学Python","nodejs开发指南","go 语言开发指南",
                 "游戏伙伴","金融投资","微信读书","拼多多拼友" };
    connect(ui->more_lb,&ClickedOnceLabel::clicked,this,&AuthenFriend::Slotmoretip);
    connect(ui->lb_ed,&CustomizeEdit::returnPressed,this,&AuthenFriend::Slotpressenter);
    connect(ui->lb_ed,&CustomizeEdit::textChanged,this,&AuthenFriend::Slottextchange);
    connect(ui->lb_ed,&CustomizeEdit::editingFinished,this,&AuthenFriend::Sloteditfinish);
    connect(ui->tip_lb,&ClickedOnceLabel::clicked,this,&AuthenFriend::Slottipclick);

    ui->scrollArea->verticalScrollBar()->setHidden(true);
    ui->scrollArea->horizontalScrollBar()->setHidden(true);
    ui->scrollArea->installEventFilter(this);

    ui->sure_btn->SetStatu("normal","hover","press");
    ui->cancel_btn->SetStatu("normal","hover","press");

    connect(ui->sure_btn,&Clickedbtn::clicked,this,&AuthenFriend::Slotsurebtnclick);
    connect(ui->cancel_btn,&Clickedbtn::clicked,this,&AuthenFriend::Slotcancelbtnclick);
    InitTipLbs();
}
void AuthenFriend::InitTipLbs(){
    int lines = 1;
    for(int i = 0; i < _tip_data.size(); i++){

        auto* lb = new cilcklabel(ui->lb_list);
        lb->setstatu("normal", "hover", "pressed", "selected_normal",
                     "selected_hover", "selected_pressed");
        lb->setObjectName("tipslb");
        lb->setText(_tip_data[i]);
        connect(lb, &cilcklabel::clicked, this, &AuthenFriend::SlotChangeFriendLabelByTip);

        QFontMetrics fontMetrics(lb->font()); // 获取QLabel控件的字体信息
        int textWidth = fontMetrics.horizontalAdvance(lb->text()); // 获取文本的宽度
        int textHeight = fontMetrics.height(); // 获取文本的高度

        if (_tip_cur_point.x() + textWidth + tip_offset > ui->lb_list->width()) {
            lines++;
            if (lines > 2) {
                delete lb;
                return;
            }

            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);

        }

        auto next_point = _tip_cur_point;

        AddTipLBS(lb, _tip_cur_point,next_point, textWidth, textHeight);

        _tip_cur_point = next_point;
    }
}

//把标签放在lb_edit上
void AuthenFriend::addlabel(QString name){
    if (_friend_labels.find(name) != _friend_labels.end()) {
        ui->lb_ed->clear();
        return;
    }

    auto tmplabel = new FriendLabel(ui->gridWidget);
    tmplabel->settext(name);
    tmplabel->setObjectName("FriendLabel");

    auto max_width = ui->gridWidget->width();
    //todo... 添加宽度统计
    if (_label_point.x() + tmplabel->width() > max_width) {
        _label_point.setY(_label_point.y() + tmplabel->height() + 15);
        _label_point.setX(2);
    }
    else {

    }


    tmplabel->move(_label_point);
    tmplabel->show();
    _friend_labels[tmplabel->text()] = tmplabel;
    _friend_labels_key.push_back(tmplabel->text());

    connect(tmplabel, &FriendLabel::sig_close, this, &AuthenFriend::SlotRemoveFriendLabel);

    _label_point.setX(_label_point.x() + tmplabel->width() + 70);

    if (_label_point.x() + MIN_APPLY_LABEL_ED_LEN > ui->gridWidget->width()) {
        ui->lb_ed->move(2, _label_point.y() + tmplabel->height() + 2);
    }
    else {
        ui->lb_ed->move(_label_point);
    }

    ui->lb_ed->clear();

    if (ui->gridWidget->height() < _label_point.y() + tmplabel->height() + 2) {
        ui->gridWidget->setFixedHeight(_label_point.y() + tmplabel->height() * 2 + 2);
    }
}

void AuthenFriend::Slotpressenter(){
    if(ui->lb_ed->text().isEmpty()){
        return;
    }

    auto text = ui->lb_ed->text();

    addlabel(ui->lb_ed->text());

    ui->input_tip_wid->hide();

    auto find_it = std::find(_tip_data.begin(), _tip_data.end(), text);
    if (find_it == _tip_data.end()) {
        _tip_data.push_back(text);
    }

    //判断标签展示栏是否有该标签
    auto find_add = _add_labels.find(text);
    if (find_add != _add_labels.end()) {
        find_add.value()->SetCurState(ClickLbState::Selected);
        return;
    }

    //标签展示栏也增加一个标签, 并设置绿色选中
    auto* lb = new cilcklabel(ui->lb_list);
    lb->setstatu("normal", "hover", "pressed", "selected_normal",
                 "selected_hover", "selected_pressed");
    lb->setObjectName("tipslb");
    lb->setText(text);
    connect(lb, &cilcklabel::clicked, this, &AuthenFriend::SlotChangeFriendLabelByTip);


    QFontMetrics fontMetrics(lb->font()); // 获取QLabel控件的字体信息
    int textWidth = fontMetrics.horizontalAdvance(lb->text()); // 获取文本的宽度
    int textHeight = fontMetrics.height(); // 获取文本的高度
    qDebug() << "textWidth is " << textWidth;

    if (_tip_cur_point.x() + textWidth + tip_offset + 3 > ui->lb_list->width()) {

        _tip_cur_point.setX(5);
        _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);

    }

    auto next_point = _tip_cur_point;

    AddTipLBS(lb, _tip_cur_point, next_point, textWidth, textHeight);
    _tip_cur_point = next_point;

    int diff_height = next_point.y() + textHeight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textHeight + tip_offset);

    lb->SetCurState(ClickLbState::Selected);

    ui->scrollcontent->setFixedHeight(ui->scrollcontent->height() + diff_height);
}

void AuthenFriend::Slottextchange(const QString& text){
    if(text.isEmpty()){
        ui->input_tip_wid->hide();
        return;
    }

    auto itea=std::find(_tip_data.begin(),_tip_data.end(),text);
    if(itea==_tip_data.end()){
        auto _text=add_prefix+text;
        ui->tip_lb->setText(_text);
        ui->input_tip_wid->show();
        return;
    }
    ui->tip_lb->setText(text);
    ui->input_tip_wid->show();
}

void AuthenFriend::Sloteditfinish(){
    ui->input_tip_wid->hide();
}

void AuthenFriend::Slottipclick(QString text){
    auto index=text.indexOf(add_prefix);
    if(index!=-1){
        text=text.mid(index+add_prefix.length());
    }
    addlabel(text);

    auto find_it = std::find(_tip_data.begin(), _tip_data.end(), text);
    if(find_it!=_tip_data.end()){
        _tip_data.push_back(text);
    }

    auto add_tip = _add_labels.find(text);
    if(add_tip!=_add_labels.end()){
        add_tip.value()->SetCurState(Selected);
        return;
    }
    auto* lb = new cilcklabel(ui->lb_list);
    lb->setstatu("normal", "hover", "pressed", "selected_normal",
                 "selected_hover", "selected_pressed");
    lb->setObjectName("tipslb");
    lb->setText(text);
    connect(lb, &cilcklabel::clicked, this, &AuthenFriend::SlotChangeFriendLabelByTip);
    qDebug() << "ui->lb_list->width() is " << ui->lb_list->width();
    qDebug() << "_tip_cur_point.x() is " << _tip_cur_point.x();

    QFontMetrics fontMetrics(lb->font()); // 获取QLabel控件的字体信息
    int textWidth = fontMetrics.horizontalAdvance(lb->text()); // 获取文本的宽度
    int textHeight = fontMetrics.height(); // 获取文本的高度
    qDebug() << "textWidth is " << textWidth;

    if (_tip_cur_point.x() + textWidth+ tip_offset+3 > ui->lb_list->width()) {

        _tip_cur_point.setX(5);
        _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);

    }

    auto next_point = _tip_cur_point;

    AddTipLBS(lb, _tip_cur_point, next_point, textWidth,textHeight);
    _tip_cur_point = next_point;

    int diff_height = next_point.y() + textHeight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textHeight + tip_offset);

    lb->SetCurState(ClickLbState::Selected);

    ui->scrollcontent->setFixedHeight(ui->scrollcontent->height()+ diff_height );
}

void AuthenFriend::Slotmoretip(){
    _tip_cur_point=QPoint(5,5);
    setFixedWidth(360);
    auto next_point=_tip_cur_point;
    int height;
    int width;
    for(auto &key:_add_labels_key){
        auto lb=_add_labels[key];
        lb->setstatu("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
        lb->setText(key);

        QFontMetrics font(lb->font());
        height=font.height();
        width=font.horizontalAdvance(lb->text());
        if(_tip_cur_point.x()+width+tip_offset>ui->lb_list->width()){
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(height+15+_tip_cur_point.y());
        }
        lb->move(_tip_cur_point);
        next_point.setX(_tip_cur_point.x()+width+30);
        next_point.setY(_tip_cur_point.y());

        _tip_cur_point=next_point;
    }

    for(int i = 0; i < _tip_data.size(); i++){
        auto iter = _add_labels.find(_tip_data[i]);
        if(iter != _add_labels.end()){
            continue;
        }

        auto* lb = new cilcklabel(ui->lb_list);
        lb->setstatu("normal", "hover", "pressed", "selected_normal",
                     "selected_hover", "selected_pressed");
        lb->setObjectName("tipslb");
        lb->setText(_tip_data[i]);
        connect(lb, &cilcklabel::clicked, this, &AuthenFriend::SlotChangeFriendLabelByTip);

        QFontMetrics fontMetrics(lb->font()); // 获取QLabel控件的字体信息
        int textWidth = fontMetrics.horizontalAdvance(lb->text()); // 获取文本的宽度
        int textHeight = fontMetrics.height(); // 获取文本的高度

        if (_tip_cur_point.x() + textWidth + tip_offset > ui->lb_list->width()) {

            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);

        }

        next_point = _tip_cur_point;

        AddTipLBS(lb, _tip_cur_point, next_point, textWidth, textHeight);

        _tip_cur_point = next_point;

    }

    int diff_height = next_point.y() + height + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + height + tip_offset);

    //qDebug()<<"after resize ui->lb_list size is " <<  ui->lb_list->size();
    ui->scrollcontent->setFixedHeight(ui->scrollcontent->height()+diff_height);
}


void AuthenFriend::Slotsurebtnclick(){
    qDebug() << "Slot Apply Sure called" ;
    auto name=ui->name_ed->text();
    if(name.isEmpty()){
        name=ui->name_ed->placeholderText();
    }

    auto backed=ui->back_ed->text();
    if(backed.isEmpty()){
        backed=ui->back_ed->placeholderText();
    }


    QJsonObject jsonobj;
    jsonobj["uid"]=UserMgr::GetInstance()->Getuserinfo()->_uid;
    jsonobj["applyname"]=name;
    jsonobj["bakname"]=backed;
    jsonobj["touid"]=_si->_uid;
    qDebug() << "uid is"<<UserMgr::GetInstance()->Getuserinfo()->_uid;
    QJsonDocument doc(jsonobj);
    QByteArray  jsonData =doc.toJson(QJsonDocument::Compact);
    emit TcpMgr::GetInstance()->sig_send_meg(ID_AUTH_FRIEND_REQ,jsonData);
    this->hide();
    deleteLater();
}

void AuthenFriend::Slotcancelbtnclick(){
    this->hide();
    deleteLater();
}

AuthenFriend::~AuthenFriend()
{
    delete ui;
}
//把标签放在label_list上
void AuthenFriend::AddTipLBS(cilcklabel* lb,QPoint cur_point,QPoint &next_point,int text_width,int text_hight){
    lb->move(cur_point);
    lb->show();
    _add_labels_key.push_back(lb->text());
    _add_labels.insert(lb->text(),lb);

    next_point.setX(lb->x()+30+text_width);
    next_point.setY(lb->y());
}

bool AuthenFriend::eventFilter(QObject *obj, QEvent *event){
    if (obj == ui->scrollArea && event->type() == QEvent::Enter)
    {
        ui->scrollArea->verticalScrollBar()->setHidden(false);
    }
    else if (obj == ui->scrollArea && event->type() == QEvent::Leave)
    {
        ui->scrollArea->verticalScrollBar()->setHidden(true);
    }
    return QObject::eventFilter(obj, event);
}

void AuthenFriend::SetSearchInfo(std::shared_ptr<ApplyInfo> si){
    _si=si;
}

void AuthenFriend::resetLabels()
{
    auto max_width = ui->gridWidget->width();
    auto label_height = 0;
    for(auto iter = _friend_labels.begin(); iter != _friend_labels.end(); iter++){
        //todo... 添加宽度统计
        if( _label_point.x() + iter.value()->width() > max_width) {
            _label_point.setY(_label_point.y()+iter.value()->height()+6);
            _label_point.setX(2);
        }

        iter.value()->move(_label_point);
        iter.value()->show();

        _label_point.setX(_label_point.x()+iter.value()->width()+2);
        _label_point.setY(_label_point.y());
        label_height = iter.value()->height();
    }

    if(_friend_labels.isEmpty()){
        ui->lb_ed->move(_label_point);
        return;
    }

    if(_label_point.x() + MIN_APPLY_LABEL_ED_LEN > ui->gridWidget->width()){
        ui->lb_ed->move(2,_label_point.y()+label_height+6);
    }else{
        ui->lb_ed->move(_label_point);
    }
}


void AuthenFriend::SlotChangeFriendLabelByTip(QString lbtext, ClickLbState state){
    auto itea=_add_labels.find(lbtext);
    if(itea==_add_labels.end()){
        return;
    }

    if(state==Selected){
        addlabel(lbtext);
        return;
    }

    if(state==Normal){
        SlotRemoveFriendLabel(lbtext);
        return;
    }
}

void AuthenFriend::SlotRemoveFriendLabel(QString name)
{
    _label_point.setX(2);
    _label_point.setY(6);

    auto find_iter = _friend_labels.find(name);

    if(find_iter == _friend_labels.end()){
        return;
    }

    auto find_key = _friend_labels_key.end();
    for(auto iter = _friend_labels_key.begin(); iter != _friend_labels_key.end();
         iter++){
        if(*iter == name){
            find_key = iter;
            break;
        }
    }

    if(find_key != _friend_labels_key.end()){
        _friend_labels_key.erase(find_key);
    }


    delete find_iter.value();

    _friend_labels.erase(find_iter);

    resetLabels();

    auto find_add = _add_labels.find(name);
    if(find_add == _add_labels.end()){
        return;
    }

    find_add.value()->ResetNormalState();
}
