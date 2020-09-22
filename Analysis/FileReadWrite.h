#ifndef _FILEREADWRITE_H_
#define _FILEREADWRITE_H_
#include<fstream>
#include<string>

class CIfstream
{
	CIfstream() {};
	CIfstream(const std::string path, const unsigned int Mode=std::ifstream::in)
	{
		_Input.open(path.c_str(), Mode);
	}
	CIfstream()
	{
		_Input.close();
	}
private:
	std::ifstream _Input;
};
class COfstream
{
	COfstream() {};
	COfstream(const std::string path, const unsigned int Mode=std::ofstream::app)
	{
		_Output.open(path.c_str(), Mode);
	}
	~COfstream()
	{
		_Output.close();
	}
private:
	std::ifstream _Output;
};
#endif
