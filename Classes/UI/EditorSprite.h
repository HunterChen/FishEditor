#pragma once

#include "../cocos2dx-better/CBPixelSprite.h"
#include "../Config/SpirteConfig/SpirteConfig.h"

class EditorSprite : public CBPixelSprite
{
public:
	EditorSprite();
	virtual ~EditorSprite();

	static EditorSprite* create(SpirteConfig config);
	bool initWithConfig(SpirteConfig config);

	CC_SYNTHESIZE_READONLY(SpirteConfig, m_spirteConfig, ConfigSpirte);
	CC_SYNTHESIZE(int, m_orderForAdd, OrderForAdd);
};
