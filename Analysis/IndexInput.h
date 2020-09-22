#ifndef _INDEXINTPUT_H
#define _INDEXINTPUT_H
#include "structdef.h"
#include<fstream>
#include"FileSet.h"
#include<sstream>
using std::istringstream;
using std::string;
using std::ifstream;
using std::vector;
class CIndexInput
{
public:
	typedef std::map<std::string, TermInfo> TermInfoArray;
	CIndexInput();
	~CIndexInput();
	void readWorddict();
	void readFreq( MapIntInt& freqset, VecInt& docid);
	void readPrx( MapIntVecInt& postion);
private:
	TermInfoArray TermInfoTotal;
	int freqPostion;
	int prxPostion;
	int DocFreq;
	int sffuixlen;
	ifstream worddict;
	ifstream freq;
	ifstream prx;
};
#endif
