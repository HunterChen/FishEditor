#pragma once

#include <vector>

template <typename T>
class CsvVecReader
{
public:
	CsvVecReader()
	{

	}

	virtual ~CsvVecReader()
	{
		clearData();
	}

	void addData(T data)
	{
		_data.push_back(data);
	}

	void clearData()
	{
		_data.clear();
	}

	virtual bool loadConfigFromCsvFile(const char* fileName) = 0;

protected:

	std::vector<T> _data;
};
