#ifndef _DOCUMENTDEAL_H_
#define _DOCUMENTDEAL_H_
#include "HzSeg.h"
#include "structdef.h"
#include "FileSet.h"
#include <string.h>
#pragma once
class CDocumentDeal
{
public:
	CDocumentDeal();
	~CDocumentDeal();
	void DocIndex(const string& file = DATAFILE);
	void DocTermIndex(CDict& dict, const string& file = DATAFILE);
	void RemoveTags(char *s);
	bool PostingList(const string &path, const string &path1, const string &path2)const;
	bool UrlToDoc(const string &path) const;
	bool DocInfoMap(const string &path)const;
	size_t suffixLen(const string& str1, const string& str2) const;
private:
	map<string,TermInfo> TermInfoTotal;
	vector<UrlInfo> UrlInfoTotal;
	vector<DocInfo> DocInfoTotal;
};
#endif
