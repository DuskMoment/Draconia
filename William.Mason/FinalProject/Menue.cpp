#include "Menue.h"
#include "ChangeLanguageEvent.h"
#include "SwitchMenueEvent.h"
#include "DiffucltyChangeEvent.h"
#include <GraphicsBuffer.h>
#include "DataReader.h"
#include "Game.h"

Menue::Menue(GraphicsBufferManager* bufferManager, const DataReader* dataReader)
{
	mpBufferManger = bufferManager;
	mpDataReader = dataReader;
	mIsActive = true;


}

Menue::~Menue()
{
	cleanUp();
}

void Menue::init(int width, int height)
{
	mpBufferManger->createBuffer("Menue", width, height, Color(0, 0, 0, 0));

	mpFont = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE);
	//white
	mpColor = new Color(1.0f, 1.0f, 1.0f);

	EventSystem::getInstance()->addListener((EventType)CHANGE_LANGUAGE_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)SWITCH_MENUE_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)DIFFICULTY_CHANGE_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)LOAD_FROM_SAVE_EVENT, this);

}

void Menue::cleanUp()
{
	mpBufferManger = nullptr;

	delete mpFont;
	delete mpColor;
}

void Menue::handleEvent(const Event& theEvent)
{
	if (mIsActive)
	{
		if (theEvent.getType() == CHANGE_LANGUAGE_EVENT && mSettingMenueActive)
		{
			const ChangeLanguageEvent& newLang = static_cast<const ChangeLanguageEvent&>(theEvent);

			std::cout << "change language event" << std::endl;
			mLanguage = newLang.getLanguage();
		}
		else if (theEvent.getType() == SWITCH_MENUE_EVENT)
		{
			const SwitchMenueEvent& switchMenu = static_cast<const SwitchMenueEvent&>(theEvent);
			std::cout << "Switch Menue Event" << std::endl;

			if (switchMenu.getIsRight())
			{
				if (mMenueActive)
				{
					mMenueActive = false;
					mSettingMenueActive = true;
				}
				else if (mSettingMenueActive)
				{
					mSettingMenueActive = false;
					mMenueActive = true;
				}
			}
			else if (!switchMenu.getIsRight())
			{
				mIsActive = false;
				//Game::getInstance()->startNewGame();
			}

		}
		else if (theEvent.getType() == DIFFICULTY_CHANGE_EVENT && mSettingMenueActive)
		{
			const DiffucltyChangeEvent& event = static_cast<const DiffucltyChangeEvent&>(theEvent);
			std::cout << "Diffuculty Change " << event.getDifficulty() << std::endl;
		}
		else if (theEvent.getType() == LOAD_FROM_SAVE_EVENT && mMenueActive)
		{
			std::cout << "received envent" << std::endl;
			mIsActive = false;
			
			Game::getInstance()->resetGame(true);
			Game::getInstance()->loadGame();
		}
	}
	
}

void Menue::createMainMenue()
{
	string langStr = std::to_string(mLanguage);

	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 150), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "Welcome"));
	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 300), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "Left"));
	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 450), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "Right"));
	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 350), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "PressG"));
	mMenueActive = true;
}

void Menue::createSettings()
{
	string langStr = std::to_string(mLanguage);

	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(280, 150), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "Settings"));
	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 350), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "PressM"));
	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 300), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "PressL"));
	mpBufferManger->getBuffer("Menue")->writeText(Vector2D(100, 400), *mpFont, *mpColor, mpDataReader->findStringDataByKey(langStr + "SelectDifficulty"));
	mSettingMenueActive = true;
}


void Menue::clearBuffer()
{
	mpBufferManger->getBuffer("Menue")->setToColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
}

void Menue::draw()
{
	clearBuffer();
	if (mMenueActive)
	{
		createMainMenue();
	}
	else if (mSettingMenueActive)
	{
		createSettings();
	}

	GraphicsSystem::getBackBuffer()->draw(Vector2D(0, 0), *mpBufferManger->getBuffer("Menue"), 1.0f);
}