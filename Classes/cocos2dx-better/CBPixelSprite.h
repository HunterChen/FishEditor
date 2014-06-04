#pragma once

#include "cocos2d.h"


class CBPixelSprite : public cocos2d::CCSprite
{
public:
	static CBPixelSprite* create();
	static CBPixelSprite* create(const char *pszFileName);
	static CBPixelSprite* create(const char *pszFileName, const cocos2d::CCRect& rect);
	static CBPixelSprite* createWithTexture(cocos2d::CCTexture2D *pTexture);
	static CBPixelSprite* createWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect& rect);
	static CBPixelSprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
	static CBPixelSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

public:
	bool isContainPoint(cocos2d::CCPoint worldPoint);
	bool isTransparentInPoint(cocos2d::CCPoint worldPoint);
};