#include "FunctionSaveFileLayer.h"
#include "FunctionLayer.h"
#include "ViewEnum.h"
#include "LanguageCache.h"

using namespace cocos2d;

#define TEXT_LENGTH_LIMIT 30


FunctionSaveFileLayer::FunctionSaveFileLayer()
	: m_textFieldBackGround(NULL)
	, m_textField(NULL)
	, m_menuItemYes(NULL)
	, m_menuItemNo(NULL)
	, m_delegateLayer(NULL)
{
	m_pTextFieldAction = CCRepeatForever::create( CCSequence::create(CCFadeOut::create(0.25f), CCFadeIn::create(0.25f), NULL) );
	m_pTextFieldAction->retain();
}

FunctionSaveFileLayer::~FunctionSaveFileLayer()
{
	m_pTextFieldAction->release();
}

bool FunctionSaveFileLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0,0,0,80)))
	{
		return false;
	}

	m_winSize = CCDirector::sharedDirector()->getWinSize();
	m_sizeBG= CCSizeMake(550, 250);
	m_sizeField = CCSizeMake(500, 50);

	CCLayerColor* layerBG = CCLayerColor::create(ccc4(100,180,225,255), m_sizeBG.width, m_sizeBG.height);
	layerBG->setPosition(ccp((m_winSize.width-m_sizeBG.width)*0.5f, (m_winSize.height-m_sizeBG.height)*0.5f));
	this->addChild(layerBG, zOrder_BackGround);

	m_textFieldBackGround = CCLayerColor::create(ccc4(255,255,255,255), m_sizeField.width, m_sizeField.height);
	m_textFieldBackGround->setPosition(ccp((m_winSize.width-m_sizeField.width)*0.5f, (m_winSize.height-m_sizeField.height)*0.5f+25));
	this->addChild(m_textFieldBackGround, zOrder_CommonNode);

	m_textField = CCTextFieldTTF::textFieldWithPlaceHolder("Touch Here To Input File Name", "Arial", 20);
	m_textField->setPosition(ccp(m_sizeField.width*0.5f, m_sizeField.height*0.5f));  
	m_textFieldBackGround->addChild(m_textField);
	m_textField->setDelegate(this);
	m_textField->setColor(ccBLACK);


	CCMenuItemFont::setFontSize(30);
	m_menuItemYes = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_2_3"), this, menu_selector(FunctionSaveFileLayer::menuItemTouched));
	m_menuItemNo = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_2_4"), this, menu_selector(FunctionSaveFileLayer::menuItemTouched));
	m_menuItemYes->setPosition(ccp(m_winSize.width*0.5f-80, m_winSize.height*0.5f-50));
	m_menuItemNo->setPosition(ccp(m_winSize.width*0.5f+80, m_winSize.height*0.5f-50));
	m_menuItemYes->setColor(ccBLACK);
	m_menuItemNo->setColor(ccBLACK);
	CCMenu* menu = CCMenu::create(m_menuItemYes, m_menuItemNo, NULL);
	menu->setPosition(CCPointZero);
	menu->setTouchPriority(touch_ButtonOnPopLayer);
	this->addChild(menu, zOrder_CommonNode);


	return true;
}

bool FunctionSaveFileLayer::onTextFieldAttachWithIME( CCTextFieldTTF * sender )
{
	return false;
}

bool FunctionSaveFileLayer::onTextFieldDetachWithIME( CCTextFieldTTF * sender )
{
	return false;
}

bool FunctionSaveFileLayer::onTextFieldInsertText( CCTextFieldTTF * sender, const char * text, int nLen )
{
	if ('\n' == *text)
	{
		m_textField->stopAllActions();
		m_textField->setOpacity(255);
		return false;
	}
	if (sender->getCharCount() >= TEXT_LENGTH_LIMIT)
	{
		return true;
	}
	return false;
}

bool FunctionSaveFileLayer::onTextFieldDeleteBackward( CCTextFieldTTF * sender, const char * delText, int nLen )
{
	return false;
	//return true;²»É¾³ý
}

bool FunctionSaveFileLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint pos = pTouch->getLocation();
	CCRect rect = m_textFieldBackGround->boundingBox();
	if (rect.containsPoint(pos))
	{
		m_textField->attachWithIME();
		m_textField->stopAllActions();
		m_textField->runAction(m_pTextFieldAction);
	}
	else
	{
		m_textField->detachWithIME();
		m_textField->stopAllActions();
		m_textField->setOpacity(255);
	}

	return true;
}

void FunctionSaveFileLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void FunctionSaveFileLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, touch_PopLayer, true);
}

void FunctionSaveFileLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void FunctionSaveFileLayer::menuItemTouched( cocos2d::CCObject* pSender )
{
	CCMenuItemFont* menuItem = (CCMenuItemFont*)pSender;
	if (menuItem == m_menuItemYes)
	{
		m_delegateLayer->checkSaveFile();
	}
	else
	{
		this->removeFromParent();
	}
}

void FunctionSaveFileLayer::draw()
{
	CCLayerColor::draw();

	glLineWidth(2);
	ccDrawColor4B(0,0,0,255);

	CCPoint posLT = ccp((m_winSize.width-m_sizeBG.width)*0.5f-1, (m_winSize.height+m_sizeBG.height)*0.5f+1);
	CCPoint posLB = ccp((m_winSize.width-m_sizeBG.width)*0.5f-1, (m_winSize.height-m_sizeBG.height)*0.5f-1);
	CCPoint posRT = ccp((m_winSize.width+m_sizeBG.width)*0.5f+1, (m_winSize.height+m_sizeBG.height)*0.5f+1);
	CCPoint posRB = ccp((m_winSize.width+m_sizeBG.width)*0.5f+1, (m_winSize.height-m_sizeBG.height)*0.5f-1);

	ccDrawLine(posLT, posLB);
	ccDrawLine(posLT, posRT);
	ccDrawLine(posRT, posRB);
	ccDrawLine(posLB, posRB);

	//restore original values
	glLineWidth(1);
	ccDrawColor4B(255,255,255,255);
	ccPointSize(1);
}

