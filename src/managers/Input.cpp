//
// Created by Sp4rk on 13-11-17.
//

#include <managers/Input.h>

Input::Input()
{
    mouseX_ = 0;
    mouseY_ = 0;
    pointerRelativeX_ = 0;
    pointerRelativeY_ = 0;
    quit_ = false;

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

Input::~Input()
{

}

void Input::handleEvents()
{
    // (Re-)init relative positions
    pointerRelativeX_ = 0;
    pointerRelativeY_ = 0;

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
            mouseKeys_[event_.key.keysym.scancode] = true;
        } else if (event_.type == SDL_MOUSEBUTTONUP)
        {
            mouseKeys_[event_.key.keysym.scancode] = false;
        } else if (event_.type == SDL_MOUSEMOTION)
        {
            mouseX_ = event_.motion.x;
            mouseY_ = event_.motion.y;
            pointerRelativeX_ = event_.motion.xrel;
            pointerRelativeY_ = event_.motion.yrel;
        } else if (event_.type == SDL_WINDOWEVENT)
        {
            if (event_.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                quit_ = true;
            }
        }
    }
}

bool Input::quit()
{
    return quit_;
}
