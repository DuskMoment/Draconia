#include "InputSystem.h"
#include "InputEvent.h"
#include <EventSystem.h>
#

InputSystem::InputSystem()
{
	
	
}

InputSystem::~InputSystem()
{
	cleanup();
}

bool InputSystem::init(sf::RenderWindow& window)
{
	mpWindow = &window;
	mpWindow->setKeyRepeatEnabled(false);

	return true;
}

void InputSystem::cleanup()
{
	//we dont own it
	mpWindow = nullptr;
}


void InputSystem::update()
{
	
	sf::Event event;

	while (mpWindow->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			InputEvent keyboardEvent(event.key.code, true);
			EventSystem::getInstance()->fireEvent(keyboardEvent);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			InputEvent keyboardEvent(event.key.code, false);

			EventSystem::getInstance()->fireEvent(keyboardEvent);
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			Vector2D loc = Vector2D(event.mouseButton.x, event.mouseButton.y);
			

			InputEvent mouseEvent(loc, event.mouseButton.button, true);

			EventSystem::getInstance()->fireEvent(mouseEvent);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			Vector2D loc = Vector2D(event.mouseButton.x, event.mouseButton.y);

			InputEvent mouseEvent(loc, event.mouseButton.button, false);

			EventSystem::getInstance()->fireEvent(mouseEvent);
		}
	}
	//ALLEGRO_EVENT theEvent;
	//while (al_get_next_event(mpEventQueue, &theEvent))
	//{
	//	if (theEvent.type == ALLEGRO_EVENT_KEY_DOWN)
	//	{
	//		//call event
	//		
	//		InputEvent keyboardEvent(theEvent.keyboard.keycode, true);

	//		EventSystem::getInstance()->fireEvent(keyboardEvent);
	//	}
	//	else if (theEvent.type == ALLEGRO_EVENT_KEY_UP)
	//	{
	//		InputEvent keyboardEvent(theEvent.keyboard.keycode, false);

	//		EventSystem::getInstance()->fireEvent(keyboardEvent);

	//	}
	//	else if (theEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	//	{
	//		//call event
	//		Vector2D loc = Vector2D(theEvent.mouse.x, theEvent.mouse.y);
	//		theEvent.mouse.button;

	//		InputEvent mouseEvent(loc, theEvent.mouse.button, true);

	//		EventSystem::getInstance()->fireEvent(mouseEvent);
	//	}
	//	else if (theEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	//	{
	//		Vector2D loc = Vector2D(theEvent.mouse.x, theEvent.mouse.y);
	//		theEvent.mouse.button;

	//		InputEvent mouseEvent(loc, theEvent.mouse.button, false);

	//		EventSystem::getInstance()->fireEvent(mouseEvent);
	//	}

	//	
	
}
