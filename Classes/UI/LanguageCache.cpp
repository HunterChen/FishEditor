#include "LanguageCache.h"
#include "../Common/StringModifier.hpp"

using namespace cocos2d;


LanguageCache* LanguageCache::pInstance = NULL;


LanguageCache::LanguageCache()
	: m_languageDict(NULL)
{
	m_languageDict = CCDictionary::createWithContentsOfFile("Resource/language.xml");
	m_languageDict->retain();
}

LanguageCache::~LanguageCache()
{
	m_languageDict->release();
	pInstance = NULL;
}
const char* LanguageCache::valueForKey( const char* key )
{
	return m_languageDict->valueForKey(key)->m_sString.c_str();
}

std::string LanguageCache::valueStringForKey( const char* key )
{
	std::string strTmp = m_languageDict->valueForKey(key)->m_sString;
	std::string strRet = StringModifier::stringAddLineBreakAtString(strTmp, "#0A");
	return strRet;
}
