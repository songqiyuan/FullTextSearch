#ifndef _STRUCTDEF_H_
#define _STRUCTDEF_H_
#include<vector>
#include<string>
#include<map>

typedef std::vector<int> VecInt;
typedef std::map<int, VecInt> MapIntVecInt;
typedef std::map<int, int> MapIntInt;

struct TermInfo
{
	std::string s_text;
	VecInt s_DocId;
	MapIntVecInt s_postion;
	MapIntInt s_freq;
};

struct UrlInfo
{
	int s_DocId;
	std::string s_Url;
};

struct DocInfo
{
	int s_DocId;
	int s_length;
	int s_offest;
};

#endif
