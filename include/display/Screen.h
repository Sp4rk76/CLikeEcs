//
// Created by Sp4rk on 10-08-17.
//

#ifndef CES_SCREEN_H
#define CES_SCREEN_H

#include <iostream>
#include <SDL.h>

class Screen
{
public:
    Screen();

    Screen(std::string title, int width, int height);

    Screen(std::string title, int width, int height, int fps);

    bool init();

    void close();

    SDL_Window *getWindow();

    SDL_Renderer *getRenderer();

    std::string &getTitle();

    int getWidth();

    int getHeight();

    int getFPS();

    int getTicksPerFrame();

    void setTitle(std::string title);

    void setWidth(int width);

    void setHeight(int height);

    void setFPS(int fps);

private:
    const std::string SCREEN_TITLE = "BindingWorlds";

    const int SCREEN_WIDTH = 800;

    const int SCREEN_HEIGHT = 600;

    const int SCREEN_FPS = 60;

    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    SDL_Window *window_;

    SDL_GLContext openGlContext_;

    SDL_Renderer *renderer_;

    std::string title_;

    int width_;

    int height_;

    int fps_;

    int ticksPerFrame_;
};

#endif //CES_SCREEN_H
