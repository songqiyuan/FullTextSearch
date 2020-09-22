#include "Dict.h"
CDict::CDict()
{
	OpenDict();
	cout << "CDict" << endl;
}
CDict::~CDict()
{
	mapDict.clear();
}

bool CDict::IsWord(string& str) const
{
	if (mapDict.find(str) == mapDict.end())
	{
		return false;
	}
	return true;
}

void CDict::OpenDict()
{
	ifstream fpdict(DICTFILENAME.c_str(), ifstream::in);
	int wordcount = 0;
	string line;
	string word;
	string number;

	while (getline(fpdict, line))
	{
		istringstream wordsline(line);
		wordsline >> number;
		wordsline >> word;
		mapDict.insert(map<string, int>::value_type(word, wordcount));
		wordcount++;
	}
	fpdict.close();

	mmseg.load(DICTFILENAME1);

}
void CDict::display()
{
	map<string, int>::iterator iter = mapDict.begin();
	while (iter != mapDict.end())
	{
		cout << iter->first << endl;
		iter++;
	}
}
