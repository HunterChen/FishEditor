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
	//���Դ洢����
	std::vector< std::vector<std::string> > data;
	std::string        fieldsep;
	int            cols;

	void StringSplit(const std::string& str, std::vector<std::string>& tokens, const char& delimiters);
	void split(std::vector<std::string>& field, std::string line);
	int advplain(const std::string& line, std::string& fld, int);
	int advquoted(const std::string& line, std::string& fld, int);

public:
	bool Parse( std::string strData);
	//�������л�ȡ����
	const char* getData(unsigned int rows, unsigned int cols);
	//����ĳ���Ƿ�ĳ���ݣ������к� 
	int findColsData(int cols, const char* value);
	//�õ���������
	inline int getCols(){return cols;}
	//�õ��ܹ�������
	inline int getRows(){return data.size();};

protected:
	//ɾ���ض��ַ�
	void deleteChar(std::string* str);
};
