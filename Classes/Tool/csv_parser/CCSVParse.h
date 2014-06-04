#pragma once

#include <iostream>
#include <string>
#include <vector>

class CCSVParse
{
public:

	CCSVParse(std::istream& fin=std::cin, std::string sep=","):fieldsep(sep),cols(0){}
	virtual ~CCSVParse(void){}

private:
	//用以存储数据
	std::vector< std::vector<std::string> > data;
	std::string        fieldsep;
	int            cols;

	void StringSplit(const std::string& str, std::vector<std::string>& tokens, const char& delimiters);
	void split(std::vector<std::string>& field, std::string line);
	int advplain(const std::string& line, std::string& fld, int);
	int advquoted(const std::string& line, std::string& fld, int);

public:
	bool Parse( std::string strData);
	//根据行列获取数据
	const char* getData(unsigned int rows, unsigned int cols);
	//查找某列是否某数据，返回行号 
	int findColsData(int cols, const char* value);
	//得到最大的列数
	inline int getCols(){return cols;}
	//得到总共的行数
	inline int getRows(){return data.size();};

protected:
	//删除特定字符
	void deleteChar(std::string* str);
};
