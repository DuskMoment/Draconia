#include "InputTranslator.h"
#include <InputSystem.h>
#include <EventSystem.h>
#include <InputEvent.h>
#include <iostream>
#include <Vector2D.h>

#include "QuitGame.h"
#include "SwitchAnimationEvent.h"
#include "PauseAllAnimations.h"
#include "UnitChangeEvent.h"
#include "PlaySoundEvent.h"
#include "PauseGameEvent.h"
#include "GameOverEvent.h"
#include "RestartGameEvent.h"
#include "PlayerDirectionEvent.h"
#include "ChangeLanguageEvent.h"
#include "SwitchMenueEvent.h"
#include "DiffucltyChangeEvent.h"
#include "LoadFromSaveEvent.h"
#include "MuteSoundEvent.h"

InputTranslator::InputTranslator()
{
	EventSystem::getInstance()->addListener((EventType)KEYBOARD_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)MOUSES_EVENT, this);

	mLanguage = 0;
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == KEYBOARD_EVENT)
	{
		const InputEvent& keyboardEvent = static_cast<const InputEvent&>(theEvent);
		EventSystem* pEventSystem = EventSystem::getInstance();

		int key = keyboardEvent.getKeycode();
		bool isDown = keyboardEvent.getKeyDown();
		//escape key
		if (key == ESCAPE_KEY && isDown)
		{
			//exit game event
			QuitGame pause;
			pEventSystem->fireEvent(pause);
			

		}
		//enter key
		//else if (key == ENTER_KEY && isDown)
		//{
		//	//switch sprite
		//	GameOverEvent gameOver;
		//	pEventSystem->fireEvent(gameOver);

		//}
		else if (key == SPACE_BAR && isDown)
		{
			PauseGameEvent pauseEvent(false);
			pEventSystem->fireEvent(pauseEvent);
		}
		//space key
		else if (key == SPACE_BAR && isDown)
		{
			bool keyDown = keyboardEvent.getKeyDown();

			//pause animation
			PauseAllAnimations pauseEvent(keyDown);

			pEventSystem->fireEvent(pauseEvent);

		}
		else if (key == F_KEY && isDown)
		{
			RestartGameEvent restart;

			pEventSystem->fireEvent(restart);

		}
		else if (key == W_KEY)
		{
			//cout << "W " + std::string(isDown ? "Down!" : "Up!") << endl;

			PlayerDirectionEvent direction(Up, isDown);

			pEventSystem->fireEvent(direction);

		}
		else if (key == A_KEY)
		{
			//cout << "A " + std::string(isDown ? "Down!" : "Up!") << endl;
			Vector2D vec;

			PlayerDirectionEvent direction(Left, isDown);

			pEventSystem->fireEvent(direction);

		}
		else if (key == S_KEY)
		{
			//cout << "S " + std::string(isDown ? "Down!" : "Up!") << endl;
			PlayerDirectionEvent direction(Down, isDown);

			pEventSystem->fireEvent(direction);

		}
		else if (key == D_KEY)
		{
			//cout << "D " + std::string(isDown ? "Down!" : "Up!") << endl;
			PlayerDirectionEvent direction(Right, isDown);

			pEventSystem->fireEvent(direction);
		}
		else if (key == L_KEY && isDown)
		{
			mLanguage++;
			if (mLanguage >= MAX_LANGUAGES)
			{
				mLanguage = 0;
			}
			ChangeLanguageEvent lang(mLanguage);

			pEventSystem->fireEvent(lang);

		}
		else if ((key == ONE_KEY || key == ONE_NUMPAD) && isDown)
		{
			DiffucltyChangeEvent diff(1);
			pEventSystem->fireEvent(diff);
		}
		else if ((key == TWO_KEY || key == TWO_NUMPAD) && isDown)
		{
			DiffucltyChangeEvent diff(2);
			pEventSystem->fireEvent(diff);
		}
		else if ((key == THREE_KEY || key == THREE_NUMPAD) && isDown)
		{
			DiffucltyChangeEvent diff(3);
			pEventSystem->fireEvent(diff);
		}
		else if(key == G_KEY && isDown)
		{
			LoadFromSaveEvent event;
			pEventSystem->fireEvent(event);

		}
		else if (key == M_KEY && isDown)
		{
			MuteSoundEvent mute;
			pEventSystem->fireEvent(mute);

		}
		
	}
	else if (theEvent.getType() == MOUSES_EVENT)
	{
		
		const InputEvent& mouseEvent = static_cast<const InputEvent&>(theEvent);
		EventSystem* pEventSystem = EventSystem::getInstance();

		//left click
		int mouseButton = mouseEvent.getMouseCode();
		bool isDown = mouseEvent.getIsMouseDown();
		Vector2D loc = mouseEvent.getMouseLoc();

		//cout << "Mouse event! Button is " << mouseButton << endl;

		if (mouseButton == LEFT_CLICK)
		{
			//if (isDown)
			//{
			//	UnitChangeEvent change(false, loc);

			//	pEventSystem->fireEvent(change);
			//}

			PlayerDirectionEvent direction(Shoot, isDown);

			pEventSystem->fireEvent(direction);

			SwitchMenueEvent menue(false);
			if (isDown)
			{
				pEventSystem->fireEvent(menue);
			}
			
		}
		else if (mouseButton == RIGHT_CLICK && isDown)
		{
			UnitChangeEvent change(true, loc);

			pEventSystem->fireEvent(change);
			//destory unit at location

			SwitchMenueEvent menue(true);
			if (isDown)
			{
				pEventSystem->fireEvent(menue);
			}

		}
	}
}
