#pragma once
#include"const.h"
class MsgNode
{
public:
	MsgNode(short max_len) :total_len(max_len), cur_len(0) {
		_data = new char[total_len + 1]();
		_data[total_len] = '\0';
	}

	~MsgNode() {
		delete[] _data;
		cur_len = 0;
	}

	void Clear() {
		memset(_data, 0, total_len);
	}

	short total_len;
	short cur_len;
	char* _data;
};

class RecvNode:public MsgNode
{
public:
	RecvNode(short max_len,short id);
	~RecvNode();
	short msg_id;
};


class SendNode :public MsgNode
{
public:
	SendNode(const char* _data,short max_len, short id);
	~SendNode();
	short msg_id;
};