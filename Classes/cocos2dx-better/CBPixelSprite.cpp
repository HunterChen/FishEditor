#include "CBPixelSprite.h"

using namespace cocos2d;


CBPixelSprite* CBPixelSprite::create()
{
	CBPixelSprite* pRet = new CBPixelSprite();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBPixelSprite* CBPixelSprite::create( const char *pszFileName )
{
	CBPixelSprite* pRet = new CBPixelSprite();
	if (pRet && pRet->initWithFile(pszFileName))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBPixelSprite* CBPixelSprite::create( const char *pszFileName, const CCRect& rect )
{
	CBPixelSprite* pRet = new CBPixelSprite();
	if (pRet && pRet->initWithFile(pszFileName, rect))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBPixelSprite* CBPixelSprite::createWithTexture( CCTexture2D *pTexture )
{
	CBPixelSprite* pRet = new CBPixelSprite();
	if (pRet && pRet->initWithTexture(pTexture))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBPixelSprite* CBPixelSprite::createWithTexture( CCTexture2D *pTexture, const CCRect& rect )
{
	CBPixelSprite* pRet = new CBPixelSprite();
	if (pRet && pRet->initWithTexture(pTexture, rect))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBPixelSprite* CBPixelSprite::createWithSpriteFrame( CCSpriteFrame *pSpriteFrame )
{
	CBPixelSprite* pRet = new CBPixelSprite();
	if (pSpriteFrame && pRet && pRet->initWithSpriteFrame(pSpriteFrame))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBPixelSprite* CBPixelSprite::createWithSpriteFrameName( const char *pszSpriteFrameName )
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

bool CBPixelSprite::isContainPoint( cocos2d::CCPoint worldPoint )
{
	CCPoint pos = this->convertToNodeSpace(worldPoint);
	CCRect rect = this->getTextureRect();
	//防止sprite是用spriteFrameName生成时造成的错误
	rect.origin = CCPointZero;
	if (rect.containsPoint(pos))
	{
		return true;
	}
	return false;
}

bool CBPixelSprite::isTransparentInPoint( cocos2d::CCPoint worldPoint )
{
	if (!isContainPoint(worldPoint))
	{
		return true;
	}

	CCPoint pos = this->convertToNodeSpace(worldPoint);
	CCRect rect = this->getTextureRect();
	int x = pos.x;
	int y = rect.size.height - pos.y;

	CCSprite* spriteTmp = new CCSprite();
	//如果sprite是用spriteFrameName生成时会造成错误
	//spriteTmp->initWithTexture(this->getTexture());
	spriteTmp->initWithSpriteFrame(this->displayFrame());
	spriteTmp->setAnchorPoint(CCPointZero);
	spriteTmp->setPosition(CCPointZero);

	CCRenderTexture* rt = new CCRenderTexture();
	rt->initWithWidthAndHeight((int)rect.size.width, (int)rect.size.height, kCCTexture2DPixelFormat_RGBA8888, 0);
	rt->begin();
	spriteTmp->visit();
	rt->end();

	CCImage* pImage = rt->newCCImage();
	delete spriteTmp;
	delete rt;

	//
	ccColor4B c = {0, 0, 0, 0};
	unsigned char* pData = pImage->getData();
	unsigned int* pixel = (unsigned int*)pData;
	pixel = pixel + y*(int)rect.size.width + x;
	c.r = *pixel & 0xff;
	c.g = (*pixel >> 8) & 0xff;
	c.b = (*pixel >> 16) & 0xff;
	c.a = (*pixel >> 24) & 0xff;
	delete pImage;
	if (c.a == 0)
	{
		return true;
	}
	return false;
}
