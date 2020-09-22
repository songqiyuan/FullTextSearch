#ifndef _DICT_H_040401_
#define _DICT_H_040401_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream>
#include "mmseg.h"
using namespace std;

const string DICTFILENAME("words.dict");
const string DICTFILENAME1("words.dic");


typedef struct{
	int id;
	string word;
	int freq;
} dictentry;


class CDict
{

public:
	CDict();
	~CDict();

	bool GetFreq(string&) const { return false; };
	bool IsWord(string&) const;
	void AddFreq(string&) {};
	void display();

private:
	map<string, int> mapDict;
	MMSeg mmseg;
	void OpenDict();
};

#endif
