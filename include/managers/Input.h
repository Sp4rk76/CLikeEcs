//
// Created by Sp4rk on 13-11-17.
//

#ifndef CLIKEECS_INPUT_H
#define CLIKEECS_INPUT_H

#include <SDL.h>

#define NUM_MOUSE_KEYS 8

class Input
{
public:
    Input();

    ~Input();

    void handleEvents();

    bool quit();

private:
    SDL_Event event_;
    bool keyboardKeys_[SDL_NUM_SCANCODES];
    bool mouseKeys_[NUM_MOUSE_KEYS];
    int mouseX_, mouseY_;
    int pointerRelativeX_, pointerRelativeY_;
    bool quit_;
};

#endif //CLIKEECS_INPUT_H
