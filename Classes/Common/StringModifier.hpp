#pragma once

#include <string.h>
#include <locale.h>
#include <algorithm>
#include <iostream>

#define COMPARE_STRING_EQUAL(STR1, STR2) StringModifier::strcmpCaseInsensitive(STR1, STR2) == 0

class StringModifier
{
public:

	static std::string toLowerCase(const std::string &aString)
	{
		std::string result = aString;
		for (std::string::iterator itr = result.begin(); itr != result.end(); ++itr)
		{
			*itr = tolower(*itr);
		}
		return result;
	}

	static int strcmpCaseInsensitive(const std::string &aLeft, const std::string &aRight)
	{
		return strcmp(toLowerCase(aLeft).c_str(), toLowerCase(aRight).c_str());
	}

	static bool stringToBool(const std::string &aInfo)
	{
		if (COMPARE_STRING_EQUAL(aInfo, "true"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static std::string stringAddLineBreakAtString(const std::string &aString, const char* markString)
	{
		std::string result = aString;
		std::string::size_type pos = result.find(markString);
		int lengthMark = strlen(markString);
		while(pos != std::string::npos)
		{
			result.erase(pos, lengthMark);
			result.insert(pos, "\n");
			pos = result.find(markString);
		}
		return result;
	}
};