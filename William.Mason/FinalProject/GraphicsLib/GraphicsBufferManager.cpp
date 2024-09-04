#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"
#include "Color.h"

GraphicsBufferManager::~GraphicsBufferManager()
{
    cleanUp();
}

void GraphicsBufferManager::cleanUp()
{
    for (auto iter : mMap)
    {
        GraphicsBuffer* pTarget = iter.second;
        delete pTarget;
    }
    mMap.clear();
}

GraphicsBuffer* GraphicsBufferManager::createBuffer(const BufferKey& key, const std::string& filePath)
{
    GraphicsBuffer* pNewBuffer = nullptr;
    auto iter = mMap.find(key);

    if (iter == mMap.end())
    {
        pNewBuffer = new GraphicsBuffer(filePath);
        mMap[key] = pNewBuffer;
    }

    return pNewBuffer;
}

GraphicsBuffer* GraphicsBufferManager::createBuffer(const BufferKey& key, unsigned int width, unsigned int height, Color color)
{
    GraphicsBuffer* pNewBuffer = nullptr;
    auto iter = mMap.find(key);

    if (iter == mMap.end())
    {
        pNewBuffer = new GraphicsBuffer(width, height, color);
        mMap[key] = pNewBuffer;
    }

    return pNewBuffer;
}

void GraphicsBufferManager::deleteBuffer(const BufferKey& key)
{
    auto iter = mMap.find(key);

    if (iter != mMap.end())
    {
        delete iter->second;
        mMap.erase(iter);
    }
}

void GraphicsBufferManager::deleteBuffer(GraphicsBuffer* pBuffer)
{
    for (auto iter : mMap)
    {
        if (pBuffer == iter.second)
        {
            delete pBuffer;
            mMap.erase(iter.first);
            return;
        }
    }
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(const BufferKey& key)
{
    auto iter = mMap.find(key);

    if (iter != mMap.end())
    {
        return iter->second;
    }
    else
    {
        return nullptr;
    }
  
}
