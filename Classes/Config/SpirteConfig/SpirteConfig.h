#pragma once

#include "../../Common/Macro.h"
#include "../../Common/StringModifier.hpp"
#include <string>

class SpirteConfigCache;

class SpirteConfig
{
public:

	friend class SpirteConfigCache;

	SpirteConfig()
		: _ID(0)
		, _frameName("")
		, _typeName("")
	{

	}
	virtual ~SpirteConfig()
	{

	}

	SYNTHESIZE_READONLY(int, _ID, ID);
	SYNTHESIZE_READONLY(std::string, _frameName, FrameName);
	SYNTHESIZE_READONLY(std::string, _typeName, TypeName);
};
