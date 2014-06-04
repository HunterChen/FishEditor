#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"


class CBCoverView : public cocos2d::CCLayer, public cocos2d::extension::CCScrollViewDelegate
{  
public:
    CBCoverView();
	
	virtual ~CBCoverView();

	//根据显示的个数自动计算位置增量，缩放增量
	static CBCoverView* create(unsigned int cellCount, cocos2d::CCSize size, int touchPriority);
	static CBCoverView* create(unsigned int cellCount, cocos2d::CCSize size, int touchPriority, float middleCardScale);

	static CBCoverView* create(unsigned int cellCount, float incrementScale, cocos2d::CCSize size, int touchPriority);
	static CBCoverView* create(unsigned int cellCount, float incrementScale, cocos2d::CCSize size, int touchPriority, float middleCardScale);

	//手动设置位置增量，缩放增量
    static CBCoverView* create(cocos2d::CCSize size, float incrementDistance, float incrementScale, int touchPriority);
	static CBCoverView* create(cocos2d::CCSize size, float incrementDistance, float incrementScale, int touchPriority, float middleCardScale);

	bool init(unsigned int cellCount, cocos2d::CCSize size, int touchPriority, float middleCardScale);
	bool init(unsigned int cellCount, float incrementScale, cocos2d::CCSize size, int touchPriority, float middleCardScale);
    bool init(cocos2d::CCSize size, float incrementDistance, float incrementScale, int touchPriority, float middleCardScale);

    virtual void onEnter();
    virtual void onExit();

    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	void addCard(cocos2d::CCNode* card);

protected:

    void initView();
    void adjustCard(cocos2d::CCPoint adjustPoint);
    void adjustScrollView(cocos2d::CCPoint adjustPoint);
    void adjustScrollViewEnd();
    int getCurIndexMiddleCard();//当前中间card索引(从0开始)

public:

	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_arrayCard, ArrayCard);
	CC_SYNTHESIZE_READONLY(cocos2d::extension::CCScrollView*, m_scrollViewCover, ScrollViewCover);
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_containLayer , ContainLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, m_sizeScrollView, SizeScrollView);
	CC_SYNTHESIZE_READONLY(int, m_touchPriority, TouchPriority);

    CC_SYNTHESIZE_READONLY(float, m_incrementDistance, IncrementDistance);
    CC_SYNTHESIZE_READONLY(float, m_incrementScale, IncrementScale);
	CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_middleCardPosition, MiddleCardPosition);
	CC_SYNTHESIZE_READONLY(float, m_middleCardScale, MiddleCardScale);
    CC_SYNTHESIZE_READONLY(int, m_cardNumber, CardNumber);
	CC_SYNTHESIZE_READONLY(int, m_curIndex, CurIndex);
}; 