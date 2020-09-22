#include "DocumentDeal.h"

const int HEADER_BUF_SIZE = 1024;

CDocumentDeal::CDocumentDeal()
{

}

CDocumentDeal::~CDocumentDeal()
{
	TermInfoTotal.clear();
	UrlInfoTotal.clear();
	DocInfoTotal.clear();
}

void CDocumentDeal::DocIndex(const string& file)
{
	ifstream InputData(file.c_str(),ifstream::in);
	if (!InputData)
	{
		cout << "Cannot open in CDocumentDeal DocIndex" << endl;
		return;
	}

	int cnt = 0;
	string strLine;
	string strPage;
	int nOffset = InputData.tellg();
	UrlInfo Url;
	DocInfo Doc;
	while (getline(InputData, strLine))
	{
		if (strLine[0] == '\0' || strLine[0] == '#' || strLine[0] == '\n')
		{
			nOffset = InputData.tellg();
			continue;
		}

		if (!strncmp(strLine.c_str(), "version: 1.0", 12))
		{
			if (!getline(InputData, strLine))
			{
				break;
			}

			if (!strncmp(strLine.c_str(), "url: ", 4))
			{
				Url.s_Url = strLine.substr(5);

			}
			else
			{
				continue;
			}
			while (getline(InputData, strLine))
			{
				if (!strncmp(strLine.c_str(), "length: ", 8))
				{
					sscanf(strLine.substr(8).c_str(), "%d", &(Doc.s_length));
					break;
				}
			}
			getline(InputData, strLine);
			Url.s_DocId = cnt;
			Doc.s_DocId = cnt;
			Doc.s_offest = nOffset;

			char* pContent = new char[Doc.s_length + 1];
			memset(pContent, 0, Doc.s_length + 1);
			InputData.read(pContent, Doc.s_length);

			delete[] pContent;
			UrlInfoTotal.push_back(Url);
			DocInfoTotal.push_back(Doc);
			cnt++;
		}
		nOffset = InputData.tellg();
	}
	DocInfoTotal.push_back(Doc);
	return;
}

void CDocumentDeal::DocTermIndex(CDict& dict,const string& file)
{
	ifstream InputData(file.c_str(), ifstream::in);
	if (!InputData)
	{
		cout << "Cannot open in CDocumentDeal DocTermIndex" << endl;
		return;
	}
	CHzSeg hzSeg;
	string result;
	int DocCount = DocInfoTotal.size();
	vector<DocInfo>::iterator iter;
	for (iter = DocInfoTotal.begin();iter != DocInfoTotal.end();iter++)
	{
		if ((iter + 1) == DocInfoTotal.end())
		{
			break;
		}
		vector<DocInfo>::iterator iternext = iter + 1;
		int length = (*iternext).s_offest - (*iter).s_offest;
		char *pContent = new char[length + 1];
		memset(pContent, 0, length + 1);
		InputData.seekg((*iter).s_offest);
		InputData.read(pContent, length);

		char *s;
		s = pContent;
		
		int readbytes = 0;
		int newlines = 0;
		int filter = 0;
		for (int i = 0;i < 2;i++)
		{
			readbytes = 0;
			newlines = 0;
			while (newlines != 2 && readbytes != HEADER_BUF_SIZE - 1)
			{
				if (*s == '\n')
				{
					newlines++;
				}
				else
				{
					newlines = 0;
				}
				s++;
				filter++;
				readbytes++;
			}

			if (readbytes == HEADER_BUF_SIZE - 1) break;
		}
		if (readbytes == HEADER_BUF_SIZE - 1) continue;

		RemoveTags(s);

		string strline = s;
		result = hzSeg.SegmentSentenceMM(dict, strline);
		int resLength = result.size();
		int termcount = 0;
		int idx = 0;
		while ((idx = result.find(SEPARATOR.c_str())) != string::npos)
		{
			string word = result.substr(0, idx);
			result = result.substr(idx + SEPARATOR.size());
			map<string, TermInfo>::iterator iterTerm;
			if ((iterTerm =TermInfoTotal.find(word)) != TermInfoTotal.end())
			{
				VecInt::iterator iter1 = iterTerm->second.s_DocId.begin();
				VecInt::iterator iter2 = iterTerm->second.s_DocId.end();
				if (find(iter1, iter2, iter->s_DocId) == iter2)
				{
					iterTerm->second.s_DocId.push_back(iter->s_DocId);
					iterTerm->second.s_freq.insert(MapIntInt::value_type(iter->s_DocId, 1));
					vector<int> temp;
					temp.push_back(termcount);
					iterTerm->second.s_postion.insert(MapIntVecInt::value_type(iter->s_DocId, temp));
				}
				else
				{
					iterTerm->second.s_freq.find(iter->s_DocId)->second++;
					iterTerm->second.s_postion.find(iter->s_DocId)->second.push_back(termcount);

				}
			}
			else
			{
				TermInfo term;
				term.s_DocId.push_back(  iter->s_DocId);
				term.s_freq.insert(MapIntInt::value_type(iter->s_DocId, 1));
				term.s_text = word;
				vector<int> temp;
				temp.push_back(termcount);
				term.s_postion.insert(MapIntVecInt::value_type(iter->s_DocId, temp));
				TermInfoTotal.insert(map<string, TermInfo>::value_type(word, term));
			}
			termcount++;
		}
		delete[] pContent;
		cout << result << endl;
		int count = 0;
	}

	int ll = 0;
}

void CDocumentDeal::RemoveTags(char *s)
{
	int intag;
	char *p, *q;

	if (!s || !*s)	return;

	for (p = q = s, intag = 0; *q; q++) {
		switch (*q) {
		case '<':
			intag = 1;
			*p++ = ' ';
			break;
		case '>':
			intag = 0;
			break;
		default:
			if (!intag) {
				*p++ = *q;
			}
			break;
		}
	}

	*p = '\0';
}

size_t CDocumentDeal::suffixLen(const string& str1, const string& str2) const
{
	size_t len = 0;
	size_t Size = str1.size() > str2.size() ? str2.size() : str1.size();
	for (size_t i = 0;i < Size;i++)
	{
		unsigned char ch = (unsigned char)str2[i];
		if (ch < 128 )
		{
			if (str1[i] == str2[i])
			{
				len++;
			}
			else
			{
				return len;
			}
		}
		else
		{
			if (str1[i] == str2[i] && str1[i + 1] == str2[i + 1] && (i + 1) < Size)
			{
				len += 2;
			}
			else
			{
				return len;
			}
			i++;
		}
	}
	return len;
}

bool CDocumentDeal::PostingList(const string &path, const string &path1, const string &path2) const
{
	ofstream worddict(path.c_str());
	ofstream freq(path1.c_str());
	ofstream prx(path2.c_str());
	map<string, TermInfo>::const_iterator iter = TermInfoTotal.begin();
	MapIntInt::const_iterator iter2, last2;
	MapIntVecInt::const_iterator iter3, last3;
	string prevWord = "";
	while (iter != TermInfoTotal.end())
	{
		size_t len =suffixLen(prevWord, iter->first);
		prevWord = iter->first;
		string s = iter->first.substr(len);
		worddict << s << " " << len<<" "<< freq.tellp()<<" "<<prx.tellp()<<" "<< iter->second.s_DocId.size()<<'\n';
		iter2 = iter->second.s_freq.begin();
		last2 = iter->second.s_freq.end();
		int prevDocId = 0;
		while (iter2 != last2)
		{
			int dalt = iter2->first - prevDocId;
			freq << dalt << " " << iter2->second << '\n';

			prevDocId = iter2->first;

			iter2++;
		}
		iter3 = iter->second.s_postion.begin();
		last3 = iter->second.s_postion.end();

		prevDocId = 0;

		while (iter3 != last3)
		{
			int dalt = iter3->first - prevDocId;
			prx << dalt << " ";
			int prev = 0;
			for (size_t i = 0;i < iter3->second.size();i++)
			{
				int postition = iter3->second[i] - prev;
				prx << postition << " ";
				prev = iter3->second[i];
			}
			prx << '\n';
			iter3++;
		}
		iter++;
	}

	worddict.close();
	freq.close();
	prx.close();
	return true;
}
bool CDocumentDeal::DocInfoMap(const string &path) const
{
	ofstream output(path.c_str());
	vector<DocInfo>::const_iterator iter = DocInfoTotal.begin();
	while (iter != DocInfoTotal.end())
	{
		output << iter->s_DocId << " " << iter->s_length << " " << iter->s_offest << "\n";
		iter++;
	}
	output.close();
	return true;
}
bool CDocumentDeal::UrlToDoc(const string &path) const
{
	ofstream output(path.c_str());
	vector<UrlInfo>::const_iterator iter = UrlInfoTotal.begin();
	while (iter != UrlInfoTotal.end())
	{
		output << iter->s_Url << " " << iter->s_DocId << "\n";
		iter++;
	}
	output.close();
	return true;
}
