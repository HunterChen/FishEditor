#include "CCSVParse.h"


bool CCSVParse::Parse( std::string strData )
{
	if (strData.empty())
	{
		return false;
	}

	std::vector<std::string> line;
	StringSplit(strData, line, '\n');
	for(unsigned int i=1; i<line.size(); i++) //i从1开始：第一行为title，不保存
	{
		deleteChar(&line[i]);//由于各系统的换行符不同(\r\n，\n，\r)删除多余的\r,\n
		std::vector<std::string> field;
		split(field, line[i]);
		data.push_back(field);
		cols = (cols > (int)field.size()) ? cols : (int)field.size();
	}
	return true;
}

void CCSVParse::StringSplit( const std::string& str, std::vector<std::string>& tokens, const char& delimiters )
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos-lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void CCSVParse::split( std::vector<std::string>& field, std::string line )
{
	std::string fld;
	unsigned int i,j=0;

	if( line.length() ==0 )
		return;
	i=0;

	do 
	{
		if(j<line.length() && line[i]=='"')
			j = advquoted(line, fld, ++i);
		else
			j = advplain(line, fld, i);

		field.push_back(fld);
		i = j+1;
	} while (j<line.length());
}

int CCSVParse::advplain( const std::string& s, std::string& fld, int i)
{
	unsigned int j;
	j = s.find_first_of(fieldsep, i);
	if(j>s.length())
		j=s.length();
	fld = std::string(s,i,j-i);
	return j;
}

int CCSVParse::advquoted( const std::string& s, std::string& fld, int i)
{
	unsigned int j;
	fld = "";
	for (j=i; j<s.length(); ++j)
	{
		if(s[j]=='"' && s[++j]!='"')
		{
			unsigned int k = s.find_first_of(fieldsep, j);
			if(k>s.length())
				k = s.length();
			for(k-=j; k-->0;)
				fld += s[j++];
			break;
		}
		fld += s[j];
	}
	return j;
}

void CCSVParse::deleteChar(std::string* str)
{
	std::string::iterator it;
	unsigned int index = 0;
	for (; index < str->size(); )
	{
		it = str->begin()+index;
		if ( *it == '\r' || *it == '\n' )
		{
			str->erase(it);
		} 
		else
		{
			index++;
		}
	}
}

const char* CCSVParse::getData(unsigned int rows, unsigned int cols )
{
	if (rows<0 || rows>=data.size() || cols<0 || cols>=data[rows].size())
	{
		return "";
	}
	return data[rows][cols].c_str();
}

int CCSVParse::findColsData( int cols, const char* value )
{
	for (unsigned int i=0; i<data.size(); ++i)
	{
		if(strcmp(getData(i,cols),value)==0)
			return i;
	}
	return -1;
}
