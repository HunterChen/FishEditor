#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>


class SpriteListLayer;
class AdjustLayer;
class FunctionLayer;
class EditorSprite;

class EditorLayer : public cocos2d::CCLayerColor, public cocos2d::extension::CCScrollViewDelegate
{
public:
	EditorLayer();
	virtual ~EditorLayer();

	CREATE_FUNC(EditorLayer);
	virtual bool init();
	virtual void draw();
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
    virtual void onExit();

	void initScrollView();
	void setScrollViewIsCanDrag(bool isCanDrag);
	std::string getEditorInfoStringWithCSV();

	void resetMapWithFile(std::string fileName);
	void buildNewMap();

private:

	EditorSprite* findTouchSprite(cocos2d::CCTouch *pTouch);
	cocos2d::CCPoint adjustIndexForTouch(cocos2d::CCTouch *pTouch);
	cocos2d::CCPoint adjustPositionForIndex(cocos2d::CCPoint index);
	cocos2d::CCPoint adjustPositionForTouch(cocos2d::CCTouch *pTouch);

	bool checkSpriteIsOutEditorRect(EditorSprite* sprite, cocos2d::CCTouch *pTouch);
	void removeSprite(EditorSprite* sprite);

	void removeSpriteInTouch(cocos2d::CCTouch *pTouch);
	void resetSpritePositionInTouch(cocos2d::CCTouch *pTouch);

public:

	CC_SYNTHESIZE_READONLY(FunctionLayer*, m_layerFunction, LayerFunction);
	CC_SYNTHESIZE_READONLY(SpriteListLayer*, m_layerSpriteList, LayerSpriteList);
	CC_SYNTHESIZE_READONLY(cocos2d::extension::CCScrollView*, m_scrollView, ViewScroll);
	CC_SYNTHESIZE_READONLY(cocos2d::CCLayer*, m_containerLayer, LayerContainer);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteBatchNode*, m_batchNode, BatchNode);
	CC_SYNTHESIZE_READONLY(AdjustLayer*, m_adjustLayer, LayerAdjust);

	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_arraySprite, ArraySprite);
	CC_SYNTHESIZE_READONLY(EditorSprite*, m_curTouchSprite, CurTouchSprite);
};


class EditorScene : public cocos2d::CCScene
{
public:
	EditorScene();
	virtual ~EditorScene();

	static EditorScene* getScene();

	void startEditor();

public:

	CC_SYNTHESIZE_READONLY(EditorLayer*, m_LayerEditor, LayerEditor);
};







