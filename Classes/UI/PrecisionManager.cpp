#include "PrecisionManager.h"


enum
{
	PRECISION_1 = 0,
	PRECISION_2,
	PRECISION_3,
	PRECISION_4,
	PRECISION_5,
	PRECISION_6,
	PRECISION_7,
	PRECISION_8,
	PRECISION_9,
	PRECISION_MAX
};

const int PRECISION_ARRAY[PRECISION_MAX] = {4, 8, 10, 16, 20, 32, 40, 80, 160};


PrecisionManager::PrecisionManager()
	: m_indexPrecision(PRECISION_1)
{
	
}

PrecisionManager::~PrecisionManager()
{

}

void PrecisionManager::changePrecision()
{
	m_indexPrecision += 1;
	if (m_indexPrecision >= PRECISION_MAX)
	{
		m_indexPrecision = PRECISION_1;
	}
}

int PrecisionManager::getCurPrecision()
{
	return PRECISION_ARRAY[m_indexPrecision];
}