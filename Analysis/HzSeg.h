#ifndef _HZSEG_H_040415_
#define _HZSEG_H_040415_
#include<set>
#include<algorithm>
#include "Dict.h"
const string SEPARATOR("/  ");
class CHzSeg
{
public:
	CHzSeg();
	~CHzSeg();
	string SegmentSentenceMM(CDict&, string) const;
	string SegmentHzStrMM(CDict&, string) const;
	string SegmengHzEnglish(string) const;
	string SegmentURL(CDict&, string) const {}
	void Translate(char* SourceStr) const {}
private:
	set<string> stopword;
};
#endif
