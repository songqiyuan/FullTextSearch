#include <iostream>
//#include "DictSegment.h"
#include "Configuration.h"
#include"CJKSegmenter.h"
int main()
{
	//CConfiguration cfg;

	//CDictSegment dict=cfg.getMainDict();
	//CHit hit;
	//string s1 = "abc";
	//string s2 = "abd";
	//string s3 = "中华";
	//string s4 = "中国";
	string s5 = "中华人民共和国";
	string s6 = "学历史知识";
	string s7 = "张三说的确实在理";
	string s8 = "IK Analyzer是一个结合词典分词和文法分词的中文分词开源工具包。它使用了全新的正向迭代最细粒度切分算法";
	//dict.fillSegment(s1);
	//dict.fillSegment(s2);
	//dict.fillSegment(s3);
	//dict.fillSegment(s4);
	//dict.fillSegment(s5);
	//dict.match(s5, hit);
	CCJKSegmenter An;
	An.setSmart(true);
	An.distext(s8);
	An.distext(s7);
	An.distext(s5);
	An.distext(s6);
    std::cout << "Hello World!\n"; 
	return 0;
}
