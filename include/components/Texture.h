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

#define UNLOCK 0

class Texture
{
public:
    Texture();
    Texture(const std::string &path);
    ~Texture();
    bool load();
    GLuint getID() const;
    void setPath(const std::string &path);
    SDL_Surface *revertPixels(SDL_Surface *imageSource_) const;

private:
    GLuint id_;
    std::string path_;
};

#endif //CLIKEECS_TEXTURE_H
