#include "WarningLayerSaveFile.h"
#include "FunctionLayer.h"
#include "ViewEnum.h"
#include "LanguageCache.h"

using namespace cocos2d;


WarningLayerSaveFile* WarningLayerSaveFile::create( std::string strFileName )
{
	WarningLayerSaveFile* pRet = new WarningLayerSaveFile();
	if (pRet && pRet->init(strFileName))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}


WarningLayerSaveFile::WarningLayerSaveFile()
	: m_menuItemYes(NULL)
	, m_menuItemNo(NULL)
	, m_delegateLayer(NULL)
{

}

WarningLayerSaveFile::~WarningLayerSaveFile()
{

}

bool WarningLayerSaveFile::init(std::string strFileName)
{
	if (!CCLayerColor::initWithColor(ccc4(0,0,0,80)))
	{
		return false;
	}

	m_strFileName = strFileName;
	m_winSize = CCDirector::sharedDirector()->getWinSize();
	m_sizeBG= CCSizeMake(550, 250);

	CCLayerColor* layerBG = CCLayerColor::create(ccc4(100,180,225,255), m_sizeBG.width, m_sizeBG.height);
	layerBG->setPosition(ccp((m_winSize.width-m_sizeBG.width)*0.5f, (m_winSize.height-m_sizeBG.height)*0.5f));
	this->addChild(layerBG, zOrder_BackGround);

	CCLabelTTF* label = CCLabelTTF::create(LanguageCache::sharedCache()->valueForKey("language_2_2"), "Arial", 30);
	label->setPosition(ccp(m_winSize.width*0.5f, m_winSize.height*0.5f+50));
	label->setColor(ccRED);
	this->addChild(label, zOrder_CommonNode);

	CCMenuItemFont::setFontSize(30);
	m_menuItemYes = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_2_3"), this, menu_selector(WarningLayerSaveFile::menuItemTouched));
	m_menuItemNo = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_2_4"), this, menu_selector(WarningLayerSaveFile::menuItemTouched));
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

bool WarningLayerSaveFile::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void WarningLayerSaveFile::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void WarningLayerSaveFile::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, touch_PopLayer, true);
}

void WarningLayerSaveFile::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void WarningLayerSaveFile::draw()
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

void WarningLayerSaveFile::menuItemTouched( cocos2d::CCObject* pSender )
{
	CCMenuItemFont* menuItem = (CCMenuItemFont*)pSender;
	if (menuItem == m_menuItemYes)
	{
		m_delegateLayer->saveToFile(m_strFileName);
	}
	else
	{
		m_delegateLayer->showLayerSaveFile();
	}
	this->removeFromParent();
}

