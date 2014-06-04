#pragma once

#include "cocos2d.h"


class AdjustLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(AdjustLayer);

	virtual void draw();
};