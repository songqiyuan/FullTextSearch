#include"HzSeg.h"

const string STOP_END("stop_end");

const string ENGLISH_STOP_WORDS[] =
{
	"a", "an", "and", "are", "as", "at", "be", "but", "by",
	"for", "if", "in", "into", "is", "it",
	"no", "not", "of", "on", "or", "s", "such",
	"t", "that", "the", "their", "then", "there", "these",
	"they", "this", "to", "was", "will", "with", "stop_end"
};

const unsigned int MAX_WORD_LENGTH = 8;
CHzSeg::CHzSeg()
{
	int Index = 0;
	while (ENGLISH_STOP_WORDS[Index] != STOP_END)
	{
		stopword.insert(ENGLISH_STOP_WORDS[Index]);
		Index++;
	}
}

CHzSeg::~CHzSeg()
{

}

string CHzSeg::SegmentHzStrMM(CDict& dict, string s1) const
{
	string s2 = "";
	while (!s1.empty())
	{
		size_t len = s1.size();
		if (len > MAX_WORD_LENGTH)
		{
			len = MAX_WORD_LENGTH;
		}
		string w = s1.substr(0, len);
		bool isw = dict.IsWord(w);
		while (len>2 && isw==false)
		{
			len -= 2;
			w = w.substr(0, len);
			isw = dict.IsWord(w);
		}
		s2 += w + SEPARATOR;
		s1 = s1.substr(w.size());
	}
	return s2;
}
string CHzSeg::SegmentSentenceMM(CDict &dict, string s1) const
{
	string s2 = "";
	unsigned int i, len;
	while (!s1.empty()) {
		unsigned char ch = (unsigned char)s1[0];
		if (ch < 128) {
			string words = "";
			words += ch;
			i = 1;
			len = s1.size();
			while (i < len && ((unsigned char)s1[i] < 128)
				&& (s1[i] != 10) && (s1[i] != 13)) {
				words += s1[i];
				i++;
			}
			s2 += SegmengHzEnglish(words);
			if (i <= s1.size())
				s1 = s1.substr(i);
			else
				break;
			continue;
		}
		else {
			if (ch < 176) {
				i = 0;
				len = s1.length();
				while (i < len && ((unsigned char)s1[i] < 176) && ((unsigned char)s1[i] >= 161)
					&& (!((unsigned char)s1[i] == 161 && ((unsigned char)s1[i + 1] >= 162 && (unsigned char)s1[i + 1] <= 168)))
					&& (!((unsigned char)s1[i] == 161 && ((unsigned char)s1[i + 1] >= 171 && (unsigned char)s1[i + 1] <= 191)))
					&& (!((unsigned char)s1[i] == 163 && ((unsigned char)s1[i + 1] == 172 || (unsigned char)s1[i + 1] == 161)
						|| (unsigned char)s1[i + 1] == 168 || (unsigned char)s1[i + 1] == 169
						|| (unsigned char)s1[i + 1] == 186 || (unsigned char)s1[i + 1] == 187
						|| (unsigned char)s1[i + 1] == 191)))
				{
					i = i + 2;
				}

				if (i == 0) i = i + 2;

				if (!(ch == 161 && (unsigned char)s1[1] == 161)) {
					if (i <= s1.size())
						s2 += s1.substr(0, i) + SEPARATOR;
					else break;
				}
				if (i <= s1.size())
					s1 = s1.substr(i);
				else break;

				continue;
			}
		}
		i = 2;
		len = s1.length();
		while (i < len && (unsigned char)s1[i] >= 176)
			i += 2;

		s2 += SegmentHzStrMM(dict, s1.substr(0, i));

		if (i <= len)
			s1 = s1.substr(i);
		else break;	
	}

	return s2;
}

string CHzSeg::SegmengHzEnglish(string s1) const
{
	string s2 = "";
	size_t len;
	while (!s1.empty())
	{
		len = s1.size();
		unsigned char ch = s1[0];
		size_t totalcount = 1;
		
		string word = "";
		while (totalcount < len)
		{
			if (((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)))
			{
		
				word += ch;
				ch = s1[totalcount];
			}
			else
			{
				break;
			}
			totalcount++;
		}
		if (!word.empty())
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			if (stopword.find(word) == stopword.end())
			{
				s2 += word + SEPARATOR;
			}
		}

		s1 = s1.substr(totalcount);
	}
	return s2;
}
