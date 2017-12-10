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

    bool getKey(const SDL_Scancode key) const;

    bool getMouseKey(const Uint8 key) const;

    bool mouseMovement() const;

    void displayCursor(bool display) const;

    void captureCursor(bool capture) const;

    void resetKeys();

    bool quit() const;

    int x() const;

    int y() const;

    int xRel() const;

    int yRel() const;

    void setX(int x);

    void setY(int y);

    void setXRel(int xRel);

    void setYRel(int yRel);

private:
    SDL_Event event_;
    bool keyboardKeys_[SDL_NUM_SCANCODES];
    bool mouseKeys_[NUM_MOUSE_KEYS];
    int x_, y_; // Mouse pointer coordinates
    int xRel_, yRel_;
    bool quit_;
};

#endif //CLIKEECS_INPUT_H
