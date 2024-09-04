#include "InputEvent.h"

InputEvent::InputEvent(const Vector2D& loc, const int& key, const bool& isMouseDown)
	:Event((EventType)MOUSES_EVENT), mMouseCode(key), mMouseLoc(loc), mIsMouseDown(isMouseDown)
{

}

InputEvent::InputEvent(const int& key, const bool& isKeyDown)
	:Event((EventType)KEYBOARD_EVENT), mKeyCode(key), mIsKeyDown(isKeyDown)
{
}
