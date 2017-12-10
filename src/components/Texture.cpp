//
// Created by Sp4rk on 15-11-17.
//

#include "components/Texture.h"

Texture::Texture(const std::string &path)
{
    id_ = 0;
    path_ = path;
}

Texture::~Texture()
{
    glDeleteTextures(1, &id_);
}

bool Texture::load()
{
    SDL_Surface *image = IMG_Load(path_.c_str());
    if (image == nullptr)
    {
        std::cout << "Error: Failed to load image" << std::endl;
        return false;
    }

    // Revert pixels
    SDL_Surface *revertImage = revertPixels(image);

    // id generation
    glGenTextures(1, &id_);

    // Lock
    glBindTexture(GL_TEXTURE_2D, id_);

    GLenum internFormat = 0;
    GLenum format = 0;

    // Determine number of image components
    if (revertImage->format->BytesPerPixel == 3)
    {
        internFormat = GL_RGB;

        if (revertImage->format->Rmask == 0xff)
        {
            format = GL_RGB;
        } else
        {
            format = GL_BGR;
        }
    } else if (revertImage->format->BytesPerPixel == 4)
    {
        internFormat = GL_RGBA;

        if (revertImage->format->Rmask == 0xff)
        {
            format = GL_RGBA;
        } else
        {
            format = GL_BGRA;
        }
    } else
    {
        std::cout << "Error: Image format not recognized." << std::endl;
        SDL_FreeSurface(revertImage);
        return false;
    }

    // Copy image pixels in the texture
    glTexImage2D(GL_TEXTURE_2D, 0, internFormat, revertImage->w, revertImage->h, 0, format, GL_UNSIGNED_BYTE, revertImage->pixels);

    // Texture Filter (min distance (=near)) => precise
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Texture Filter (max distance (=far)) => not precise
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Unlock
    glBindTexture(GL_TEXTURE_2D, UNLOCK);



    // Free surface
    SDL_FreeSurface(revertImage);

    return true;
}

GLuint Texture::getID() const
{
    return id_;
}

void Texture::setPath(const std::string &path)
{
    path_ = path;
}

SDL_Surface *Texture::revertPixels(SDL_Surface *imageSource_) const
{
    SDL_Surface *invertedImage = SDL_CreateRGBSurface(0, imageSource_->w, imageSource_->h,
                                                       imageSource_->format->BitsPerPixel, imageSource_->format->Rmask,
                                                       imageSource_->format->Gmask, imageSource_->format->Bmask,
                                                       imageSource_->format->Amask);

    // Intermediate tables -> pixel manipulation
    unsigned char* pixelsSources = (unsigned char*) imageSource_->pixels;
    unsigned char* pixelsInverses = (unsigned char*) invertedImage->pixels;

    // Revert pixels
    for(int i = 0; i < imageSource_->h; i++)
    {
        for(int j = 0; j < imageSource_->w * imageSource_->format->BytesPerPixel; j++)
            pixelsInverses[(imageSource_->w * imageSource_->format->BytesPerPixel * (imageSource_->h - 1 - i)) + j] = pixelsSources[(imageSource_->w * imageSource_->format->BytesPerPixel * i) + j];
    }

    return invertedImage;
}

Texture::Texture()
{
    id_ = 0;
    path_ = "";
}
