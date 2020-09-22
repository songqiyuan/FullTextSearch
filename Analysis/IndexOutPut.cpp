#include "IndexOutPut.h"
CIndexOutput::CIndexOutput()
{}
CIndexOutput::CIndexOutput(shared_ptr<CDocumentDeal> DocDeal) :
	DocumentDeal(DocDeal)
{

}
CIndexOutput::~CIndexOutput()
{

}

bool CIndexOutput::UrlToDoc(string &path) const
{
	
	DocumentDeal->UrlToDoc(path);
	return true;
}
bool CIndexOutput::PostingList(string &path, string &path1, string &path2)const
{
	DocumentDeal->PostingList(path,path1,path2);
	return true;
}
bool CIndexOutput::DocInfoMap(string &path) const
{
	DocumentDeal->DocInfoMap(path);
	return true;
}
