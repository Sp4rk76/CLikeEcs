//
// Created by Sp4rk on 13-11-17.
//

#ifndef CLIKEECS_CUBE_H
#define CLIKEECS_CUBE_H

#ifdef WIN32

#include <glew.h>

#else
#define GL3_PROTOTYPES 1
#include <gl3.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <effects/Shader.h>

class Cube
{
public:
    Cube(float size, std::string const &vertexShader, std::string const &fragmentShader);

    ~Cube();

    void display(glm::mat4 &projection, glm::mat4 &modelview);

private:
    Shader shader_;
    float vertices_[108]; // 36 vertices * 3 coordinates (6 faces = 2 triangles with 3 vertices per face);
    float colors_[108];
};

#endif //CLIKEECS_CUBE_H
