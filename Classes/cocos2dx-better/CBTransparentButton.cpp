#include "CBTransparentButton.h"

using namespace cocos2d;
using namespace cocos2d::extension;


CBTransparentButton::CBTransparentButton()
	: m_image(NULL)
	, m_imageSize(CCSizeZero)
{

}

CBTransparentButton::~CBTransparentButton()
{
	CC_SAFE_DELETE(m_image);
}

CBTransparentButton* CBTransparentButton::createWithFile( const char* fileName )
{
	CCSprite* pSprite = CCSprite::create(fileName);
	CCSize sizeTmp = pSprite->getContentSize();

	CCScale9Sprite* pScale9Sprite = CCScale9Sprite::create(fileName);
	pScale9Sprite->setPreferredSize(sizeTmp);
	CBTransparentButton* pButton = new CBTransparentButton();
	if (pButton && pButton->initWithBackgroundSprite(pScale9Sprite))
	{
		pButton->m_imageSize = sizeTmp;
		pButton->m_image = new CCImage();
		pButton->m_image->initWithImageFileThreadSafe(fileName);
		pButton->setPreferredSize(sizeTmp);

		pButton->autorelease();
		return pButton;
	}
	CC_SAFE_DELETE(pButton);
	return NULL;
}

CBTransparentButton* CBTransparentButton::createWithSpriteFrameName( const char* frameName )
{
	CCSprite* pSprite = new CCSprite();
	pSprite->initWithSpriteFrameName(frameName);
	pSprite->setAnchorPoint(CCPointZero);
	pSprite->setPosition(CCPointZero);
	CCSize sizeTmp = pSprite->getContentSize();

	CCRenderTexture* rt = new CCRenderTexture();
	rt->initWithWidthAndHeight((int)sizeTmp.width, (int)sizeTmp.height, kCCTexture2DPixelFormat_RGBA8888, 0);
	rt->begin();
	pSprite->visit();
	rt->end();
	delete pSprite;

	CCScale9Sprite* pScale9Sprite = CCScale9Sprite::createWithSpriteFrameName(frameName);
	pScale9Sprite->setPreferredSize(sizeTmp);
	CBTransparentButton *pButton = new CBTransparentButton();
	if (pButton && pButton->initWithBackgroundSprite(pScale9Sprite))
	{
		pButton->m_imageSize = sizeTmp;
		pButton->m_image = rt->newCCImage();
		pButton->setPreferredSize(sizeTmp);
		pButton->autorelease();
		CC_SAFE_DELETE(rt);
		return pButton;
	}
	CC_SAFE_DELETE(rt);
	CC_SAFE_DELETE(pButton);
	return NULL;
}

bool CBTransparentButton::isTouchInside( cocos2d::CCTouch* touch )
{
	bool ret = CCControl::isTouchInside(touch);
	if (ret)
	{
		return isTouchInOpaqueRect(touch);
	}
	return false;
}

bool CBTransparentButton::isTouchInOpaqueRect( cocos2d::CCTouch* pTouch )
{
	CCPoint pos = this->convertTouchToNodeSpace(pTouch);
	int x = pos.x;
	int y = m_imageSize.height-pos.y;

	ccColor4B c = {0, 0, 0, 0};
	unsigned char* pData = m_image->getData();
	unsigned int* pixel = (unsigned int*)pData;
	pixel = pixel + y*(int)m_imageSize.width + x;
	c.r = *pixel & 0xff; 
	c.g = (*pixel >> 8) & 0xff;
	c.b = (*pixel >> 16) & 0xff;
	c.a = (*pixel >> 24) & 0xff;
	if (c.a == 0)
	{
		return false;
	}
	return true;
}
