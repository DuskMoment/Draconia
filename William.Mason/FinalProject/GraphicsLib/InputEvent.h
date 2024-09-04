#pragma once
#include <Event.h>
#include <Vector2D.h>
#include <allegro5/allegro.h>

enum InputEventType
{
    KEYBOARD_EVENT = NUM_BASE_EVENT_TYPES,
    MOUSES_EVENT,
    NUM_INPUT_EVENT_TYPES,
};

class InputEvent :
    public Event
{
public:
    InputEvent(const Vector2D& loc, const int& key, const bool& isMouseDown);

    InputEvent(const int& key, const bool& isKeyDown);

    inline int getKeycode() const { return mKeyCode; };
    inline bool getKeyDown() const{ return mIsKeyDown; };
    inline bool getIsMouseDown() const { return mIsMouseDown; };
    inline int getMouseCode() const { return mMouseCode; };

    inline Vector2D getMouseLoc() const { return mMouseLoc; };

private:

    int mKeyCode = 0;
    bool mIsKeyDown = false;

    int mMouseCode = 0;
    bool mIsMouseDown = false;

    Vector2D mMouseLoc = ZERO_VECTOR2D;
   
};

