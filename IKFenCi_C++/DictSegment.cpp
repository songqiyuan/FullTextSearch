#include"DictSegment.h"
#include<iterator>
CDictSegment::CDictSegment()
{

}
CDictSegment::~CDictSegment()
{

}
void CDictSegment::fillSegment(string str, WordNode& node)
{
	//判断是否为ascii码值的字符 <128 数字，英文字母以及标点符号
	Iter iterBegin = node.begin();
	Iter iterEnd = node.end();
	unsigned char ch = str[0];
	bool strEnd = false;
	string tmp;
	if (isChar(ch))
	{
		tmp = str.substr(0, 1);
		str = str.substr(1);
		if (str.empty()) strEnd = true;
	}
	else
	{
		tmp = str.substr(0, 2);
		str = str.substr(2);
		if (str.empty()) strEnd = true;
	}
	CIter iterFind = node.find(tmp);
	if(iterFind ==iterEnd)
	{
		signleNode currNode;
		currNode.endFlag = strEnd ? true : false;
		node.insert(std::pair<string, signleNode>(tmp,currNode));
		if (strEnd) return;
		else
		{
			fillSegment(str, node[tmp].childnode);
		}
	}
	else
	{
		fillSegment(str, node[tmp].childnode);
	}
}
void CDictSegment::match(string &str, CHit& Hit)
{
	if (Hit.getCurrNode().childnode.size() > 0)
	{
		match(str, Hit, Hit.getCurrNode().childnode);
	}
	else
	{
		match(str, Hit, _wordnode);
	}
}
void CDictSegment::match(string &str,CHit& Hit,const WordNode& node)
{
	if (str.empty()) return;

	unsigned char ch = str[0];
	CIter iterEnd = node.end();
	bool strEnd = false;
	bool firstMatch = false;
	//firstMatch = (Hit == nullptr ? true : false);
	string tmp;
	if (isChar(ch))
	{
		tmp = str.substr(0, 1);
		str = str.substr(1);
		if (str.empty()) strEnd = true;
	}
	else
	{
		tmp = str.substr(0, 2);
		str = str.substr(2);
		if (str.empty()) strEnd = true;
	}
	CIter iterFind = node.find(tmp);
	if (iterFind == iterEnd)
	{
		Hit.setNotMatch();
		return;
	}
	else
	{
		Hit.setText(tmp);
		//如果是一个词
		if (iterFind->second.endFlag == true)
		{
			Hit.setMatch();
			
			if (iterFind->second.childnode.size() > 0)
			{
				Hit.setPrefix();
				Hit.setCurrNode(iterFind->second);
			}
			else
			{
				Hit.cancelPrefix();
			}
			return;
		}
		else if(!strEnd)
		{
			
			match(str, Hit, iterFind->second.childnode);
		}

		if(strEnd)
		{
			Hit.setNotMatch();
		}
		return;

	}
}
void CDictSegment::fillSegment(string str)
{
	fillSegment(str, _wordnode);
}
bool CDictSegment::isChar(unsigned char ch)
{
	return ch < 128;
}
void CDictSegment::display()
{

}
