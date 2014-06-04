#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include <string>

class FunctionLayer;

class FunctionFileListLayer : public cocos2d::CCLayerColor, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	FunctionFileListLayer();
	virtual ~FunctionFileListLayer();

	static void removeFileList();

	static FunctionFileListLayer* create(cocos2d::CCPoint posList, cocos2d::CCSize listSize);

	virtual bool init(cocos2d::CCPoint posList, cocos2d::CCSize listSize);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	virtual void draw();

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};

	virtual void tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:

	CC_SYNTHESIZE(FunctionLayer*, m_delegateLayer, DelegateLayer);

private:

	void getAllFilePath();
	void updateTable();

private:

	static FunctionFileListLayer* m_pInstance;

	cocos2d::CCPoint m_positionListLeftTop;

	cocos2d::CCSize m_listSize;

	std::vector<std::string> m_vecAllFilePath;

	cocos2d::extension::CCTableView* m_tableView;
};