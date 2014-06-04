#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

class FunctionSaveFileLayer;

class FunctionLayer: public cocos2d::CCLayerColor
{
public:
	FunctionLayer();
	virtual ~FunctionLayer();

	CREATE_FUNC(FunctionLayer);

	virtual bool init();

	void initMenu();

	void checkSaveFile();
	void saveToFile(std::string strFileName);
	void showLayerSaveFile();

	void openFile(std::string strFileName);


private:

	void menuItemTouched(cocos2d::CCObject* pSender);
	void menuItemToggleTouched(cocos2d::CCObject* pSender);

	void buildNewMap();

	std::vector<std::string> getAllFileName();

public:

	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemNewFile, MenuItemNewFile);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemOpenFile, MenuItemOpenFile);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemSaveFile, MenuItemSaveFile);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemSaveAsFile, MenuItemSaveAsFile);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemChangePrecision, MenuItemChangePrecision);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemToggle*, m_menuItemToggleMode, MenuItemToggleMode);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemToggle*, m_menuItemToggleClear, MenuItemToggleClear);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemToggle*, m_menuItemToggleDrag, MenuItemToggleDrag);

	CC_SYNTHESIZE_READONLY(std::string, m_curFileName, CurFileName);
	CC_SYNTHESIZE_READONLY(bool, m_isModeX, IsModeX);
	CC_SYNTHESIZE_READONLY(bool, m_isClear, IsClear);
	CC_SYNTHESIZE_READONLY(bool, m_isDrag, IsDrag);


	CC_SYNTHESIZE_READONLY(FunctionSaveFileLayer*, m_saveFileLayer, SaveFileLayer);
	
};