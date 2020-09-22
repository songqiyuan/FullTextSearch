#ifndef _INDEXOUTPUT_H_
#define _INDEXOUTPUT_H_
#include "DocumentDeal.h"
#include<memory>
class CIndexOutput
{
public:
	CIndexOutput();
	CIndexOutput(shared_ptr<CDocumentDeal> DocDeal);
	~CIndexOutput();
	bool PostingList(string &path, string &path1, string &path2) const;
	bool UrlToDoc(string &path) const;
	bool DocInfoMap(string &path)const;
private:
	shared_ptr<CDocumentDeal> DocumentDeal;
};
#endif
