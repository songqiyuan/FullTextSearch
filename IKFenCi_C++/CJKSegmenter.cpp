#include"CJKSegmenter.h"

string CCJKSegmenter::SEGMENTER_NAME = "CJK_SEGMENTER";
CCJKSegmenter::CCJKSegmenter() :
	_currPos(0), length(0)
{
	_cfg.setUseSmart(false);
}
CCJKSegmenter::~CCJKSegmenter()
{

}
bool CCJKSegmenter::Analyzer(string& str)
{
	if (str.size() < 2) return false;
	//优先处理前缀队列中的词
	if (!Hit.empty())
	{
		std::vector<CHit>::iterator Iter = Hit.begin();
		std::vector<CHit>::iterator Iterend = Hit.begin();
		while (Iter!=Hit.end())
		{
			string strtmp = str;
			_cfg.getMainDict().match(strtmp, (*Iter));
			if ((*Iter).isMatch())
			{
				//(*Iter).displayText();

				//构造CLexeme并加入CQuickSortSet集合中
				CLexeme lexeme((*Iter).getBegin(), (*Iter).getText().size(), CLexeme::TYPE_CNWORD);
				lexeme.setText((*Iter).getText());
				_sortSet.addLexeme(lexeme);

				if (!(*Iter).isPrefix())
				{
					//不再是前缀则从列表中移除
					Iter=Hit.erase(Iter);
				}
				else
				{
					Iter++;
				}
			}
			else if ((*Iter).isNotMatch())
			{
				Iter=Hit.erase(Iter);
			}
		}
	}
	//前缀列表为空，从开始位置匹配
	CHit hit;
	_cfg.getMainDict().match(str, hit);
	
	//前缀则加入集合
	if (hit.isMatch())
	{
		//hit.displayText();
		hit.setBegin(_currPos);
		CLexeme lexeme(hit.getBegin(), hit.getText().size(), CLexeme::TYPE_CNWORD);
		lexeme.setText(hit.getText());
		_sortSet.addLexeme(lexeme);
	}
	if (hit.isPrefix())
	{
		hit.setBegin(_currPos);
		Hit.push_back(hit);
	}
	_currPos = length - str.size();
	return true;
}
void CCJKSegmenter::reset()
{
	_sortSet.getLexemePath().clear(); //第一次分词结果，未进行歧义处理
	_pathSet.clear();
	result.clear();
	//清空前缀队列
	_currPos = 0;
	Hit.clear();
}
void CCJKSegmenter::distext(string str)
{
	length = str.size();
	while (Analyzer(str) && str.size() > 0);
	if (getSmart())
	{
		process();
		addResult();
	}
	reset();
}

void CCJKSegmenter::process()
{
	CLexemePath lexemePath;
	lexemeIter iter = _sortSet.getLexemePath().begin();
	while (iter != _sortSet.getLexemePath().end())
	{
		if (!lexemePath.addCrossLexeme((*iter)))
		{
			if (lexemePath.getLexemePath().size() == 1 || _cfg.getuseSmart() == false)
			{
				_pathSet.push_back(lexemePath);
			}
			else
			{
				//歧义处理
				CLexemePath Path = judge(lexemePath);
				_pathSet.push_back(Path);
			}
			lexemePath = CLexemePath(0, 0, 0);
			lexemePath.addCrossLexeme((*iter));
		}
		iter++;
	}

	if (lexemePath.getLexemePath().size() == 1 || _cfg.getuseSmart() == false)
	{
		_pathSet.push_back(lexemePath);
	}
	else
	{
		//歧义处理
		CLexemePath Path = judge(lexemePath);
		_pathSet.push_back(Path);
	}
}

CLexemePath CCJKSegmenter::judge(CLexemePath& lexemePath)
{
	//候选路径集合
	PathSortSet pathOptions;
	//候选路径
	CLexemePath option;
	lexemeIter Start = lexemePath.getLexemePath().begin();
	lexemeIter End = lexemePath.getLexemePath().end();
	sIter lexemeStack = forwardPath(Start, End, option);
	pathOptions.push(option);//.copyPath());
	while (!lexemeStack.empty())
	{
		lexemeIter c = lexemeStack.top();
		lexemeStack.pop();
		backPath((*c), option);
		forwardPath(c, End, option);
		pathOptions.push(option);//.copyPath());
	}
	return pathOptions.top();
}
sIter CCJKSegmenter::forwardPath(lexemeIter leIterStart, lexemeIter leIterEnd, CLexemePath& options)
{
	sIter conflictStack;
	while (leIterStart != leIterEnd)
	{
		if (!options.addNotCrossLexeme((*leIterStart)))
		{
			conflictStack.push(leIterStart);
		}
		leIterStart++;
	}
	return conflictStack;
}

void CCJKSegmenter::backPath(CLexeme l, CLexemePath& option)
{

	while (!option.getLexemePath().empty() &&  option.checkCross(l))
	{
		option.DeleteWordTail();
	}
}
bool CCJKSegmenter::addResult()
{
	if (_pathSet.empty()) return false;
	std::vector<CLexemePath>::iterator Iter1 = _pathSet.begin();
	std::list<CLexeme>::iterator Iter2,Iter3;

	while (Iter1!=_pathSet.end())
	{
		CLexemePath  cl = (*Iter1);
		Iter2 = cl.getLexemePath().begin();
		Iter3 = cl.getLexemePath().end();
		while (Iter2 != Iter3)
		{
			result.push_back((*Iter2));
			std::cout << (*Iter2).getText() << std::endl;
			Iter2++;
		}
		Iter1++;
	}
	return true;
}
