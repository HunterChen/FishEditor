#include "SpirteConfigCache.h"
#include "../../Tool/csv_parser/CCSVParse.h"
#include "../../cocos2dx-better/CBFileTool.h"

enum
{
	INDEX_ID = 0,
	INDEX_FRAME_NAME,
	INDEX_TYPE_NAME,
	INDEX_MAX
};

bool SpirteConfigCache::loadConfigFromCsvFile( const char* fileName )
{
	std::string strFilePath = CBFileTool::getFullPath(fileName);
	std::string strFileData = CBFileTool::getFileData(strFilePath.c_str());

	CCSVParse* csvParse = new CCSVParse();
	if (!(csvParse->Parse(strFileData)))
	{
		delete csvParse;
		return false;
	}

	int cols = csvParse->getCols();
	int rows = csvParse->getRows();
	if (cols < INDEX_MAX)
	{
		delete csvParse;
		return false;
	}

	for (int i=0; i<rows; i++)
	{
		SpirteConfig config;

		config._ID = atoi(csvParse->getData(i, INDEX_ID));
		config._frameName = csvParse->getData(i, INDEX_FRAME_NAME);
		config._typeName = csvParse->getData(i, INDEX_TYPE_NAME);

		this->addData(config);
	}

	delete csvParse;
	return true;
}

std::vector<SpirteConfig> SpirteConfigCache::getAllSpriteConfig()
{
	return _data;
}

SpirteConfig SpirteConfigCache::getSpirteConfigByType( std::string strType )
{
	SpirteConfig config;

	for (unsigned int i=0; i<_data.size(); i++)
	{
		if (_data[i]._typeName == strType)
		{
			config = _data[i];
			break;
		}
	}

	return config;
}
