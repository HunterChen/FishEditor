#pragma once

#include "cocos2d.h"
#include <string>

class FunctionLayer;


class WarningLayerSaveFile : public cocos2d::CCLayerColor
{
public:
	WarningLayerSaveFile();
	virtual ~WarningLayerSaveFile();

	static WarningLayerSaveFile* create(std::string strFileName);

	bool init(std::string strFileName);

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	virtual void draw();

private:

	void menuItemTouched(cocos2d::CCObject* pSender);

public:
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemYes, MenuItemYes);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemNo, MenuItemNo);
	CC_SYNTHESIZE(FunctionLayer*, m_delegateLayer, DelegateLayer);

	cocos2d::CCSize m_winSize;
	cocos2d::CCSize m_sizeBG;

	std::string m_strFileName;
};