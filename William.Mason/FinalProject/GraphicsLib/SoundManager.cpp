#include "SoundManager.h"
#include "GameEvent.h"
#include <EventSystem.h>

SoundManager::~SoundManager()
{
    cleanup();
}

void SoundManager::handleEvent(const Event& theEvent)
{
    if(theEvent.getType() == )
}

bool SoundManager::init(int numSamples)
{
    //EventSystem::getInstance()->addListener()
    return al_install_audio() && al_init_acodec_addon() && al_reserve_samples(numSamples);
}

void SoundManager::cleanup()
{
    for (auto iter : mMap)
    {
        ALLEGRO_SAMPLE* pTarget = iter.second;
        al_destroy_sample(pTarget);
    }
    mMap.clear();
}

void SoundManager::addSound(const SoundKey& key, const std::string& filePath)
{
    ALLEGRO_SAMPLE* pSample = al_load_sample(filePath.c_str());

    auto iter = mMap.find(key);

    if (iter == mMap.end())
    {
        mMap[key] = pSample;
    }
   
}

void SoundManager::removeSound(const SoundKey& key)
{
    auto iter = mMap.find(key);

    if (iter != mMap.end())
    {
        al_destroy_sample(iter->second);
        mMap.erase(iter);
    }
}

void SoundManager::playSound(const SoundKey& key)
{
    ALLEGRO_SAMPLE* pSample = mMap[key];
    ALLEGRO_PLAYMODE playMode = ALLEGRO_PLAYMODE_ONCE;

    al_play_sample(pSample, 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, playMode, nullptr);

}


