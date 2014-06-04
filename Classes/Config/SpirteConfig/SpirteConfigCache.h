#pragma once

#include "SpirteConfig.h"
#include "../CsvVecReader.hpp"

class SpirteConfigCache
	: public CsvVecReader<SpirteConfig>
{
public:

	SINGLETON(SpirteConfigCache, sharedCache);

	virtual bool loadConfigFromCsvFile(const char* fileName);

	std::vector<SpirteConfig> getAllSpriteConfig();

	SpirteConfig getSpirteConfigByType(std::string strType);
};