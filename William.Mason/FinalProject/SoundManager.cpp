#include "SoundManager.h"
#include "GameEvent.h"
#include "PlaySoundEvent.h"
#include "ChangePointEvent.h"
#include "PlaySoundEvent.h"
#include <iostream>
#include <EventSystem.h>

SoundManager::~SoundManager()
{
    cleanup();
}

void SoundManager::handleEvent(const Event& theEvent)
{
    if (theEvent.getType() == MUTE_SOUND_EVENT)
    {
        if (mMute)
        {
            std::cout << "UNMUTED" << std::endl;
            mMute = false;
            mpMusic->play();
        }
        else
        {
            std::cout << "MUTED" << std::endl;
            mMute = true;
            mpMusic->pause();
        }
    }
    if (!mMute)
    {
        if (theEvent.getType() == CHANGE_POINT_EVENT)
        {
            const ChangePointEvent& changePoints = static_cast<const ChangePointEvent&>(theEvent);

            std::string sound;


            if (changePoints.getIsNegitive())
            {
                sound = "PointLost";
            }
            else
            {
                sound = "PointCollected";
            }
            //playSound(sound);
        }
        if (theEvent.getType() == GAME_OVER_EVENT)
        {
            playSound("gameOver");
        }
        if (theEvent.getType() == PLAY_SOUND_EVENT)
        {
            const PlaySoundEvent& soundEvent = static_cast<const  PlaySoundEvent&>(theEvent);

            if (soundEvent.getKey() == "music")
            {
                playMusic();
            }
            else
            {
                playSound(soundEvent.getKey());
            }
            
        }

    }
   
}

bool SoundManager::init(int numSamples)
{
    //EventSystem::getInstance()->addListener((EventType)CHANGE_POINT_EVENT, this);
    EventSystem::getInstance()->addListener((EventType)GAME_OVER_EVENT, this);
    EventSystem::getInstance()->addListener((EventType)MUTE_SOUND_EVENT, this);
    EventSystem::getInstance()->addListener((EventType)PLAY_SOUND_EVENT, this);

    mpSound = new sf::Sound();

    return true;
}

void SoundManager::cleanup()
{
    for (auto iter : mMap)
    {
        sf::SoundBuffer* pTarget = iter.second;
        delete pTarget;
    }
    mMap.clear();

    delete mpSound;
    delete mpMusic;
}

void SoundManager::addSound(const SoundKey& key, const std::string& filePath, bool isMusic)
{
    if (!isMusic)
    {
        sf::SoundBuffer* pSample = new sf::SoundBuffer();
        pSample->loadFromFile(filePath);

        auto iter = mMap.find(key);

        if (iter == mMap.end())
        {
            mMap[key] = pSample;
        }
    }
    else
    {
        mMusicFilePath = filePath;
    }
    

}

void SoundManager::removeSound(const SoundKey& key)
{
    auto iter = mMap.find(key);

    if (iter != mMap.end())
    {
        delete iter->second;
        mMap.erase(iter);
    }
}

void SoundManager::playSound(const SoundKey& key)
{
    sf::SoundBuffer* pSample = mMap[key];

    mpSound->setBuffer(*pSample);
    mpSound->play();

}

void SoundManager::playMusic()
{
    if (mpMusic != nullptr)
    {
        delete mpMusic;
    }
    mpMusic = new sf::Music;
    mpMusic->openFromFile(mMusicFilePath);
    mpMusic->setLoop(true);
    mpMusic->play();

   

}

// volume is between 0 and 100
void SoundManager::setMusicVolume(float volume)
{
    assert(mpMusic);

    mpMusic->setVolume(volume);
}

void SoundManager::setSoundVolume(float volume)
{
    mpSound->setVolume(volume);
}



