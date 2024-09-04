#include "DataReader.h"
#include <string>


DataReader::DataReader(string filePath)
{
	mFilePath = filePath;
}

void DataReader::cleanUp()
{
	mIntDataMap.clear();
}

void DataReader::readFile()
{
	ifstream theStream;
	theStream.open(mFilePath);
	
	
	
	string fileData;
	string data;

	bool isStringData = false;

	while (getline(theStream, fileData))
	{
		DataKey theKey;
		data.clear();

		bool flip = false;

		for (unsigned int i = 0; i < fileData.size(); i++)
		{
			//checks to see if their is a type change
			if (fileData == "STRING")
			{
				isStringData = true;
				break;
			}
			else if (fileData == "STRING_END")
			{
				isStringData = false;
				break;
			}

			//checks to see if we are no longer in the name area
			if (fileData[i] == ':')
			{
				flip = true;
				i++;
			}

			//adds data
			if (flip)
			{
				data += fileData[i];
			}
			else
			{
				theKey += fileData[i];
			}
		}
		//adds it to the correnct map
		if (!isStringData && !theKey.empty())
		{
			auto iter = mIntDataMap.find(theKey);
			if (iter == mIntDataMap.end())
			{

				mIntDataMap[theKey] = stoi(data);
			}
		}
		else
		{
			auto iter = mStringDataMap.find(theKey);
			if (iter == mStringDataMap.end())
			{

				mStringDataMap[theKey] = data;
			}
		}


	}
}

void DataReader::readFile(string filePath)
{
	ifstream theStream;
	theStream.open(filePath);

	DataKey theKey;
	string fileData;
	string data;

	bool isStringData = false;

	while (getline(theStream, fileData))
	{
		bool flip = false;

		for (unsigned int i = 0; i < fileData.size(); i++)
		{
			//checks to see if their is a type change
			if (fileData == "STRING")
			{
				isStringData = true;
			}
			else if (fileData == "STRING_END")
			{
				isStringData = false;
			}

			//checks to see if we are no longer in the name area
			if (fileData[i] == ':')
			{
				flip = true;
				i++;
			}

			//adds data
			if (flip)
			{
				data += fileData[i];
			}
			else
			{
				theKey += fileData[i];
			}
		}
		//adds it to the correnct map
		if (isStringData)
		{
			auto iter = mIntDataMap.find(theKey);
			if (iter == mIntDataMap.end())
			{

				mIntDataMap[theKey] = stoi(data);
			}
		}
		else
		{
			auto iter = mStringDataMap.find(theKey);
			if (iter == mStringDataMap.end())
			{

				mStringDataMap[theKey] = data;
			}
		}
		

	}
}

int DataReader::findIntDataByKey(DataKey key) const
{
	auto iter = mIntDataMap.find(key);

	if (iter != mIntDataMap.end())
	{
		return iter->second;
	}
	else
	{
		//bad! data not in map
		return -1;
	}
}

string DataReader::findStringDataByKey(DataKey key) const
{
	auto iter = mStringDataMap.find(key);

	if (iter != mStringDataMap.end())
	{
		return iter->second;
	}
	else
	{
		//bad! data not in map
		return "BAD!";
	}
	return 0;
}
