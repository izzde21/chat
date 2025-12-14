#include "userdata.h"

SearchInfo::SearchInfo(int Uid, QString name, QString nike, QString desc, int sex,QString icon)
    :_uid(Uid),_name(name),_nick(nike),_desc(desc),_sex(sex),_icon(icon)
{

}

void FriendInfo::AppendChatMsgs(const std::vector<std::shared_ptr<TextChatData> > text_vec)
{
    qDebug()<<"AppendChatMsgs";
    for(const auto & text: text_vec){
        _chat_msgs.push_back(text);
    }
}
