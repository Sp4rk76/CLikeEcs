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

    return true;
}

void SceneOpenGL::simulate()
{
    // Variables (vertices, etc...
    bool quit(false);

    float vertices[] = {-0.5, 0.0, 0.0, 1.0, 0.5, 0.0,
                        -0.5, 0.0, 0.0, -1.0, 0.5, 0.0};
    float colors[] = {240.0 / 255.0, 210.0 / 255.0, 23.0 / 255.0,
                      230.0 / 255.0, 0.0, 230.0 / 255.0,
                      0.0, 1.0, 0.0,

                      240.0 / 255.0, 210.0 / 255.0, 23.0 / 255.0,
                      0.0, 0.0, 1.0,
                      0.0, 1.0, 0.0};

    // Create a Shader
    Shader shaderColor("shaders/couleur2D.vert", "shaders/couleur2D.frag");
    shaderColor.charger();

    while (!quit)
    {
        SDL_WaitEvent(&event_);
        if (event_.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            quit = true;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // Activate Shader
        glUseProgram(shaderColor.getProgramID());

        // Define / Send vertices
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        // Define / Send colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
        glEnableVertexAttribArray(1);

        // Display triangle with shader
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /// Note: deactivate array in reverse activation order !
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        // Deactivate Shader
        glUseProgram(0);

        SDL_GL_SwapWindow(screen_->getWindow());
    }

    close();
}

void SceneOpenGL::close()
{
    screen_->close();

    delete screen_;
    screen_ = nullptr;
}
