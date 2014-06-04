#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

class CBTransparentButton : public cocos2d::extension::CCControlButton
{
public:
	CBTransparentButton();
	virtual ~CBTransparentButton();

	static CBTransparentButton* createWithFile(const char* fileName);
	static CBTransparentButton* createWithSpriteFrameName(const char* frameName);

	virtual bool isTouchInside(cocos2d::CCTouch* touch);

protected:
	bool isTouchInOpaqueRect(cocos2d::CCTouch* pTouch);

protected:
	cocos2d::CCImage* m_image;
	cocos2d::CCSize m_imageSize;
};