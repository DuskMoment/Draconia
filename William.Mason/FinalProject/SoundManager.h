#pragma once
#include <EventListener.h>
#include <unordered_map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <sfml/audio.hpp>

#include <Trackable.h>

typedef std::string SoundKey;

class SoundManager : public EventListener
{
public:
	SoundManager() {};
	~SoundManager();

	void handleEvent(const Event& theEvent);

	bool init(int numSamples);
	void cleanup();

	void addSound(const SoundKey& key, const std::string& filePath, bool isMusic = false);
	void removeSound(const SoundKey& key);
	void playSound(const SoundKey& key);
	void playMusic();

	void setMusicVolume(float volume);
	void setSoundVolume(float volume);

	bool getMute() { return mMute; };
	void setMute(bool con) { mMute = con; };

private:
	std::unordered_map<SoundKey, sf::SoundBuffer*> mMap;
	sf::Sound* mpSound = nullptr;
	sf::Music* mpMusic = nullptr;
	std::string mMusicFilePath;
	bool mMute = false;

};

