#pragma once

#include <map>
#include "../Common/Macro.h"

template <typename KeyType, typename DataType>

class CsvMapReader
{
public:

	CsvMapReader()
	{

	}

	virtual ~CsvMapReader()
	{
		clearConfig();
	}

	virtual DataType* getConfigByKey(const KeyType& aId) const
	{
		typename std::map<KeyType, DataType*>::const_iterator itr = _config.find(aId);
		if (itr == _config.end())
		{
			return NULL;
		}
		else
		{
			return itr->second;
		}
	}

	virtual void addConfig(const KeyType& aId, DataType *aData)
	{
		_config[aId] = aData;
	}

	void clearConfig()
	{
		for (typename std::map<KeyType, DataType*>::iterator itr = _config.begin(); itr != _config.end(); ++itr)
		{
			DataType *data = itr->second;
			SAFE_DELETE(data);
		}

		_config.clear();
	}

	int getConfigRecordCount() const
	{
		return _config.size();
	}

	virtual bool loadConfigFromCsvFile(const char* fileName) = 0;

protected:

	std::map<KeyType, DataType*> _config;
};