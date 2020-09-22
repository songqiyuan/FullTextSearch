#include"Lexeme.h"
#include<algorithm>
bool CQuickSortSet::addLexeme(CLexeme lexeme)
{
	//从小到大插入元素
	if (lexemeset.size() == 0)
	{
		lexemeset.push_back(lexeme);
	}
	else
	{
		if (lexeme.compareTo((*lexemeset.rbegin())) == 0)
		{
			return false;
		}
		else if (lexeme.compareTo((*lexemeset.rbegin())) > 0)
		{
			lexemeset.push_back(lexeme);
			return true;
		}
		else if (lexeme.compareTo((*lexemeset.begin())) < 0)
		{
			lexemeset.push_front(lexeme);
			return true;
		}
		else
		{
			std::list<CLexeme>::iterator iter = lexemeset.begin();
			while (iter != lexemeset.end())
			{
				if ((*iter).compareTo(lexeme) == 0) return false;
				if ((*iter).compareTo(lexeme) > 0)
				{
					lexemeset.insert(iter, lexeme);
					return true;
				}
				iter++;
			}
		}

	}
	return false;
}

CLexeme CQuickSortSet::peekLast()
{
	std::list<CLexeme>::reverse_iterator tail = lexemeset.rbegin();
	return (*tail);
}

std::list<CLexeme>& CQuickSortSet::getLexemePath()
{
	return lexemeset;
}


CLexeme::CLexeme()
{}
CLexeme::CLexeme(int begin, int length, int lexemeType):
	_begin(begin),_length(length),_lexemeType(lexemeType)
{

}
int CLexeme::getBegin()
{
	return _begin;
}
int CLexeme::getLength()
{
	return _length;
}
std::string CLexeme::getText()
{
	return _text;
}
int CLexeme::compareTo(CLexeme other)
{
	if (_begin < other.getBegin())
	{
		return -1;
	}
	else if(_begin==other.getBegin())
	{
		if (_length > other.getLength())
		{
			return -1;
		}
		if (_length == other.getLength())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

bool CLexeme::equals(CLexeme o)
{
	return (_begin == o.getBegin() && _length == o.getLength() && _text == o.getText());
}



CLexemePath::CLexemePath():
	_pathBegin(0), _pathEnd(0), _payloadLength(0)
{}
CLexemePath::CLexemePath(int pathBegin, int pathEnd, int payloadLength):
	_pathBegin(pathBegin),_pathEnd(pathEnd),_payloadLength(payloadLength)
{
}


bool CLexemePath::checkCross(CLexeme lexeme)
{
	return ((_pathBegin <= lexeme.getBegin() && _pathEnd > lexeme.getBegin()) 
		|| (_pathBegin>=lexeme.getBegin() && _pathEnd<lexeme.getBegin()+lexeme.getLength()));
}

bool CLexemePath::addCrossLexeme(CLexeme lexeme)
{
	if (lexemeset.empty())
	{
		addLexeme(lexeme);
		_pathBegin = lexeme.getBegin();
		_pathEnd = lexeme.getBegin() + lexeme.getLength()-1;
		_payloadLength += lexeme.getLength();
		return true;
	}
	else if(!checkCross(lexeme))
	{
		return false;
	}
	else
	{
		addLexeme(lexeme);
		if (_pathEnd < lexeme.getBegin() + lexeme.getLength())
		{
			_pathEnd = lexeme.getBegin() + lexeme.getLength()-1;
		}
		_payloadLength = _pathEnd - _pathBegin;
		return true;
	}
	return false;
}
bool CLexemePath::addNotCrossLexeme(CLexeme lexeme)
{
	if (lexemeset.empty())
	{
		addLexeme(lexeme);
		_pathBegin = lexeme.getBegin();
		_pathEnd = lexeme.getBegin() + lexeme.getLength()-1;
		_payloadLength += lexeme.getLength();
		return true;
	}
	else if (!checkCross(lexeme))
	{
		addLexeme(lexeme);
		_payloadLength += lexeme.getLength();
		CLexeme head = lexemeset.front();
		_pathBegin = head.getBegin();
		std::list<CLexeme>::reverse_iterator tail = lexemeset.rbegin();
		_pathEnd=(*tail).getBegin() + (*tail).getLength()-1;
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

CLexemePath CLexemePath::copyPath()
{
	CLexemePath thecopy;
	thecopy._pathBegin = _pathBegin;
	thecopy._pathEnd = _pathEnd;
	thecopy._payloadLength = _payloadLength;
	//thecopy.lexemeset = lexemeset;
	std::copy(thecopy.lexemeset.begin(), thecopy.lexemeset.end(), lexemeset.begin());
	return thecopy;
}
int CLexemePath::getPWeight()
{
	int pWeight = 0;
	int p = 0;
	lexemeIter iter = lexemeset.begin();
	while (iter != lexemeset.end())
	{
		p++;
		pWeight += p * (*iter).getLength();
		iter++;
	}
	return pWeight;
}

int CLexemePath::getXWeight()
{
	int product = 1;
	lexemeIter iter = lexemeset.begin();
	while (iter != lexemeset.end())
	{
		product *= (*iter).getLength();
		iter++;
	}
	return product;
}

int CLexemePath::compareTo(CLexemePath o)
{
	//此比较函数把最优解放在最前位置来进行比较的，最优解要小于其他解
	//1.比较有效文本长度，越长越好
	if (_payloadLength > o._payloadLength)
	{
		return -1; 
	}
	else if (_payloadLength < o._payloadLength)
	{
		return 1;
	}
	else
	{
		//2.比较词元个数,越少越好
		if (lexemeset.size() < o.lexemeset.size())
		{
			return -1;
		}
		else if (lexemeset.size() > o.lexemeset.size())
		{
			return 1;
		}
		else
		{
			//3.比较路径跨度，越大越好
			if (getPathLength() > o.getPathLength())
			{
				return -1;
			}
			else if (getPathLength() < o.getPathLength())
			{
				return 1;
			}
			else
			{
				//4.根据统计学结论，逆向切分概率高于正向切分，因此位置越靠后的优先
				if (_pathEnd > o._pathEnd)
				{
					return -1;
				}
				else if (_pathEnd < o._pathEnd)
				{
					return 1;
				}
				else
				{
					//5.词平均长度
					if (getXWeight() > o.getXWeight())
					{
						return -1;
					}
					else if (getXWeight() < o.getXWeight())
					{
						return 1;
					}
					else
					{
						//位置权重比较
						if (getPWeight() > o.getPWeight())
						{
							return -1;
						}
						else if (getPWeight() < o.getPWeight())
						{
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

void CLexemePath::DeleteWordTail()
{
	//减少有效长度
	int len = (*getLexemePath().rbegin()).getText().size();
	_payloadLength -= len;
	getLexemePath().pop_back();
}
