#include "EditorSprite.h"


EditorSprite::EditorSprite()
	: m_orderForAdd(0)
{

}

EditorSprite::~EditorSprite()
{

}

EditorSprite* EditorSprite::create( SpirteConfig config )
{	
	EditorSprite* pRet = new EditorSprite();
	if (pRet && pRet->initWithConfig(config))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool EditorSprite::initWithConfig( SpirteConfig config )
{
	if (!CBPixelSprite::initWithSpriteFrameName(config.getFrameName().c_str()))
	{
		return false;
	}

	m_spirteConfig = config;

	return true;
}


