//
// Created by Sp4rk on 12-11-17.
//

#include <effects/Shader.h>
#include "scenes/SceneOpenGL.h"

SceneOpenGL::SceneOpenGL()
{
    screen_ = new Screen();
}

SceneOpenGL::SceneOpenGL(const std::string &title, int width, int height, int fps)
{
    screen_ = new Screen(title, width, height, fps);
}

SceneOpenGL::~SceneOpenGL()
{
    close();
}

// TODO: improve this class
void SceneOpenGL::init()
{
    if (!screen_->init())
    {
        std::cout << "Error: could not initialize screen_gl" << std::endl;
    } else
    {
        // GLEW successfully initialized
        if (initGL())
        {
            simulate();
        }
    }
}

bool SceneOpenGL::initGL()
{
#ifdef WIN32

    GLenum initialisationGLEW(glewInit());

    if (initialisationGLEW != GLEW_OK)
    {
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

        screen_->close();

        return false;
    }

#endif

    glEnable(GL_DEPTH_TEST);

    return true;
}

void SceneOpenGL::simulate()
{
    // Variables (vertices, etc...
    bool quit(false);

    float vertices[] = {-1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,     // Face 1
                        -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0,     // Face 1

                        1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,       // Face 2
                        1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,         // Face 2

                        -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0,      // Face 3
                        -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0,    // Face 3

                        -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,        // Face 4
                        -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,        // Face 4

                        -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0,     // Face 5
                        -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0,     // Face 5

                        -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,         // Face 6
                        -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0};      // Face 6
    float colors[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 1
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

    // Create a Shader
    Shader shaderColor("shaders/couleur3D.vert", "shaders/couleur3D.frag");
    shaderColor.charger();

    // Initialize Matrices
    projection = glm::perspective(70.0, (double) (screen_->getWidth() / screen_->getHeight()), 1.0, 100.0);
    modelview = glm::mat4(1.0);

    while (!quit)
    {
        SDL_WaitEvent(&event_);
        if (event_.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            quit = true;
        }

        // Clear screen (gl)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Re-initialization: modelview
        modelview = glm::lookAt(glm::vec3(4,4,4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        // Activate Shader
        glUseProgram(shaderColor.getProgramID());

        // Define / Send vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        // Define / Send colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
        glEnableVertexAttribArray(1);

        // Send matrices to Shader
        glUniformMatrix4fv(glGetUniformLocation(shaderColor.getProgramID(), "projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderColor.getProgramID(), "modelview"), 1, GL_FALSE,
                           glm::value_ptr(modelview));

        // Display triangle with shader
        glDrawArrays(GL_TRIANGLES, 0, 36);


        /// Note: deactivate array in reverse activation order !
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        // Deactivate Shader
        glUseProgram(0);

        SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
    }

    close();
}

void SceneOpenGL::close()
{
    screen_->close();

    delete screen_;
    screen_ = nullptr;
}
