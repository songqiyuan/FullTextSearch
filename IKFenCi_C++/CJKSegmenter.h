#ifndef _CJKSEGMENTER_H_
#define _CJKSEGMENTER_H_
#pragma once
#include"Configuration.h"
#include "DictSegment.h"
#include"Lexeme.h"
#include<iostream>
#include <vector>
#include <stack>
#include <queue>
//typedef std::priority_queue<CLexeme> lexemePathQueue;
typedef std::stack<lexemeIter> sIter;
//用于优先队列，使用小顶堆
struct cmpPath
{
	bool operator()(CLexemePath o1, CLexemePath o2)
	{
		return o1.compareTo(o2) > 0;
	}
};
typedef std::priority_queue<CLexemePath, std::vector<CLexemePath>, cmpPath> PathSortSet;

class CCJKSegmenter
{
public:
	bool Analyzer(string& str);
	void reset();
	void distext(string str);
	void setConfiguration(const CConfiguration& cfg)
	{
		_cfg = cfg;
	}
	CCJKSegmenter();
	~CCJKSegmenter();
	//智能化处理
	void setSmart(bool useSmart)
	{
		_cfg.setUseSmart(useSmart);
	}
	bool getSmart()
	{
		return _cfg.getuseSmart();
	}
	sIter forwardPath(lexemeIter leIterStart, lexemeIter leIterEnd,CLexemePath& options);
public:
	//分词歧义处理
	void process();
	CLexemePath judge(CLexemePath &lexemePath);
	void backPath(CLexeme l, CLexemePath& option);
	bool addResult();
private:
	//前缀队列
	CDictSegment _dictTree;
	std::vector<CHit> Hit;
	static string SEGMENTER_NAME ;
	CConfiguration _cfg;
	CQuickSortSet _sortSet; //第一次分词结果，未进行歧义处理
	CLexeme _lexeme;
	int _currPos;
	std::vector<CLexemePath> _pathSet;
	std::list<CLexeme> result;
	int length;
};
#endif // !_CJKSEGMENTER_H_


