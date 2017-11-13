//
// Created by Sp4rk on 12-11-17.
//

#include <effects/Shader.h>
#include <scenes/prefabs/Cube.h>
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

    size_t frameRate = 1000 / 60;
    Uint32 startTime = 0, endTime = 0, elapsedTime = 0;

    // Initialize Matrices
    projection = glm::perspective(70.0, (double) (screen_->getWidth() / screen_->getHeight()), 1.0, 100.0);
    modelview = glm::mat4(1.0);

    Cube cube(1.0, "shaders/couleur3D.vert", "shaders/couleur3D.frag");


    float angle(0);

    while (!quit)
    {
        startTime = SDL_GetTicks();

        SDL_PollEvent(&event_);
        if (event_.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            quit = true;
        }

        // Clear screen (gl)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Re-initialization: modelview
        modelview = glm::lookAt(glm::vec3(10,10,10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        if(angle >= 360.0)
        {
            angle -= 360.0;
        }

        angle += 1.0;

        // Save model view at this state
        glm::mat4 saveModelView = modelview;

        modelview = glm::rotate(modelview, angle, glm::vec3(0,1,0));
        cube.display(projection, modelview);

        // Restore model view at previous state
        modelview = saveModelView;

        modelview = glm::translate(modelview, glm::vec3(10,0,0));
        cube.display(projection, modelview);

        SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

        endTime = SDL_GetTicks();
        elapsedTime = endTime - startTime;
        if(elapsedTime < frameRate) // elapsedTime < (1000/60);
        {
            SDL_Delay(frameRate - elapsedTime); // wait rest of time
        }
    }

    close();
}

void SceneOpenGL::close()
{
    screen_->close();

    delete screen_;
    screen_ = nullptr;
}
