//分词前的配置，主要用来加载词典,以及智能分词
#ifndef _CONFIGURATIO_H__
#define _CONFIGURATIO_H__
#pragma once
#include"DictSegment.h"

#include<string>
#include<vector>

const string DICTFILENAME("words.dict");
//const string DICTFILENAME("words.dic");
//const string DICTFILENAME("main2012S.dic");
const string DICTFILENAME1("quantifierS.dic");
const string STOPDICT("stop.dict");
const string CSTOPDICT("CStopword.dict");

class CConfiguration
{
public:
	CConfiguration();
	~CConfiguration();
	bool getuseSmart();
	void setUseSmart(bool usesmart);
	std::string getMainDictionary();
	std::string getQuantifierDicionary();
	std::vector<std::string> getExtDictionarys();
	std::vector<std::string> getExtStopWordDictionarys();
	//
	CDictSegment& getMainDict()
	{
		return _MainDict;
	}
protected:
	//初始化
	void _init();
	//加载主词典
	void loadMainDict();
	//加载量词词典
	void loadQuantDict();
	//加载停止词词典
	void loadStopDict();
private:
	//主词典以及量词词典
	static std::string PATH_DIC_MAIN;
	static std::string PATH_DIC_QUANTIFIER;
	bool useSmart;
	//主词典
	CDictSegment _MainDict;
	//量词词典
	CDictSegment _QuantDict;
	//扩展词典
	CDictSegment _StopWordDict;
};
#endif // !_CONFIGURATIO_H__
