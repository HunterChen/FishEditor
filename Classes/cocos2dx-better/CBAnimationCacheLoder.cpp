#include "CBAnimationCacheLoder.h"
#include "cocos2d.h"
#include <map>
#include <algorithm>

using namespace cocos2d;

#define SEP_STRING "_"


CBAnimationCacheLoder* CBAnimationCacheLoder::m_pInstance = NULL;


CBAnimationCacheLoder::CBAnimationCacheLoder()
{

}

CBAnimationCacheLoder::~CBAnimationCacheLoder()
{

}

CBAnimationCacheLoder* CBAnimationCacheLoder::sharedCacheLoder( void )
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CBAnimationCacheLoder();
	}
	return m_pInstance;
}

void CBAnimationCacheLoder::LoadAnimationCacheWithFile( const char* plist, const char* keyName )
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist);

	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
	CCDictionary* dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
	if (!dict)
	{
		return;
	}

	std::vector<std::string> vecAnimation;
	CCDictionary* framesDict = (CCDictionary*)dict->objectForKey("frames");
	if (framesDict)
	{
		CCDictElement* pElement;
		CCDICT_FOREACH(framesDict, pElement)
		{
			std::string strFrameKey = pElement->getStrKey();
			vecAnimation.push_back(strFrameKey);
		}
	}
	qSortAnimationFrame(&(vecAnimation[0]), 0, vecAnimation.size()-1);

	//
	CCArray* animFrames = new CCArray();
	for (unsigned int i=0; i<vecAnimation.size(); i++)
	{
		std::string strFrameName = vecAnimation[i];
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName.c_str());
		animFrames->addObject(frame);
	}
	if (animFrames->count() > 0)
	{
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, keyName);
	}
	animFrames->removeAllObjects();
	delete animFrames;

	CC_SAFE_RELEASE(dict);
}

void CBAnimationCacheLoder::unLoadAnimationCacheWithFile( const char* plist, const char* keyName )
{
	CCAnimationCache::sharedAnimationCache()->removeAnimationByName(keyName);
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist);

	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
	CCDictionary* dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
	if (!dict)
	{
		return;
	}

	CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
	if (metadataDict)
	{
		CCString* strTextureFileName = (CCString*)(metadataDict->objectForKey("textureFileName"));
		if (strTextureFileName)
		{			
			std::string str_plist = plist;
			std::string str_plistExtension = ".plist";

			std::string str_textureFile = strTextureFileName->m_sString;
			std::string::size_type startPos = str_textureFile.find_last_of(".");
			std::string str_textureFileExtension = str_textureFile.substr(startPos, str_textureFile.length()-startPos);

			std::string strTmp = str_plist.substr(0, str_plist.length()-str_plistExtension.length());
			std::string strImageName = strTmp + str_textureFileExtension;
			CCTextureCache::sharedTextureCache()->removeTextureForKey(strImageName.c_str());
		}
	}

	CC_SAFE_RELEASE(dict);
}

void CBAnimationCacheLoder::LoadAnimationCacheWithFile( const char* plist )
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist);

	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
	CCDictionary* dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
	if (!dict)
	{
		return;
	}

	std::map< std::string, std::vector<std::string>* > map_animations;

	CCDictionary* framesDict = (CCDictionary*)dict->objectForKey("frames");
	if (framesDict)
	{
		CCDictElement* pElement;
		CCDICT_FOREACH(framesDict, pElement)
		{
			std::string strFrameKey = pElement->getStrKey();
			std::string::size_type posSep = strFrameKey.find_last_of(SEP_STRING);
			if (posSep != std::string::npos)
			{
				std::string strAnimationName = strFrameKey.substr(0, posSep);

				std::map< std::string, std::vector<std::string>* >::const_iterator itr = map_animations.find(strAnimationName);
				if (itr == map_animations.end())
				{
					std::vector<std::string>* pVecAnimation = new std::vector<std::string>;
					pVecAnimation->push_back(strFrameKey);
					map_animations.insert(std::map< std::string, std::vector<std::string>* >::value_type(strAnimationName, pVecAnimation));
				}
				else
				{
					std::vector<std::string>* pVecAnimation = itr->second;
					pVecAnimation->push_back(strFrameKey);
				}
			}
		}
	}

	//
	for (std::map< std::string, std::vector<std::string>* >::iterator itr = map_animations.begin(); itr != map_animations.end(); ++itr)
	{
		std::string strAnimationName = itr->first;
		std::vector<std::string>* pVecAnimation = itr->second;
		qSortAnimationFrame(&(pVecAnimation->at(0)), 0, pVecAnimation->size()-1);

		//
		CCArray* animFrames = new CCArray();
		for (unsigned int i=0; i<pVecAnimation->size(); i++)
		{
			std::string strFrameName = pVecAnimation->at(i);
			CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName.c_str());
			animFrames->addObject(frame);
		}
		if (animFrames->count() > 0)
		{
			CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames);
			CCAnimationCache::sharedAnimationCache()->addAnimation(animation, strAnimationName.c_str());
		}

		animFrames->removeAllObjects();
		delete animFrames;

		CC_SAFE_DELETE(pVecAnimation);
	}
	map_animations.clear();

	CC_SAFE_RELEASE(dict);
}

void CBAnimationCacheLoder::unLoadAnimationCacheWithFile( const char* plist )
{
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
	CCDictionary* dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
	if (!dict)
	{
		return;
	}

	std::vector<std::string> vecAnimationName;
	CCDictionary* framesDict = (CCDictionary*)dict->objectForKey("frames");
	if (framesDict)
	{
		CCDictElement* pElement;
		CCDICT_FOREACH(framesDict, pElement)
		{
			std::string strFrameKey = pElement->getStrKey();
			std::string::size_type posSep = strFrameKey.find_last_of(SEP_STRING);
			if (posSep != std::string::npos)
			{
				std::string strAnimationName = strFrameKey.substr(0, posSep);
				std::vector<std::string>::iterator itr = std::find( vecAnimationName.begin(), vecAnimationName.end(), strAnimationName);
				if( itr == vecAnimationName.end() )
				{
					vecAnimationName.push_back(strAnimationName);
				}
			}
		}
	}
	for (unsigned int i=0; i<vecAnimationName.size(); i++)
	{
		std::string strAnimationName = vecAnimationName[i];
		CCAnimationCache::sharedAnimationCache()->removeAnimationByName(strAnimationName.c_str());
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist);

	//
	CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
	if (metadataDict)
	{
		CCString* strTextureFileName = (CCString*)(metadataDict->objectForKey("textureFileName"));
		if (strTextureFileName)
		{
			std::string str_plist = plist;
			std::string str_plistExtension = ".plist";

			std::string str_textureFile = strTextureFileName->m_sString;
			std::string::size_type startPos = str_textureFile.find_last_of(".");
			std::string str_textureFileExtension = str_textureFile.substr(startPos, str_textureFile.length()-startPos);

			std::string strTmp = str_plist.substr(0, str_plist.length()-str_plistExtension.length());
			std::string strImageName = strTmp + str_textureFileExtension;
			CCTextureCache::sharedTextureCache()->removeTextureForKey(strImageName.c_str());
		}
	}

	CC_SAFE_RELEASE(dict);
}

void CBAnimationCacheLoder::qSortAnimationFrame( std::string *p, int l, int r )
{
	if (l < r)
	{
		int i = l;
		int j = r;

		std::string x = *(p + i);
		std::string::size_type posSep1 = x.find_last_of(SEP_STRING);
		std::string::size_type posSep2 = x.find_last_of(".");
		std::string strIndex = x.substr(posSep1+1, posSep2-(posSep1+1));
		int index_x = atoi(strIndex.c_str());

		while(i < j)
		{
			std::string str_j = *(p + j);
			std::string::size_type posSep_j_1 = str_j.find_last_of(SEP_STRING);
			std::string::size_type posSep_j_2 = str_j.find_last_of(".");
			std::string strIndex_j = str_j.substr(posSep_j_1+1, posSep_j_2-(posSep_j_1+1));
			int index_j = atoi(strIndex_j.c_str());

			while(i<j && index_j>index_x)
			{
				j--;

				str_j = *(p + j);
				posSep_j_1 = str_j.find_last_of(SEP_STRING);
				posSep_j_2 = str_j.find_last_of(".");
				strIndex_j = str_j.substr(posSep_j_1+1, posSep_j_2-(posSep_j_1+1));
				index_j = atoi(strIndex_j.c_str());
			}
			if(i < j)
			{
				*(p + i) = *(p + j);
				i++;
			}


			std::string str_i = *(p + i);
			std::string::size_type posSep_i_1 = str_i.find_last_of(SEP_STRING);
			std::string::size_type posSep_i_2 = str_i.find_last_of(".");
			std::string strIndex_i = str_i.substr(posSep_i_1+1, posSep_i_2-(posSep_i_1+1));
			int index_i = atoi(strIndex_i.c_str());

			while(i<j && index_i < index_x)
			{
				i++;

				str_i = *(p + i);
				posSep_i_1 = str_i.find_last_of(SEP_STRING);
				posSep_i_2 = str_i.find_last_of(".");
				strIndex_i = str_j.substr(posSep_i_1+1, posSep_i_2-(posSep_i_1+1));
				index_i = atoi(strIndex_i.c_str());
			}
			if(i < j)
			{
				*(p + j) = *(p + i);
				j--; 
			}
		}

		*(p + i) = x;
		qSortAnimationFrame(p, l, i-1);
		qSortAnimationFrame(p, i+1, r);
	}
}
