#pragma once
#include <Trackable.h>
#include <unordered_map>
#include <string>



typedef std::string BufferKey;

class GraphicsBuffer;
class Color;

class GraphicsBufferManager: public Trackable
{
public:
	GraphicsBufferManager() {};
	~GraphicsBufferManager();

	void cleanUp();

	GraphicsBuffer* createBuffer(const BufferKey& key, const std::string& filePath);
	GraphicsBuffer* createBuffer(const BufferKey& key, unsigned int width, unsigned int height, Color color);

	void deleteBuffer(const BufferKey& key);
	void deleteBuffer(GraphicsBuffer* pBuffer);

	GraphicsBuffer* getBuffer(const BufferKey& key);
	

private:
	std::unordered_map<BufferKey, GraphicsBuffer*>	mMap;

	
};

