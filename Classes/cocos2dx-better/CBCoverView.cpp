#include "CBCoverView.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define Z_ORDER_MAX 0x7fff


CBCoverView::CBCoverView()
	: m_arrayCard(NULL)
	, m_scrollViewCover(NULL)
	, m_containLayer(NULL)
	, m_sizeScrollView(CCSizeZero)
	, m_touchPriority(0)
	, m_incrementDistance(0)
	, m_incrementScale(0)
	, m_middleCardPosition(CCPointZero)
	, m_middleCardScale(1)
	, m_cardNumber(0)
	, m_curIndex(0)
{
	m_arrayCard = CCArray::create();
	m_arrayCard->retain();
}

CBCoverView::~CBCoverView()
{
	m_arrayCard->removeAllObjects();
	m_arrayCard->release();
}

CBCoverView* CBCoverView::create( unsigned int cellCount, cocos2d::CCSize size, int touchPriority )
{
	return CBCoverView::create(cellCount, size, touchPriority, 1.0f);
}

CBCoverView* CBCoverView::create( unsigned int cellCount, cocos2d::CCSize size, int touchPriority, float middleCardScale )
{
	CBCoverView* pRet = new CBCoverView();
	if(pRet && pRet->init(cellCount, size, touchPriority, middleCardScale))  
	{  
		pRet->autorelease();
		return pRet;
	}  
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBCoverView* CBCoverView::create( unsigned int cellCount, float incrementScale, cocos2d::CCSize size, int touchPriority )
{
	return CBCoverView::create(cellCount, incrementScale, size, touchPriority, 1.0f);
}

CBCoverView* CBCoverView::create( unsigned int cellCount, float incrementScale, cocos2d::CCSize size, int touchPriority, float middleCardScale )
{
	CBCoverView* pRet = new CBCoverView();
	if(pRet && pRet->init(cellCount, incrementScale, size, touchPriority, middleCardScale))  
	{  
		pRet->autorelease();
		return pRet;
	}  
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBCoverView* CBCoverView::create( cocos2d::CCSize size, float incrementDistance, float incrementScale, int touchPriority )
{
	return CBCoverView::create(size, incrementDistance, incrementScale, touchPriority, 1.0f);
}

CBCoverView* CBCoverView::create( cocos2d::CCSize size, float incrementDistance, float incrementScale, int touchPriority, float middleCardScale )
{
	CBCoverView* pRet = new CBCoverView();
	if(pRet && pRet->init(size, incrementDistance, incrementScale, touchPriority, middleCardScale))  
	{  
		pRet->autorelease();
		return pRet;
	}  
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBCoverView::init( unsigned int cellCount, cocos2d::CCSize size, int touchPriority, float middleCardScale )
{
	return init(size, size.width/(float)cellCount, middleCardScale/(float)cellCount, touchPriority, middleCardScale);
}

bool CBCoverView::init( unsigned int cellCount, float incrementScale, cocos2d::CCSize size, int touchPriority, float middleCardScale )
{
	return init(size, size.width/(float)cellCount, 0, touchPriority, middleCardScale);
}

bool CBCoverView::init( cocos2d::CCSize size, float incrementDistance, float incrementScale, int touchPriority, float middleCardScale )
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_sizeScrollView = size;
	m_incrementDistance = incrementDistance;
	m_incrementScale = incrementScale;
	m_touchPriority = touchPriority;
	m_middleCardScale = middleCardScale;
	m_middleCardPosition = ccp(m_sizeScrollView.width*0.5f, m_sizeScrollView.height*0.5f);
	m_cardNumber = 0;

	this->setAnchorPoint(CCPointZero);
	this->initView();

	return true;
}

void CBCoverView::initView()
{
	m_containLayer = CCLayer::create();
	m_containLayer->setAnchorPoint(CCPointZero);
	m_containLayer->setPosition(CCPointZero);
	m_containLayer->setContentSize(m_sizeScrollView);

	m_scrollViewCover = CCScrollView::create(m_sizeScrollView, m_containLayer);
	m_scrollViewCover->setAnchorPoint(CCPointZero);
	m_scrollViewCover->setPosition(CCPointZero);
	m_scrollViewCover->setContentOffset(CCPointZero);
	m_scrollViewCover->setTouchEnabled(false);
	m_scrollViewCover->setDelegate(this);
	m_scrollViewCover->setDirection(kCCScrollViewDirectionHorizontal);
	this->addChild(m_scrollViewCover);
}

void CBCoverView::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, true);
}

void CBCoverView::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool CBCoverView::ccTouchBegan( cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent )
{
	//CCPoint pos = pTouch->getLocation();
	CCPoint pos = this->convertTouchToNodeSpace(pTouch);
	CCRect rect = m_scrollViewCover->boundingBox();
	if (rect.containsPoint(pos))
	{
		return true;
	}
	return false;
}

void CBCoverView::ccTouchMoved( cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent )
{
	CCPoint posPrevious = pTouch->getPreviousLocation();
	posPrevious = this->convertToNodeSpace(posPrevious);

	CCPoint pos = this->convertTouchToNodeSpace(pTouch);
	CCRect rect = m_scrollViewCover->boundingBox();
	if (rect.containsPoint(pos))
	{
		CCPoint adjustPoint = pos - posPrevious;  
		adjustScrollView(adjustPoint);    
		adjustCard(adjustPoint);
	}
}

void CBCoverView::ccTouchEnded( cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent )
{
	adjustScrollViewEnd();
}

void CBCoverView::ccTouchCancelled( cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent )
{
	ccTouchEnded(pTouch, pEvent);
}

void CBCoverView::addCard( cocos2d::CCNode* card )
{
	int zOrder = Z_ORDER_MAX - m_cardNumber;
	float posX = m_middleCardPosition.x + m_incrementDistance*m_cardNumber;
	float scale = m_middleCardScale - m_incrementScale*m_cardNumber;
	if (scale < 0)
	{
		scale = 0;
	}
	card->setPosition(ccp(posX, m_middleCardPosition.y));
	card->setScale(scale);
	m_containLayer->addChild(card, zOrder, m_cardNumber);
	m_arrayCard->addObject(card);
	m_cardNumber++;
}

void CBCoverView::adjustCard( cocos2d::CCPoint adjustPoint )
{
	CCObject* obj = NULL;  
	CCARRAY_FOREACH(m_arrayCard, obj)
	{  
		CCNode* card = (CCNode*)obj;
		float offset = m_scrollViewCover->getContentOffset().x;
		float posX = card->getPositionX() + offset;

		float incrementPosX = fabs(m_middleCardPosition.x - posX);
		float incrementCount = incrementPosX/m_incrementDistance;
		//CCLOG("%.2f", incrementCount);
		float scale = m_middleCardScale - incrementCount*m_incrementScale;
		card->setScale(scale);

		int zOrder = (Z_ORDER_MAX - incrementCount*100);
		card->setZOrder(zOrder);
	}
}

void CBCoverView::adjustScrollView( cocos2d::CCPoint adjustPoint )
{
	CCPoint endPoint = ccpAdd(m_scrollViewCover->getContentOffset(), ccp(adjustPoint.x,0));
	m_scrollViewCover->unscheduleAllSelectors();
	m_scrollViewCover->setContentOffset(endPoint, false);
}

void CBCoverView::adjustScrollViewEnd()
{
	float minIncrementPosX = m_incrementDistance*m_cardNumber;

	//获取距离中间最近的card
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_arrayCard, obj)
	{  
		CCNode* card = (CCNode*)obj;
		float offset = m_scrollViewCover->getContentOffset().x;
		float posX = card->getPositionX() + offset;
		float incrementPosX = m_middleCardPosition.x - posX;
		if (fabs(incrementPosX) < fabs(minIncrementPosX))
		{
			minIncrementPosX = incrementPosX;
			m_curIndex = card->getTag();
		}
	}

	float timeAction = 0.1f;

	CCARRAY_FOREACH(m_arrayCard, obj)
	{
		CCNode* card = (CCNode*)obj;
		float offset = m_scrollViewCover->getContentOffset().x;
		float posX = card->getPositionX() + offset;
		float incrementPosX = fabs(m_middleCardPosition.x - posX - minIncrementPosX);
		float incrementCount = incrementPosX/m_incrementDistance;
		float scale = m_middleCardScale - incrementCount*m_incrementScale;
		CCScaleTo* scaleBy = CCScaleTo::create(timeAction, scale);
		card->stopAllActions();
		card->runAction(scaleBy);

		int zOrder = (Z_ORDER_MAX - incrementCount*100);
		card->setZOrder(zOrder);
	}

	CCMoveBy* moveBy = CCMoveBy::create(timeAction, ccp(minIncrementPosX, 0));
	m_containLayer->stopAllActions();
	m_containLayer->runAction(moveBy);
}

int CBCoverView::getCurIndexMiddleCard()
{
	return m_curIndex;
}
