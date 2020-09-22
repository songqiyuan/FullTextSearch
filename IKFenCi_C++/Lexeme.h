#ifndef _LEXEME_H_
#define _LEXEME_H_
#pragma once
#include<list>
#include<string>
//词元表

class CLexeme;
typedef std::list<CLexeme>::iterator lexemeIter;
typedef std::list<CLexeme>::reverse_iterator RIter;
class CLexemePath;
class CQuickSortSet
{
public:
	//从小到大排序插入
	bool addLexeme(CLexeme lexxme);
	//获取路径
	std::list<CLexeme>& getLexemePath();
	CLexeme peekLast();
	CQuickSortSet() {}
	~CQuickSortSet() {}
//private:
protected:
	std::list<CLexeme> lexemeset;
};
class CLexeme
{
public:
	enum LexemeType
	{
		//lexemeType常量
		//未知
		TYPE_UNKNOWN = 0,
		//英文
		TYPE_ENGLISH = 1,
		//数字
		 TYPE_ARABIC = 2,
		//英文数字混合
		 TYPE_LETTER = 3,
		//中文词元
		TYPE_CNWORD = 4,
		//中文单字
		 TYPE_CNCHAR = 64,
		//日韩文字
		 TYPE_OTHER_CJK = 8,
		//中文数词
		 TYPE_CNUM = 16,
		//中文量词
		TYPE_COUNT = 32,
		//中文数量词
		 TYPE_CQUAN = 48,
	};
public:
	CLexeme();
	CLexeme(int begin, int length, int lexemeType);
public:
	//按照位置比较大小
	int compareTo(CLexeme other);
	//判断词元相等
	bool equals(CLexeme o);

	int getBegin();
	int getLength();
	std::string getText();
	void setText(std::string text)
	{
		_text = text;
	}

private:
	//词的开始位置
	size_t _begin;
	//词的结束位置
	size_t _length;
	//词元文本
	std::string _text;
	//词元类型
	int _lexemeType;
};

class CLexemePath:public CQuickSortSet
{
public:
	CLexemePath();
	CLexemePath(int pathBegin, int pathEnd, int payloadLength);
	bool addCrossLexeme(CLexeme lexeme);
	bool addNotCrossLexeme(CLexeme lexeme);
	bool checkCross(CLexeme lexeme);
	int getPathBegin() {
		return _pathBegin;
	}

	int getPathEnd() {
		return _pathEnd;
	}

	
	 //获取Path的有效词长
	int getPayloadLength() {
		return _payloadLength;
	}

	//跨度
	int getPathLength() {
		return _pathEnd - _pathBegin;
	}
	CLexemePath copyPath();
	//权重计算
	int getXWeight();
	int getPWeight();
	//比较词元链的大小，即寻找最优解
	//删除词
	void DeleteWordTail();
	int compareTo(CLexemePath o);
private:
	//CQuickSortSet _sortSet;
	int _pathBegin;
	int _pathEnd;
	int _payloadLength;
};

#endif // !_LEXEME_H_



