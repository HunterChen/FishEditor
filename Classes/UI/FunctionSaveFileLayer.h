#pragma once

#include "cocos2d.h"

class FunctionLayer;


class FunctionSaveFileLayer : public cocos2d::CCLayerColor, public cocos2d::CCTextFieldDelegate  
{
public:
	FunctionSaveFileLayer();
	virtual ~FunctionSaveFileLayer();

	CREATE_FUNC(FunctionSaveFileLayer);

	virtual bool init();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	virtual void draw();

	virtual bool onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF * sender);
	virtual bool onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF * sender);
    virtual bool onTextFieldInsertText(cocos2d::CCTextFieldTTF * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF * sender, const char * delText, int nLen);

private:

	void menuItemTouched(cocos2d::CCObject* pSender);

public:

	CC_SYNTHESIZE_READONLY(cocos2d::CCLayerColor*, m_textFieldBackGround, TextFieldBackGround);
	CC_SYNTHESIZE_READONLY(cocos2d::CCTextFieldTTF*, m_textField, TextField);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemYes, MenuItemYes);
	CC_SYNTHESIZE_READONLY(cocos2d::CCMenuItemFont*, m_menuItemNo, MenuItemNo);
	CC_SYNTHESIZE(FunctionLayer*, m_delegateLayer, DelegateLayer);

	cocos2d::CCSize m_winSize;
	cocos2d::CCSize m_sizeBG;
	cocos2d::CCSize m_sizeField;
	cocos2d::CCAction* m_pTextFieldAction;
};