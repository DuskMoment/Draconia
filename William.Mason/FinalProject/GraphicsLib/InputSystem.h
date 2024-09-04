#pragma once


#include <Vector2D.h>
#include <Trackable.h>
#include <iostream>
#include <Event.h>
#include <SFML/Graphics.hpp>

enum KeyCodes
{
	ESCAPE_KEY = sf::Keyboard::Escape,
	F_KEY = sf::Keyboard::F,
	M_KEY = sf::Keyboard::M,
	W_KEY = sf::Keyboard::W,
	A_KEY = sf::Keyboard::A,
	S_KEY = sf::Keyboard::S,
	D_KEY = sf::Keyboard::D,
	L_KEY = sf::Keyboard::L,
	ONE_KEY = sf::Keyboard::Num1,
	ONE_NUMPAD = sf::Keyboard::Numpad1,
	TWO_KEY = sf::Keyboard::Num2,
	TWO_NUMPAD = sf::Keyboard::Numpad2,
	THREE_KEY = sf::Keyboard::Num3,
	THREE_NUMPAD = sf::Keyboard::Numpad3,
	ENTER_KEY = sf::Keyboard::Enter,
	SPACE_BAR = sf::Keyboard::Space,
	G_KEY = sf::Keyboard::G,
	//temp
	DOWN_ARROW = sf::Keyboard::Down
};

enum MouseButtons
{
	LEFT_CLICK = 0,
	RIGHT_CLICK = 1
};

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	bool init(sf::RenderWindow& window);
	void cleanup();

	void update();

	
	
private:


	sf::RenderWindow* mpWindow;
	bool mKeyPress;
	//any other data here
};
