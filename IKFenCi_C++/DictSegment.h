#ifndef _DICTSEGMENG_H__
#define _DICTSEGMENG_H__
#pragma once

//#include "DefineStruct.h"
#include "Hit.h"
//匹配判定

class CDictSegment
{
public:



	CDictSegment();
	~CDictSegment();
	void display();

	//填充字典树
	void fillSegment(string str);
	//字符串匹配
	void match(string &str, CHit &Hit);
	void match(string &str, CHit& Hit,const WordNode& node);
protected:
	//填充字典树
	void fillSegment(string str,std::map<string, signleNode>& node);

private:
	bool isChar(unsigned char ch);
private:
	WordNode  _wordnode;

};
#endif // !_DICTSEGMENG_H__



