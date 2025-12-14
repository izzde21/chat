#ifndef SEARCHLIST_H
#define SEARCHLIST_H

#include <QListWidget>
#include<QEvent>
#include<QWheelEvent>
#include<QScrollBar>
#include "loadingdlg.h"
#include"userdata.h"
class SearchList : public QListWidget
{
    Q_OBJECT
public:
    SearchList(QWidget *parent = nullptr);
    void CloseFinDig();
    void SetSearchItme(QWidget * w);
    bool eventFilter(QObject *object, QEvent *event) override{
        if(this->viewport()==object){
            if(event->type()== QEvent::Enter){
                this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            }else if (event->type() == QEvent::Leave)
            {
                this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            }
        }

        if(this->viewport()==object && event->type()==QEvent::Wheel){
            QWheelEvent* qwe=static_cast<QWheelEvent*>(event);
            int numDegrees =qwe->angleDelta().y()/8;
            int numdis=numDegrees/15;
            this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numdis);
            return true;
        }
        return QListWidget::eventFilter(object, event);
    }
    void SetSearchEdit(QWidget* edit);
private:
    void waitPending(bool pending = true);
    bool _send_pending;
    void addTipItem();
    std::shared_ptr<QDialog> _find_dlg;
    QWidget* _search_edit;
    LoadingDlg * _loadingDialog;
signals:
    void sig_jump_chat_item(std::shared_ptr<SearchInfo> si);
private slots:
    void slot_item_clicked(QListWidgetItem *item);
    void slot_user_search(std::shared_ptr<SearchInfo> si);
};


#endif // SEARCHLIST_H
