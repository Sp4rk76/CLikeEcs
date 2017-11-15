//
// Created by Sp4rk on 13-11-17.
//

#include <managers/Input.h>

Input::Input()
{
    x_ = 0;
    y_ = 0;
    xRel_ = 0;
    yRel_ = 0;
    quit_ = false;

    resetKeys();
}

Input::~Input()
{
    resetKeys();
}

void Input::handleEvents()
{
    // (Re-)init relative positions
    xRel_ = 0;
    yRel_ = 0;

    while (SDL_PollEvent(&event_))
    {
        if (event_.type == SDL_KEYDOWN)
        {
            keyboardKeys_[event_.key.keysym.scancode] = true;
        } else if (event_.type == SDL_KEYUP)
        {
            keyboardKeys_[event_.key.keysym.scancode] = false;
        } else if (event_.type == SDL_MOUSEBUTTONDOWN)
        {
            mouseKeys_[event_.button.button] = true;
        } else if (event_.type == SDL_MOUSEBUTTONUP)
        {
            mouseKeys_[event_.button.button] = false;
        } else if (event_.type == SDL_MOUSEMOTION)
        {
            x_ = event_.motion.x;
            y_ = event_.motion.y;
            xRel_ = event_.motion.xrel;
            yRel_ = event_.motion.yrel;
        } else if (event_.type == SDL_WINDOWEVENT)
        {
            if (event_.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                quit_ = true;
            }
        }
    }
}

bool Input::getKey(const SDL_Scancode key) const
{
    return keyboardKeys_[key];
}

bool Input::getMouseKey(const Uint8 key) const
{
    return mouseKeys_[key];
}

bool Input::mouseMovement() const
{
    return !(xRel_ == 0 && yRel_ == 0);
}

void Input::displayCursor(bool display) const
{
    if (display)
    {
        SDL_ShowCursor(SDL_ENABLE);
    } else
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
}

void Input::captureCursor(bool capture) const
{
    if (capture)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    } else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

bool Input::quit() const
{
    return quit_;
}

void Input::resetKeys()
{
    // Init keyboard keys
    for (int key_id = 0; key_id < SDL_NUM_SCANCODES; ++key_id)
    {
        keyboardKeys_[key_id] = false;
    }

    // Init mouse keys
    for (int key_id = 0; key_id < NUM_MOUSE_KEYS; ++key_id)
    {
        mouseKeys_[key_id] = false;
    }
}

int Input::x() const
{
    return x_;
}

int Input::y() const
{
    return y_;
}

int Input::xRel() const
{
    return xRel_;
}

int Input::yRel() const
{
    return yRel_;
}

void Input::setX(int x)
{
    x_ = x;
}

void Input::setY(int y)
{
    y_ = y;
}

void Input::setXRel(int xRel)
{
    xRel_ = xRel;
}

void Input::setYRel(int yRel)
{
    yRel_ = yRel;
}


