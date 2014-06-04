#include "FunctionLayer.h"
#include "ViewDefine.h"
#include "ViewEnum.h"
#include "LanguageCache.h"
#include "FunctionFileListLayer.h"
#include "EditorLayer.h"
#include "PrecisionManager.h"
#include "FunctionSaveFileLayer.h"
#include "WarningLayerSaveFile.h"
#include "../cocos2dx-better/CBFileTool.h"
#include "../cocos2dx-better/CBFolderTool.h"

using namespace cocos2d;

#define FILE_LIST_WIDTH 150
#define FILE_LIST_HEIGHT 250


FunctionLayer::FunctionLayer()
	: m_menuItemNewFile(NULL)
	, m_menuItemOpenFile(NULL)
	, m_menuItemSaveFile(NULL)
	, m_menuItemSaveAsFile(NULL)
	, m_menuItemToggleMode(NULL)
	, m_menuItemToggleClear(NULL)
	, m_menuItemToggleDrag(NULL)
	, m_curFileName("")
	, m_isModeX(true)
	, m_isClear(false)
	, m_isDrag(false)
	, m_saveFileLayer(NULL)
{

}

FunctionLayer::~FunctionLayer()
{

}

bool FunctionLayer::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (!CCLayerColor::initWithColor(ccc4(0,125,200,255), WIDTH_FUNCTION_LAYER-WIDTH_BORDER_LINE*0.5f, winSize.height))
	{
		return false;
	}
	this->initMenu();

	return true;
}

void FunctionLayer::initMenu()
{
	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(20);

	m_menuItemNewFile = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_1"), this, menu_selector(FunctionLayer::menuItemTouched));
	m_menuItemOpenFile = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_2"), this, menu_selector(FunctionLayer::menuItemTouched));
	m_menuItemSaveFile = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_3"), this, menu_selector(FunctionLayer::menuItemTouched));
	m_menuItemSaveAsFile = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_4"), this, menu_selector(FunctionLayer::menuItemTouched));
	m_menuItemChangePrecision = CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_11"), this, menu_selector(FunctionLayer::menuItemTouched));

	m_menuItemToggleMode = CCMenuItemToggle::createWithTarget(
		this,
		menu_selector(FunctionLayer::menuItemToggleTouched),
		CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_5")),
		CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_6")),
		NULL);

	m_menuItemToggleClear = CCMenuItemToggle::createWithTarget(
		this,
		menu_selector(FunctionLayer::menuItemToggleTouched),
		CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_7")),
		CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_8")),
		NULL);

	m_menuItemToggleDrag = CCMenuItemToggle::createWithTarget(
		this,
		menu_selector(FunctionLayer::menuItemToggleTouched),
		CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_9")),
		CCMenuItemFont::create(LanguageCache::sharedCache()->valueForKey("language_1_10")),
		NULL);

	m_menuItemToggleMode->setSelectedIndex((m_isModeX == true) ? (0) : (1));
	m_menuItemToggleClear->setSelectedIndex((m_isClear == false) ? (0) : (1));
	m_menuItemToggleDrag->setSelectedIndex((m_isDrag == false) ? (0) : (1));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_menuItemNewFile->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*15.0f/16.0f));
	m_menuItemOpenFile->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*13.0f/16.0f));
	m_menuItemSaveFile->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*11.0f/16.0f));
	m_menuItemSaveAsFile->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*9.0f/16.0f));
	m_menuItemToggleMode->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*7.0f/16.0f));
	m_menuItemToggleClear->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*5.0f/16.0f));
	m_menuItemToggleDrag->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*3.0f/16.0f));
	m_menuItemChangePrecision->setPosition(ccp(WIDTH_FUNCTION_LAYER*0.5f, winSize.height*1.0f/16.0f));
	m_menuItemNewFile->setColor(ccBLACK);
	m_menuItemOpenFile->setColor(ccBLACK);
	m_menuItemSaveFile->setColor(ccBLACK);
	m_menuItemSaveAsFile->setColor(ccBLACK);

	CCMenu* menu = CCMenu::create(
		m_menuItemNewFile,
		m_menuItemOpenFile,
		m_menuItemSaveFile,
		m_menuItemSaveAsFile,
		m_menuItemToggleMode,
		m_menuItemToggleClear,
		m_menuItemToggleDrag,
		m_menuItemChangePrecision,
		NULL);
	menu->setPosition(CCPointZero);
	menu->setTouchPriority(touch_ButtonOnCommonLayer);
	this->addChild(menu, zOrder_CommonNode);
}

void FunctionLayer::menuItemTouched( cocos2d::CCObject* pSender )
{
	CCMenuItem* menuItem = (CCMenuItem*)pSender;
	if (menuItem == m_menuItemNewFile)
	{
		this->buildNewMap();
	}
	else if (menuItem == m_menuItemOpenFile)
	{
		CCPoint posTmp = menuItem->getPosition();
		CCSize sizeTmp = menuItem->getContentSize();
		CCPoint posLT = ccp(posTmp.x - sizeTmp.width*0.5f, posTmp.y - sizeTmp.height*0.5f - 5);
		FunctionFileListLayer* pFileListLayer = FunctionFileListLayer::create(posLT, CCSizeMake(FILE_LIST_WIDTH, FILE_LIST_HEIGHT));
		pFileListLayer->setDelegateLayer(this);
		this->addChild(pFileListLayer, zOrder_CommonNode);
	}
	else if (menuItem == m_menuItemSaveFile)
	{
		if (m_curFileName.empty())
		{
			m_saveFileLayer = FunctionSaveFileLayer::create();
			m_saveFileLayer->setDelegateLayer(this);
			this->addChild(m_saveFileLayer, zOrder_PopLayer);
		}
		else
		{
			this->saveToFile(m_curFileName);
		}
	}
	else if (menuItem == m_menuItemSaveAsFile)
	{
		m_saveFileLayer = FunctionSaveFileLayer::create();
		m_saveFileLayer->setDelegateLayer(this);
		this->addChild(m_saveFileLayer, zOrder_PopLayer);
	}
	else if (menuItem == m_menuItemChangePrecision)
	{
		PrecisionManager::sharedManager()->changePrecision();
	}
}

void FunctionLayer::menuItemToggleTouched( cocos2d::CCObject* pSender )
{
	CCMenuItemToggle* menuItemToggle = (CCMenuItemToggle*)pSender;
	int idx = menuItemToggle->getSelectedIndex();
	if (menuItemToggle == m_menuItemToggleMode)
	{
		//重置地图（删除所有添加精灵，改变拖动方向）
		m_isModeX = !m_isModeX;
		this->buildNewMap();
	}
	else if (menuItemToggle == m_menuItemToggleClear)
	{
		m_isClear = (idx==1);
		m_isDrag = ((m_isClear == true) ? false : m_isDrag);
		m_menuItemToggleDrag->setSelectedIndex((m_isDrag == false) ? (0) : (1));
	}
	else if (menuItemToggle == m_menuItemToggleDrag)
	{
		m_isDrag = (idx==1);
		m_isClear = ((m_isDrag == true) ? false : m_isClear);
		m_menuItemToggleClear->setSelectedIndex((m_isClear == false) ? (0) : (1));
	}

	EditorScene* pEditorScene = EditorScene::getScene();
	pEditorScene->getLayerEditor()->setScrollViewIsCanDrag(m_isDrag);
}

void FunctionLayer::buildNewMap()
{
	m_curFileName = "";
	EditorScene* pEditorScene = EditorScene::getScene();
	pEditorScene->getLayerEditor()->buildNewMap();
}

std::vector<std::string> FunctionLayer::getAllFileName()
{
	std::vector<std::string> vecResourcePath = CCFileUtils::sharedFileUtils()->getSearchPaths();
	std::string strPath = vecResourcePath[0];
	if (m_isModeX)
	{
		strPath += FOLDER_NAME_MODE_X;
	}
	else
	{
		strPath += FOLDER_NAME_MODE_Y;
	}

	std::vector<std::string> vecAllFilePath = CBFolderTool::AllFilePathInFolder(strPath);
	std::vector<std::string> vecAllFileName;
	for (unsigned int i=0; i<vecAllFilePath.size(); i++)
	{
		std::string::size_type startPos = vecAllFilePath[i].find_last_of("\\");
		std::string::size_type endPos = vecAllFilePath[i].find_last_of(".");
		std::string strFileName = vecAllFilePath[i].substr(startPos+1, endPos-(startPos+1));
		vecAllFileName.push_back(strFileName);
	}

	return vecAllFileName;
}

void FunctionLayer::checkSaveFile()
{
	std::string strInputName = m_saveFileLayer->getTextField()->getString();
	if (strInputName.empty())
	{
		return;
	}

	std::vector<std::string> vecAllFileName = this->getAllFileName();

	if(std::find( vecAllFileName.begin(), vecAllFileName.end(), strInputName) != vecAllFileName.end())
	{
		//已存在文件
		if (m_saveFileLayer)
		{
			m_saveFileLayer->setVisible(false);
			WarningLayerSaveFile* pWarningLayer = WarningLayerSaveFile::create(strInputName);
			pWarningLayer->setDelegateLayer(this);
			this->addChild(pWarningLayer, zOrder_PopLayer);
		}
	}
	else
	{
		this->saveToFile(strInputName);
	}
}

void FunctionLayer::saveToFile( std::string strFileName )
{
	std::string fileName = "";
	if (m_isModeX)
	{
		fileName = FOLDER_NAME_MODE_X;
	}
	else
	{
		fileName = FOLDER_NAME_MODE_Y;
	}
	fileName += "/";
	fileName += strFileName;
	fileName += ".csv";

	std::string strFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
	EditorScene* pEditorScene = EditorScene::getScene();
	std::string strCSV = pEditorScene->getLayerEditor()->getEditorInfoStringWithCSV();
	CBFileTool::saveFileToFolder(strCSV.c_str(), strFilePath.c_str());

	if (m_saveFileLayer)
	{
		this->removeChild(m_saveFileLayer);
	}
}

void FunctionLayer::showLayerSaveFile()
{
	if (m_saveFileLayer)
	{
		m_saveFileLayer->setVisible(true);
	}
}

void FunctionLayer::openFile( std::string strFileName )
{
	m_curFileName = strFileName;

	EditorScene* pEditorScene = EditorScene::getScene();
	pEditorScene->getLayerEditor()->resetMapWithFile(strFileName);
}
