#include "SpriteListLayer.h"
#include "ViewDefine.h"
#include "ViewEnum.h"

using namespace cocos2d;
using namespace cocos2d::extension;



bool SpriteListLayer::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (!CCLayerColor::initWithColor(ccc4(0,135,210,255), WIDTH_LIST_LAYER - WIDTH_BORDER_LINE/2.0f, winSize.height))
	{
		return false;
	}
	
	m_vecSpirteConfig = SpirteConfigCache::sharedCache()->getAllSpriteConfig();
	m_curSpirteConfig = m_vecSpirteConfig[0];

	m_tableView = CCTableView::create(this, CCSizeMake(WIDTH_LIST_LAYER - WIDTH_BORDER_LINE/2.0f, winSize.height));
	m_tableView->setDirection(kCCScrollViewDirectionVertical);
	m_tableView->setAnchorPoint(CCPointZero);
	m_tableView->setPosition(CCPointZero);
	m_tableView->setDelegate(this);
	m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_tableView->setBounceable(false);
	m_tableView->setTouchPriority(touch_ScrollViewOnCommonLayer);
	this->addChild(m_tableView);
	m_tableView->reloadData();

	return true;
}

void SpriteListLayer::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	int idx = cell->getIdx();
	m_curSpirteConfig = m_vecSpirteConfig[idx];
	this->updateTable();
}

cocos2d::CCSize SpriteListLayer::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(WIDTH_LIST_LAYER - WIDTH_BORDER_LINE/2.0f, WIDTH_LIST_LAYER - WIDTH_BORDER_LINE/2.0f);
}

cocos2d::extension::CCTableViewCell* SpriteListLayer::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = table->cellAtIndex(idx);
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCSize sizeCell = cellSizeForTable(table);
		float _w = 2.0f;
		CCLayerColor* pBG = CCLayerColor::create(ccc4(255,135,210,255), sizeCell.width - _w, sizeCell.height - _w);
		pBG->setPosition(ccp(_w*0.5f, _w*0.5f));
		pBG->setTag(123);
		cell->addChild(pBG);
		if (m_vecSpirteConfig[idx].getID() == m_curSpirteConfig.getID())
		{
			pBG->setColor(ccc3(0,135,210));
		}
		else
		{
			pBG->setColor(ccc3(255,135,210));
		}


		std::string strSpriteName = m_vecSpirteConfig[idx].getFrameName();
		CCSprite* pSprite = CCSprite::createWithSpriteFrameName(strSpriteName.c_str());
		float scaleX = (sizeCell.width - _w)/pSprite->getContentSize().width;
		float scaleY = (sizeCell.height - _w)/pSprite->getContentSize().height;
		float scale = (scaleX <= scaleY) ? (scaleX) : (scaleY);
		pSprite->setScale((scale >= 1) ? 1 : scale);
		pSprite->setPosition(ccp((sizeCell.width - _w)/2.0f, (sizeCell.height - _w)/2.0f));
		pBG->addChild(pSprite);
	}

	return cell;
}

unsigned int SpriteListLayer::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_vecSpirteConfig.size();
}

void SpriteListLayer::updateTable()
{
	for (unsigned int i=0; i<numberOfCellsInTableView(m_tableView); i++)
	{
		CCTableViewCell* cell = m_tableView->cellAtIndex(i);
		if (cell)
		{
			m_tableView->updateCellAtIndex(i);
		}
	}
}

