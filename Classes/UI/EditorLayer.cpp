#include "EditorLayer.h"
#include "ViewDefine.h"
#include "ViewEnum.h"
#include "FunctionLayer.h"
#include "SpriteListLayer.h"
#include "AdjustLayer.h"
#include "EditorSprite.h"
#include "PrecisionManager.h"
#include "../Tool/csv_parser/CCSVParse.h"
#include "../cocos2dx-better/CBFileTool.h"
#include "../Config/SpirteConfig/SpirteConfigCache.h"
#include <vector>

using namespace cocos2d;
using namespace cocos2d::extension;


EditorScene::EditorScene()
	: m_LayerEditor(NULL)
{

}

EditorScene::~EditorScene()
{

}

EditorScene* EditorScene::getScene()
{
	static EditorScene* scene = NULL;
	if (scene == NULL)
	{
		scene = new EditorScene();
		scene->startEditor();
	}
	return scene;
}

void EditorScene::startEditor()
{
	if (m_LayerEditor != NULL)
	{
		if (m_LayerEditor->getParent() != NULL)
		{
			m_LayerEditor->removeFromParent();
		}
		CC_SAFE_RELEASE_NULL(m_LayerEditor);
	}

	this->removeAllChildren();
	m_LayerEditor = EditorLayer::create();
	m_LayerEditor->retain();
	this->addChild(m_LayerEditor);
}



EditorLayer::EditorLayer()
	: m_layerFunction(NULL)
	, m_layerSpriteList(NULL)
	, m_scrollView(NULL)
	, m_containerLayer(NULL)
	, m_batchNode(NULL)
	, m_adjustLayer(NULL)
	, m_arraySprite(NULL)
	, m_curTouchSprite(NULL)
{
	m_arraySprite = CCArray::create();
	m_arraySprite->retain();
}

EditorLayer::~EditorLayer()
{
	m_arraySprite->removeAllObjects();
	m_arraySprite->release();
}

bool EditorLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_layerFunction = FunctionLayer::create();
	m_layerFunction->setPosition(ccp(0, 0));
	this->addChild(m_layerFunction, zOrder_CommonNode);

	m_layerSpriteList = SpriteListLayer::create();
	m_layerSpriteList->setPosition(ccp(winSize.width - WIDTH_LIST_LAYER + WIDTH_BORDER_LINE/2.0f, 0));
	this->addChild(m_layerSpriteList, zOrder_CommonNode);

	this->initScrollView();

	return true;
}

void EditorLayer::initScrollView()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_scrollView = CCScrollView::create(CCSizeMake(winSize.width - WIDTH_FUNCTION_LAYER - WIDTH_LIST_LAYER, winSize.height));
	m_scrollView->setContentSize(CCSizeMake(WIDTH_SCROLL_VIEW, HEIGHT_SCROLL_VIEW));
	m_scrollView->setDelegate(this);
	m_scrollView->setDirection(kCCScrollViewDirectionHorizontal);
	m_scrollView->setAnchorPoint(CCPointZero);
	m_scrollView->setPosition(ccp(WIDTH_FUNCTION_LAYER, 0));
	m_scrollView->setContentOffset(CCPointZero);
	m_scrollView->setTouchPriority(touch_ScrollViewOnBackGround);
	m_scrollView->setTouchEnabled(false);
	this->addChild(m_scrollView, zOrder_BackGround);

	m_containerLayer = CCLayer::create();
	m_containerLayer->setContentSize(CCSizeMake(WIDTH_SCROLL_VIEW, HEIGHT_SCROLL_VIEW));
	m_scrollView->setContainer(m_containerLayer);

	m_batchNode = CCSpriteBatchNode::create("Resource/sprite.png");
	m_adjustLayer = AdjustLayer::create();
	m_containerLayer->addChild(m_batchNode, zOrder_BackGround);
	m_containerLayer->addChild(m_adjustLayer, zOrder_CoverLayer);
}

void EditorLayer::draw()
{
	CCLayerColor::draw();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	glLineWidth(WIDTH_BORDER_LINE);
	ccDrawColor4B(255,0,0,255);
	ccDrawLine(ccp(WIDTH_FUNCTION_LAYER - WIDTH_BORDER_LINE/2.0f, 0), ccp(WIDTH_FUNCTION_LAYER - WIDTH_BORDER_LINE/2.0f, winSize.height));
	ccDrawLine(ccp(winSize.width - WIDTH_LIST_LAYER + WIDTH_BORDER_LINE/2.0f, 0), ccp(winSize.width - WIDTH_LIST_LAYER + WIDTH_BORDER_LINE/2.0f, winSize.height));

	//restore original values
	glLineWidth(1);
	ccDrawColor4B(255,255,255,255);
	ccPointSize(1);
}

bool EditorLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint pos = pTouch->getLocation();
	CCRect rect = m_scrollView->boundingBox();
	if (!rect.containsPoint(pos))
	{
		return false;
	}
	if (m_layerFunction->getIsDrag())
	{
		return false;
	}

	if (m_layerFunction->getIsClear())
	{
		this->removeSpriteInTouch(pTouch);
	}
	else
	{
		m_curTouchSprite = this->findTouchSprite(pTouch);
		if (m_curTouchSprite == NULL)
		{
			m_curTouchSprite = EditorSprite::create(m_layerSpriteList->getCurSpirteConfig());
			if (m_layerFunction->getIsModeX() == false)
			{
				m_curTouchSprite->setRotation(-90);
			}

			if (this->checkSpriteIsOutEditorRect(m_curTouchSprite, pTouch))
			{
				CC_SAFE_RELEASE_NULL(m_curTouchSprite);
			}
			else
			{
				m_curTouchSprite->setOrderForAdd(m_arraySprite->count());
				m_curTouchSprite->setPosition(adjustPositionForTouch(pTouch));
				m_batchNode->addChild(m_curTouchSprite);
				m_arraySprite->addObject(m_curTouchSprite);
			}
		}
	}

	return true;
}

void EditorLayer::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_layerFunction->getIsClear())
	{
		this->removeSpriteInTouch(pTouch);
	}
	else
	{
		this->resetSpritePositionInTouch(pTouch);
	}
}

void EditorLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_layerFunction->getIsClear())
	{
		this->removeSpriteInTouch(pTouch);
	}
	else
	{
		this->resetSpritePositionInTouch(pTouch);
	}
}

void EditorLayer::ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	ccTouchEnded(pTouch, pEvent);
}

void EditorLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, touch_BackGround, true);
}

void EditorLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

EditorSprite* EditorLayer::findTouchSprite( cocos2d::CCTouch *pTouch )
{
	CCPoint pos = m_containerLayer->convertTouchToNodeSpace(pTouch);
	pos = pTouch->getLocation();
	CCLOG("position x = %.0f, y = %.0f", pos.x, pos.y);


	CCArray* arraySprites = new CCArray();
	arraySprites->init();

	for (unsigned int i=0; i<m_arraySprite->count(); i++)
	{
		EditorSprite* pEditorSprite = (EditorSprite*)m_arraySprite->objectAtIndex(i);
		if (!pEditorSprite->isTransparentInPoint(pos))
		{
			arraySprites->addObject(pEditorSprite);
		}
	}

	EditorSprite* pRet = NULL;
	if (arraySprites->count() > 0)
	{
		pRet = (EditorSprite*)arraySprites->objectAtIndex(0);
	}
	for (unsigned int i=0; i<arraySprites->count(); i++)
	{
		EditorSprite* pEditorSprite = (EditorSprite*)arraySprites->objectAtIndex(i);
		if (pEditorSprite->getOrderForAdd() > pRet->getOrderForAdd())
		{
			pRet = pEditorSprite;
		}
	}

	arraySprites->removeAllObjects();
	delete arraySprites;

	return pRet;
}

cocos2d::CCPoint EditorLayer::adjustIndexForTouch( cocos2d::CCTouch *pTouch )
{
	int precision = PrecisionManager::sharedManager()->getCurPrecision();
	CCPoint pos = m_containerLayer->convertTouchToNodeSpace(pTouch);
	int idxX = pos.x/precision;
	int idxY = pos.y/precision;
	return ccp(idxX, idxY);
}

cocos2d::CCPoint EditorLayer::adjustPositionForIndex( cocos2d::CCPoint index )
{
	int precision = PrecisionManager::sharedManager()->getCurPrecision();
	return ccp((index.x + 0.5f)*precision, (index.y + 0.5f)*precision);
}

cocos2d::CCPoint EditorLayer::adjustPositionForTouch( cocos2d::CCTouch *pTouch )
{
	return adjustPositionForIndex(adjustIndexForTouch(pTouch));
}

void EditorLayer::setScrollViewIsCanDrag( bool isCanDrag )
{
	m_scrollView->setTouchEnabled(isCanDrag);
}

bool EditorLayer::checkSpriteIsOutEditorRect( EditorSprite* sprite, cocos2d::CCTouch *pTouch )
{
	CCPoint posAdjust = this->adjustPositionForTouch(pTouch);
	CCSize sizeSprite = sprite->boundingBox().size;

	CCPoint posLT = ccp(posAdjust.x-sizeSprite.width*0.5f, posAdjust.y+sizeSprite.height*0.5f);
	CCPoint posLB = ccp(posAdjust.x-sizeSprite.width*0.5f, posAdjust.y-sizeSprite.height*0.5f);
	CCPoint posRT = ccp(posAdjust.x+sizeSprite.width*0.5f, posAdjust.y+sizeSprite.height*0.5f);
	CCPoint posRB = ccp(posAdjust.x+sizeSprite.width*0.5f, posAdjust.y-sizeSprite.height*0.5f);

	std::vector<CCPoint> vecPoint;
	vecPoint.push_back(posLT);
	vecPoint.push_back(posLB);
	vecPoint.push_back(posRT);
	vecPoint.push_back(posRB);

	CCSize viewSize = m_scrollView->getViewSize();
	CCSize contenSize = m_scrollView->getContentSize();

	for (unsigned int i=0; i<vecPoint.size(); i++)
	{
		if (m_layerFunction->getIsModeX())
		{
			if ((vecPoint[i].x < 0) || (vecPoint[i].x > contenSize.width) || (vecPoint[i].y < 0) || (vecPoint[i].y > viewSize.height))
			{
				return true;
			}
		}
		else
		{
			if ((vecPoint[i].x < 0) || (vecPoint[i].x > viewSize.width) || (vecPoint[i].y < 0) || (vecPoint[i].y > contenSize.height))
			{
				return true;
			}
		}
	}
	return false;
}

void EditorLayer::removeSprite( EditorSprite* sprite )
{
	int orderAdd = sprite->getOrderForAdd();
	m_arraySprite->removeObject(sprite);
	sprite->removeFromParent();

	for (unsigned int i=0; i<m_arraySprite->count(); i++)
	{
		EditorSprite* tmp = (EditorSprite*)m_arraySprite->objectAtIndex(i);
		int orderTmp = tmp->getOrderForAdd();
		if (orderTmp > orderAdd)
		{
			tmp->setOrderForAdd(orderTmp - 1);
		}
	}
}

void EditorLayer::removeSpriteInTouch( cocos2d::CCTouch *pTouch )
{
	EditorSprite* spriteTouch = this->findTouchSprite(pTouch);
	if (spriteTouch != NULL)
	{
		this->removeSprite(spriteTouch);
	}
}

void EditorLayer::resetSpritePositionInTouch( cocos2d::CCTouch *pTouch )
{
	if (m_curTouchSprite != NULL)
	{
		if (!(this->checkSpriteIsOutEditorRect(m_curTouchSprite, pTouch)))
		{
			m_curTouchSprite->setPosition(adjustPositionForTouch(pTouch));
		}
	}
}

std::string EditorLayer::getEditorInfoStringWithCSV()
{
	std::string strCSV = "";
	strCSV += "positionX,";
	strCSV += "positionY,";
	strCSV += "Type\n";

	for (unsigned int i=0; i<m_arraySprite->count(); i++)
	{
		EditorSprite* sprite = (EditorSprite*)m_arraySprite->objectAtIndex(i);
		CCPoint pos = sprite->getPosition();
		CCSize viewSize = m_scrollView->getViewSize();

		CCPoint posMode;
		if (m_layerFunction->getIsModeX())
		{
			posMode = ccp(pos.x, pos.y - viewSize.height*0.5f);
		}
		else
		{
			posMode = ccp(pos.x - viewSize.width*0.5f, pos.y);
		}

		std::string strType = sprite->getConfigSpirte().getTypeName();

		strCSV += CCString::createWithFormat("%.0f,%.0f,", posMode.x, posMode.y)->m_sString;
		strCSV += strType;
		strCSV += "\n";
	}

	return strCSV;
}

void EditorLayer::resetMapWithFile( std::string fileName )
{
	m_batchNode->removeAllChildren();
	m_arraySprite->removeAllObjects();

	//
	std::string strFileName = "";
	if (m_layerFunction->getIsModeX())
	{
		strFileName = FOLDER_NAME_MODE_X;
	}
	else
	{
		strFileName = FOLDER_NAME_MODE_Y;
	}
	strFileName += "/";
	strFileName += fileName;
	strFileName += ".csv";

	//
	std::string strFilePath = CBFileTool::getFullPath(strFileName.c_str());
	std::string strFileData = CBFileTool::getFileData(strFilePath.c_str());

	CCSVParse* csvParse = new CCSVParse();
	if (!(csvParse->Parse(strFileData)))
	{
		delete csvParse;
		return;
	}
	int cols = csvParse->getCols();
	int rows = csvParse->getRows();
	if (cols < 3)
	{
		delete csvParse;
		return;
	}
	for (int i=0; i<rows; i++)
	{
		float posX = atof(csvParse->getData(i, 0));
		float posY = atof(csvParse->getData(i, 1));
		std::string strType = csvParse->getData(i, 2);
		SpirteConfig config = SpirteConfigCache::sharedCache()->getSpirteConfigByType(strType);

		//
		EditorSprite* pSprite = EditorSprite::create(config);
		pSprite->setOrderForAdd(m_arraySprite->count());
		m_batchNode->addChild(pSprite);
		m_arraySprite->addObject(pSprite);

		CCPoint pos;
		CCSize sizeView = m_scrollView->getViewSize();
		if (m_layerFunction->getIsModeX())
		{
			pos = ccp(posX, posY+sizeView.height*0.5f);
		}
		else
		{
			pos = ccp(posX+sizeView.width*0.5f, posY);
			pSprite->setRotation(-90);
		}
		pSprite->setPosition(pos);
	}
	delete csvParse;
}

void EditorLayer::buildNewMap()
{
	m_batchNode->removeAllChildren();
	m_arraySprite->removeAllObjects();

	if (m_layerFunction->getIsModeX())
	{
		m_scrollView->setDirection(kCCScrollViewDirectionHorizontal);
		m_scrollView->setContentOffset(CCPointZero);
	}
	else
	{
		m_scrollView->setDirection(kCCScrollViewDirectionVertical);
		m_scrollView->setContentOffset(CCPointZero);
	}
}
