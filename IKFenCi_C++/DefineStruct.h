#ifndef _DEFINESTRCUT_H__
#define _DEFINESTRCUT_H__
#pragma once
#include<string>

#include<vector>
#include<map>
#include <set>
#include <unordered_set>
#include <algorithm>
using std::string;
struct signleNode;
typedef std::map<string, signleNode> WordNode;
typedef std::map<string, signleNode>::iterator Iter;
typedef std::map<string, signleNode>::const_iterator CIter;
//字典树节点 endFlag为true表示是一个完整的词
struct signleNode
{
	bool endFlag;
	WordNode childnode;
};
#endif // !_DEFINESTRCUT_H__


