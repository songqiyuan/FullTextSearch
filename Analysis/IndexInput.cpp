#include"IndexInput.h"

const int DATACNT = 5;

CIndexInput::CIndexInput() :
	sffuixlen(0),
	DocFreq(0),
	freqPostion(0), 
	prxPostion(0), 
	worddict(WORDDICT.c_str()),
	freq(FREQ.c_str()),
	prx(PRX.c_str())
{

}
CIndexInput::~CIndexInput()
{
	sffuixlen = 0;
	DocFreq = 0;
	freqPostion=0;
	prxPostion = 0;
	TermInfoTotal.clear();
	worddict.close();
	freq.close();
	prx.close();
}


void CIndexInput::readWorddict()
{
	string prevword ("");
	string line;
	while (getline(worddict,line))
	{
		string currentword;
		TermInfo terminfo;
		istringstream linedata(line);
		linedata >> currentword;
		linedata >> sffuixlen;
		linedata >> freqPostion;
		linedata >> prxPostion;
		linedata >> DocFreq;
	
		currentword = prevword.substr(0, sffuixlen) + currentword;
		prevword = currentword;
		terminfo.s_text = currentword;
		readFreq(terminfo.s_freq,terminfo.s_DocId);
		readPrx(terminfo.s_postion);
		TermInfoTotal.insert(TermInfoArray::value_type(currentword, terminfo));

	}
}
void CIndexInput::readFreq( MapIntInt& freqset, VecInt& docid)
{
	int linecount = 0;
	int prevdocid = 0;
	int wordfreq = 0;
	string line;
	while (linecount < DocFreq && getline(freq,line))
	{
		linecount++;
		int currentdocid;
		istringstream linedata(line);
		linedata >> currentdocid;
		currentdocid += prevdocid;
		prevdocid = currentdocid;
		linedata >> wordfreq;
		freqset.insert(MapIntInt::value_type(currentdocid, wordfreq));
		docid.push_back(currentdocid);
	}
}
void CIndexInput::readPrx( MapIntVecInt& postion)
{
	int linecount = 0;
	int prevdocid = 0;
	string line;
	while (linecount < DocFreq && getline(prx, line))
	{
		int currentdocid;
		linecount++;
		istringstream linedata(line);
		vector<int> vecPostion;
		int temppostion;
		int prevpostion = 0;
		linedata >> currentdocid;
		currentdocid += prevdocid;
		prevdocid = currentdocid;
		while (linedata >> temppostion)
		{
			temppostion += prevpostion;
			prevpostion = temppostion;
			vecPostion.push_back(temppostion);
		}
		postion.insert(MapIntVecInt::value_type(currentdocid, vecPostion));
	}
}
