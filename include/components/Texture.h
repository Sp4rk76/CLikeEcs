//
// Created by Sp4rk on 15-11-17.
//

#ifndef CLIKEECS_TEXTURE_H
#define CLIKEECS_TEXTURE_H

#ifdef WIN32
#include <glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Texture
{
public:
    Texture(std::string path);
    ~Texture();
    size_t load();

private:
    GLuint id_;
    std::string path_;
};

Texture::Texture(std::string path)
{
    path_ = path;
}

#endif //CLIKEECS_TEXTURE_H
