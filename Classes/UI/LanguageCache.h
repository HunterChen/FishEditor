#pragma once

#include "cocos2d.h"
#include "../Common/Macro.h"
#include <string>

class LanguageCache
{
public:

	SINGLETON_CLEAR(LanguageCache, sharedCache, clearCache);

	const char* valueForKey(const char* key);

	std::string valueStringForKey(const char* key);

private:
	LanguageCache();
	virtual ~LanguageCache();

private:
	 cocos2d::CCDictionary* m_languageDict;
};
