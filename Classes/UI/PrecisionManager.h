#pragma once

#include "../Common/Macro.h"

class PrecisionManager
{
public:

	SINGLETON(PrecisionManager, sharedManager);

	void changePrecision();

	int getCurPrecision();

private:
	PrecisionManager();

	virtual ~PrecisionManager();

private:
	int m_indexPrecision;
};