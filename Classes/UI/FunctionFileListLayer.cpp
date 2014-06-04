#include "FunctionFileListLayer.h"
#include "EditorLayer.h"
#include "FunctionLayer.h"
#include "../cocos2dx-better/CBFolderTool.h"
#include "ViewEnum.h"
#include "ViewDefine.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define CELL_SIZE_HEIGHT 30


FunctionFileListLayer* FunctionFileListLayer::m_pInstance = NULL;


void FunctionFileListLayer::removeFileList()
{
	if (m_pInstance != NULL)
	{
		if (m_pInstance->getParent() != NULL)
		{
			m_pInstance->removeFromParent();
		}
		CC_SAFE_DELETE(m_pInstance);
	}
}

FunctionFileListLayer* FunctionFileListLayer::create( cocos2d::CCPoint posList, cocos2d::CCSize listSize )
{
	removeFileList();
	m_pInstance = new FunctionFileListLayer();
	m_pInstance->init(posList, listSize);
	return m_pInstance;
}

FunctionFileListLayer::FunctionFileListLayer()
	: m_positionListLeftTop(CCPointZero)
	, m_listSize(CCSizeZero)
	, m_tableView(NULL)
	, m_delegateLayer(NULL)
{

}

FunctionFileListLayer::~FunctionFileListLayer()
{

}

bool FunctionFileListLayer::init( cocos2d::CCPoint posList, cocos2d::CCSize listSize )
{
	if (!CCLayerColor::initWithColor(ccc4(0,0,0,0)))
	{
		return false;
	}
	m_positionListLeftTop = posList;
	m_listSize = listSize;

	CCLayerColor* listBG = CCLayerColor::create(ccc4(255,255,255,255), listSize.width, listSize.height);
	listBG->setPosition(ccp(m_positionListLeftTop.x, m_positionListLeftTop.y-m_listSize.height));
	this->addChild(listBG, zOrder_BackGround);

	this->getAllFilePath();
	m_tableView = CCTableView::create(this, m_listSize);
	m_tableView->setDirection(kCCScrollViewDirectionVertical);
	m_tableView->setAnchorPoint(CCPointZero);
	m_tableView->setPosition(ccp(m_positionListLeftTop.x, m_positionListLeftTop.y-m_listSize.height));
	m_tableView->setDelegate(this);
	m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_tableView->setBounceable(false);
	m_tableView->setTouchPriority(touch_ScrollViewOnCoverLayer);
	this->addChild(m_tableView, zOrder_CommonNode);
	m_tableView->reloadData();

	return true;
}

void FunctionFileListLayer::tableCellHighlight( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	CCLayerColor* pBG = (CCLayerColor*)cell->getChildByTag(123);
	pBG->setVisible(true);
}

void FunctionFileListLayer::tableCellUnhighlight( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	CCLayerColor* pBG = (CCLayerColor*)cell->getChildByTag(123);
	pBG->setVisible(false);
}

void FunctionFileListLayer::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	int idx = cell->getIdx();
	std::string strFilePath = m_vecAllFilePath[idx];

	std::string::size_type startPos = strFilePath.find_last_of("\\");
	std::string::size_type endPos = strFilePath.find_last_of(".");
	std::string strFileName = strFilePath.substr(startPos+1, endPos-(startPos+1));

	m_delegateLayer->openFile(strFileName);
	this->removeFromParent();
}

cocos2d::CCSize FunctionFileListLayer::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(m_listSize.width, CELL_SIZE_HEIGHT);
}

cocos2d::extension::CCTableViewCell* FunctionFileListLayer::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = table->cellAtIndex(idx);
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCSize sizeCell = cellSizeForTable(table);
		float _w = 1.0f;
		CCLayerColor* pBG = CCLayerColor::create(ccc4(0,0,0,80), sizeCell.width - _w, sizeCell.height - _w);
		pBG->setPosition(ccp(_w*0.5f, _w*0.5f));
		pBG->setTag(123);
		pBG->setVisible(false);
		cell->addChild(pBG);

		CCLayerColor* pLine = CCLayerColor::create(ccc4(0,0,0,255), sizeCell.width - _w, _w);
		pLine->setPosition(ccp(_w*0.5f, _w*0.5f));
		cell->addChild(pLine);

		std::string strFilePath = m_vecAllFilePath[idx];
		std::string::size_type startPos = strFilePath.find_last_of("\\");
		std::string strFileName = strFilePath.substr(startPos+1, strFilePath.length()-(startPos+1));
		CCLabelTTF* labelName = CCLabelTTF::create(strFileName.c_str(), "Arial", 12);
		labelName->setAnchorPoint(ccp(0, 0.5f));
		labelName->setPosition(ccp(5, sizeCell.height*0.5f));
		labelName->setColor(ccBLACK);
		cell->addChild(labelName);
	}

	return cell;
}

unsigned int FunctionFileListLayer::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_vecAllFilePath.size();
}

void FunctionFileListLayer::updateTable()
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

void FunctionFileListLayer::getAllFilePath()
{
	EditorScene* pEditorScene = EditorScene::getScene();
	bool isModeX = pEditorScene->getLayerEditor()->getLayerFunction()->getIsModeX();
	
	std::vector<std::string> vecResourcePath = CCFileUtils::sharedFileUtils()->getSearchPaths();
	std::string strPath = vecResourcePath[0];
	if (isModeX)
	{
		strPath += FOLDER_NAME_MODE_X;
	}
	else
	{
		strPath += FOLDER_NAME_MODE_Y;
	}

	m_vecAllFilePath = CBFolderTool::AllFilePathInFolder(strPath);
}

void FunctionFileListLayer::draw()
{
	CCLayerColor::draw();

	if (!m_positionListLeftTop.equals(CCPointZero) && !m_listSize.equals(CCSizeZero))
	{
		glLineWidth(1);
		ccDrawColor4B(0,0,0,255);

		CCPoint posLT = ccp(m_positionListLeftTop.x-1, m_positionListLeftTop.y+1);
		CCPoint posLB = ccp(m_positionListLeftTop.x-1, m_positionListLeftTop.y-m_listSize.height-1);
		CCPoint posRT = ccp(m_positionListLeftTop.x+m_listSize.width+1, m_positionListLeftTop.y+1);
		CCPoint posRB = ccp(m_positionListLeftTop.x+m_listSize.width+1, m_positionListLeftTop.y-m_listSize.height-1);

		ccDrawLine(posLT, posLB);
		ccDrawLine(posLT, posRT);
		ccDrawLine(posRT, posRB);
		ccDrawLine(posLB, posRB);

		//restore original values
		glLineWidth(1);
		ccDrawColor4B(255,255,255,255);
		ccPointSize(1);
	}
}

bool FunctionFileListLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint pos = pTouch->getLocation();
	CCRect rect = m_tableView->boundingBox();
	if (!rect.containsPoint(pos))
	{
		this->removeFromParent();
	}
	return true;
}

void FunctionFileListLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void FunctionFileListLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, touch_CoverLayer, true);
}

void FunctionFileListLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
