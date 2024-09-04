#pragma once
#include <EventListener.h>
#include <unordered_map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

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

	void addSound(const SoundKey& key, const std::string& filePath);
	void removeSound(const SoundKey& key);
	void playSound(const SoundKey& key);

private:
	std::unordered_map<SoundKey, ALLEGRO_SAMPLE*> mMap;

};

