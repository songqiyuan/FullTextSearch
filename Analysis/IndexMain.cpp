#include <iostream>
#include "HzSeg.h"
#include "DocumentDeal.h"
#include "IndexInput.h"
////const string SPLICRESULT("splicResult.txt");
//const string DATA("testdata.dat");
void readData(string& str)
{
	ifstream fpdata(DATA.c_str(),ifstream::in);
	string line;
	while(getline(fpdata,line))
	{
		str+=line;
	}
}
int main()
{
	CDict dict;
	string str = "";
	string strlin = "";
	CDocumentDeal dealDoc;
	dealDoc.DocIndex();
	dealDoc.DocTermIndex(dict);
	dealDoc.UrlToDoc(PATHINDEX);
	dealDoc.DocInfoMap(PATHDOC);
	dealDoc.PostingList(WORDDICT, FREQ, PRX);

	CIndexInput IndexInput;
	IndexInput.readWorddict();
	//std::u16string ch="";
	//CDict dict;
	//auto a=4;
	//string str="";
	//string strlin="";
	//readData(str);
	//CHzSeg hzSeg;
	//string result=hzSeg.SegmentSentenceMM(dict, str);
	//cout<<result<<endl;
	//FILE *fpresult;
	//if ((fpresult = fopen(SPLICRESULT.c_str(), "w")) == NULL) {
	//	cout << "Can not open the Dictionary file!";
	//	exit(1);
	//}
	//fprintf(fpresult, "%s", result.c_str());
	//fclose(fpresult);

	//MMSeg mmseg;
	//mmseg.load("words.dic");
	//std::ifstream ifs(SPLICRESULT.c_str());
	//if (!ifs.good()) {
	//	std::cerr << "Failed to open " << std::endl;
	//	return -1;
	//}
	//std::stringstream ss;
	//ss << ifs.rdbuf();
	//auto s = MMSeg::from_utf8(str);
	//for (auto& w : mmseg.segment(s))
	//{
	//	std::cout << MMSeg::to_utf8(w) << "  "; std::cout << std::endl;
	//}

	return 0;
}
