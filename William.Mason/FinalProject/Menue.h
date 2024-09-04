#pragma once
#include <Trackable.h>
#include <GraphicsBufferManager.h>
#include <GraphicsSystem.h>
#include <Eventlistener.h>
#include <EventSystem.h>
#include <Color.h>
#include <Font.h>

class DataReader;

class Menue : public EventListener
{
public:
	Menue(GraphicsBufferManager * bufferManager, const DataReader* dataReader);
	~Menue();

	void init(int width, int height);
	void cleanUp();
	void handleEvent(const Event& theEvent);

	void createMainMenue();
	void createSettings();

	void clearBuffer();
	void draw();

	bool getIsActive() { return mIsActive; };


private:
	GraphicsBufferManager* mpBufferManger;
	const DataReader* mpDataReader;

	Font* mpFont;
	Color* mpColor;

	bool mMenueActive = true;
	bool mSettingMenueActive = false;
	bool mIsActive;

	int mLanguage;
	
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 20; // used to be 48
};

