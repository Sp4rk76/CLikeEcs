//
// Created by Sp4rk on 12-11-17.
//

#include "scenes/SceneOpenGL.h"

SceneOpenGL::SceneOpenGL()
{
    screen_ = new Screen();
}

SceneOpenGL::SceneOpenGL(const std::string& title, int width, int height, int fps)
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

    float vertices[] = {0.0, 0.0,   0.5,0.0,   0.0,0.5,
                        -0.8, -0.8,   -0.3, -0.8,   -0.8, -0.3};

    while (!quit)
    {
        SDL_WaitEvent(&event_);
        if (event_.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            quit = true;

        }

        glClear(GL_COLOR_BUFFER_BIT);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0);

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
