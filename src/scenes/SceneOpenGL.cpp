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


    float xAngle(0), yAngle(0);

    while (!input_.quit())
    {
        startTime = SDL_GetTicks();

        input_.handleEvents();

        if(input_.getKey(SDL_SCANCODE_ESCAPE))
        {
            break;
        }

        if(input_.getKey(SDL_SCANCODE_UP)) { xAngle += -5; }
        if(input_.getKey(SDL_SCANCODE_DOWN)) { xAngle += 5; }
        if(input_.getKey(SDL_SCANCODE_LEFT)) { yAngle += -5; }
        if(input_.getKey(SDL_SCANCODE_RIGHT)) { yAngle += 5; }

        // Clear screen (gl)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Re-initialization: modelview
        modelview = glm::lookAt(glm::vec3(8,8,10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        // Save model view at this state
        glm::mat4 saveModelView = modelview;

        // 2 angles: rotate_x and rotate_y
        modelview = glm::rotate(modelview, xAngle, glm::vec3(1,0,0));
        modelview = glm::rotate(modelview, yAngle, glm::vec3(0,1,0));
        // Display cube
        cube.display(projection, modelview);

        // Restore model view at previous state
        modelview = saveModelView;

        modelview = glm::translate(modelview, glm::vec3(6,0,0));
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
