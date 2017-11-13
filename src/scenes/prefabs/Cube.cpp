//
// Created by Sp4rk on 13-11-17.
//

#include "scenes/prefabs/Cube.h"

Cube::Cube(float size, std::string const &vertexShader, std::string const &fragmentShader)
{
    shader_ = Shader(vertexShader, fragmentShader);

    // Loading Shader
    shader_.charger();

    // Size Division ('cause -1;1 "doubles" the size)
    size /= 2.0;

    // Vertices temporaires
    float verticesTmp[] = {-size, -size, -size, size, -size, -size, size, size, -size,     // Face 1
                           -size, -size, -size, -size, size, -size, size, size, -size,     // Face 1

                           size, -size, size, size, -size, -size, size, size, -size,       // Face 2
                           size, -size, size, size, size, size, size, size, -size,         // Face 2

                           -size, -size, size, size, -size, size, size, -size, -size,      // Face 3
                           -size, -size, size, -size, -size, -size, size, -size, -size,    // Face 3

                           -size, -size, size, size, -size, size, size, size, size,        // Face 4
                           -size, -size, size, -size, size, size, size, size, size,        // Face 4

                           -size, -size, -size, -size, -size, size, -size, size, size,     // Face 5
                           -size, -size, -size, -size, size, -size, -size, size, size,     // Face 5

                           -size, size, size, size, size, size, size, size, -size,         // Face 6
                           -size, size, size, -size, size, -size, size, size, -size};      // Face 6

    // Couleurs temporaires

    float colorsTmp[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 1
                         1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 1

                         0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 2
                         0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 2

                         0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,           // Face 3
                         0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,           // Face 3

                         1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 4
                         1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 4

                         0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 5
                         0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 5

                         0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,           // Face 6
                         0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0};          // Face 6

    for (size_t i = 0; i < 108; i++)
    {
        vertices_[i] = verticesTmp[i];
        colors_[i] = colorsTmp[i];
    }
}

Cube::~Cube()
{

}

void Cube::display(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(shader_.getProgramID());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices_);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors_);
    glEnableVertexAttribArray(1);

    glUniformMatrix4fv(glGetUniformLocation(shader_.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader_.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}