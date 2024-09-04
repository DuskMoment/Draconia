#pragma once
#include <iostream>
#include <fstream>
#include <Trackable.h>
#include <unordered_map>

using namespace std;
typedef std::string DataKey;

class DataReader : public Trackable
{
public:
	DataReader(string filePath);

	void cleanUp();

	void readFile();
	void readFile(string filePath);
	
	int findIntDataByKey(DataKey key) const;
	string findStringDataByKey(DataKey key) const;

private:
	string mFilePath;

	unordered_map<DataKey, int> mIntDataMap;
	unordered_map<DataKey, string> mStringDataMap;

	
};

