#include "AdjustLayer.h"
#include "ViewDefine.h"
#include "PrecisionManager.h"

using namespace cocos2d;


bool AdjustLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setContentSize(CCSizeMake(WIDTH_SCROLL_VIEW, HEIGHT_SCROLL_VIEW));
	return true;
}

void AdjustLayer::draw()
{
	CCLayer::draw();

	glLineWidth(1);
	ccDrawColor4B(0,0,0,50);

	int precision = PrecisionManager::sharedManager()->getCurPrecision();
	for (int x=0; x<=WIDTH_SCROLL_VIEW/precision; x++)
	{
		ccDrawLine(ccp(x*precision, 0), ccp(x*precision, HEIGHT_SCROLL_VIEW));
	}
	for (int y=0; y<=HEIGHT_SCROLL_VIEW/precision; y++)
	{
		ccDrawLine(ccp(0, y*precision), ccp(WIDTH_SCROLL_VIEW, y*precision));
	}

	//restore original values
	glLineWidth(1);
	ccDrawColor4B(255,255,255,255);
	ccPointSize(1);
}

