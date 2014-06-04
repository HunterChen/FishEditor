#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../Config/SpirteConfig/SpirteConfigCache.h"


class SpriteListLayer : public cocos2d::CCLayerColor, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:

	CREATE_FUNC(SpriteListLayer);
	virtual bool init();
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	void updateTable();

public:
	CC_SYNTHESIZE_READONLY(SpirteConfig, m_curSpirteConfig, CurSpirteConfig);

private:
	std::vector<SpirteConfig> m_vecSpirteConfig;

	cocos2d::extension::CCTableView* m_tableView;
};