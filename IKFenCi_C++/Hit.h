#ifndef _HIT_H__
#define _HIT_H__
#pragma once
#include "DefineStruct.h"
class CHit
{
public:
	CHit();
	~CHit();
	void setMatch();
	void setText(const string str);
	void cancelText()
	{
		_text = "";
	}
	string getText();
	void displayText();
	void setPrefix();
	void setNotMatch();
	void cancelMatch()
	{
		if (isMatch())
		{
			_match -= MATCH;
		}
	}
	void cancelPrefix()
	{
		if (isPrefix())
		{
			_match -= PREFIX;
		}
	}
	bool isNotMatch();
	bool isMatch();
	bool isPrefix();
	int getMatch();
	void setCurrNode(const signleNode& hitNode);

	signleNode getCurrNode();
public:
	//位置
	void setBegin(int begin)
	{
		_begin = begin;
	}
	void setEnd(int end)
	{
		_end = end;
	}
	int getBegin()
	{
		return _begin;
	}
	int getEnd()
	{
		return _end;
	}
private:
	enum Match
	{
		NOT_MATCH = 0,
		PREFIX = 0x00000001,
		MATCH = 0x00000010
	};
	int _match;
	int _begin;
	int _end;
	string _text;
	signleNode _HitNode;
};
#endif // !_HIT_H__



