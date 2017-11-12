//
// Created by Sp4rk on 12-11-17.
//

#include "display/Screen.h"

Screen::Screen()
{
    window_ = nullptr;
    renderer_ = nullptr;
    title_ = SCREEN_TITLE;
    width_ = SCREEN_WIDTH;
    height_ = SCREEN_HEIGHT;
    fps_ = SCREEN_FPS;
    ticksPerFrame_ = SCREEN_TICKS_PER_FRAME;
}

Screen::Screen(std::string title, int width, int height)
{
    window_ = nullptr;
    renderer_ = nullptr;
    title_ = std::move(title);
    width_ = width;
    height_ = height;
}

Screen::Screen(std::string title, int width, int height, int fps)
{
    window_ = nullptr;
    renderer_ = nullptr;
    title_ = std::move(title);
    width_ = width;
    height_ = height;
    fps_ = fps;
    ticksPerFrame_ = 1000 / fps_;
}

bool Screen::init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize (Video module). SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else
    {
        // Target OpenGL version range
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // 24 bits Double Buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        if (window_ == nullptr)
        {
            std::cout << "Window could not be created. SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        } else
        {
            openGlContext_ = SDL_GL_CreateContext(window_);
            if (!openGlContext_)
            {
                std::cout << "Failed to create OpenGL Context : " << SDL_GetError() << std::endl;
            }
        }

    }

    return success;
}


void Screen::close()
{
    SDL_GL_DeleteContext(openGlContext_);

    SDL_DestroyWindow(window_);

    SDL_DestroyRenderer(renderer_);

    SDL_Quit(); // TODO: see if it belongs to here
}

SDL_Window *Screen::getWindow()
{
    return window_;
}

SDL_Renderer *Screen::getRenderer()
{
    return renderer_;
}

std::string &Screen::getTitle()
{
    return title_;
}

int Screen::getWidth()
{
    return width_;
}

int Screen::getHeight()
{
    return height_;
}

int Screen::getFPS()
{
    return fps_;
}

int Screen::getTicksPerFrame()
{
    return ticksPerFrame_;
}

void Screen::setTitle(std::string title)
{
    if (title_ != title && !title.empty())
    {
        title_ = std::move(title);
    }
}

void Screen::setWidth(int width)
{
    if (width_ != width && width > 0)
    {
        width_ = width;
    }
}

void Screen::setHeight(int height)
{
    if (height_ != height && height > 0)
    {
        height_ = height;
    }
}

void Screen::setFPS(int fps)
{
    if (fps_ != fps && fps >= 0)
    {
        fps_ = fps;
    }
}
