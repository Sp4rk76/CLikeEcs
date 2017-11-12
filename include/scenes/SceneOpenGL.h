//
// Created by Sp4rk on 12-11-17.
//

#ifndef CLIKEECS_SCENEOPENGL_H
#define CLIKEECS_SCENEOPENGL_H

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <display/Screen.h>
#include <glew.h>

class SceneOpenGL
{
public:
    SceneOpenGL();

    SceneOpenGL(const std::string& title, int width, int height, int fps = 60);

    ~SceneOpenGL();

    void init();

    bool initGL();

    void simulate();

    void close();

private:
    Screen *screen_;
    SDL_Event event_;

    glm::mat4 projection; // projection matrice
    glm::mat4 modelview; // modelview matrice
};

#endif //CLIKEECS_SCENEOPENGL_H
