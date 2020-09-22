#include <fstream>
#include <sstream>
#include "Configuration.h"
std::string CConfiguration::PATH_DIC_MAIN= "main2012.dic";
std::string CConfiguration::PATH_DIC_QUANTIFIER= "quantifier.dic";

CConfiguration::CConfiguration() :useSmart(false)
{
	_init();
}
CConfiguration::~CConfiguration()
{}
void CConfiguration::setUseSmart(bool usesmart)
{
	useSmart = usesmart;
}
bool CConfiguration::getuseSmart()
{
	return useSmart;
}
std::string CConfiguration::getMainDictionary()
{
	return 	CConfiguration::PATH_DIC_MAIN;
}
std::string CConfiguration::getQuantifierDicionary()
{
	return CConfiguration::PATH_DIC_QUANTIFIER;
}

std::vector<std::string> CConfiguration::getExtDictionarys()
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> CConfiguration::getExtStopWordDictionarys()
{
	std::vector<std::string> result;
	return result;
}
void CConfiguration::loadMainDict()
{
	std::ifstream fpMainDict(DICTFILENAME.c_str(), std::ifstream::in);
	std::string line;
	std::string number;
	std::string word;
	while (std::getline(fpMainDict, line))
	{
		std::istringstream wordsline(line);
		wordsline >> number;
		wordsline >> word;
		_MainDict.fillSegment(word);
	}
	fpMainDict.close();
	
}

void CConfiguration::loadQuantDict()
{
	std::ifstream fpQuantDict(DICTFILENAME1.c_str(), std::ifstream::in);
	std::string line;

	std::string word;
	while (std::getline(fpQuantDict, line))
	{
		std::istringstream wordsline(line);
	
		wordsline >> word;
		_QuantDict.fillSegment(word);
	}
	fpQuantDict.close();

}
void CConfiguration::loadStopDict()
{
	std::ifstream fpStopDict(STOPDICT.c_str(), std::ifstream::in);
	std::ifstream fpCStopDict(CSTOPDICT.c_str(), std::ifstream::in);
	std::string line;
	std::string word;
	while (std::getline(fpStopDict, line))
	{
		std::istringstream wordsline(line);
		wordsline >> word;
		_StopWordDict.fillSegment(word);
	}
	line = "";
	word = "";
	while (std::getline(fpCStopDict, line))
	{
		std::istringstream wordsline(line);
		wordsline >> word;
		_StopWordDict.fillSegment(word);
	}
	fpStopDict.close();
	fpCStopDict.close();

}
void CConfiguration::_init()
{
	loadMainDict();
	loadQuantDict();
	loadStopDict();
}
