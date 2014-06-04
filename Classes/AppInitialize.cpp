#include "AppInitialize.h"
#include "Config/SpirteConfig/SpirteConfigCache.h"
#include "cocos2d.h"


void AppInitialize::LoadResource()
{
	SpirteConfigCache::sharedCache()->loadConfigFromCsvFile("Resource/config.csv");

	cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Resource/sprite.plist");
}
