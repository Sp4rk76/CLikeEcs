#ifdef _WIN32

#include <windows.h>
#include <cstdio> // stdio.h deprecated ?
#include <tchar.h>
#define GLEW_BUILD
#include <glew.h>

#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// TODO: include this file (& link ?)
#include <gl3.h>
#endif

/// SDL Headers
#include <SDL.h>
#include <iostream>

/// OpenGL Headers
#include <GL.h>
#include <GLU.h>

// Core Headers
#include <managers/Manager.h>
#include <systems/Physics2D.h>
#include <display/Screen.h>

class SparkEngine
{
public:
    void init();
};

// TODO: when setting a new Entity instance in map, check if it already exists !
int main(int argc, char **argv)
{
    float vertices[] = {0.0, 0.0,   0.5,0.0,   0.0,0.5,
                         -0.8, -0.8,   -0.3, -0.8,   -0.8, -0.3};

    SDL_Event event;
    bool quit(false);
    auto screen = new Screen();

    screen->init();

    GLenum initialisationGlew(glewInit());
    // Si l'initialisation a échouée :

    if(initialisationGlew != GLEW_OK)
    {
        // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGlew) << std::endl;
    }

    while(!quit)
    {
        SDL_WaitEvent(&event);
        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            quit = true;
            screen->close();
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(screen->getWindow());
    }

    SparkEngine sparkEngine;
    sparkEngine.init();

    return 0;
}
void SparkEngine::init()
{

    auto entityManager = new EntityManager();
    auto systemManager = new SystemManager();
    auto manager = new Manager(10);

    size_t loaded_entities = manager->loadEntities(entityManager);
    std::cout << "Loaded Entities: " << loaded_entities << std::endl;

    size_t loaded_systems = manager->loadSystems(systemManager);
    std::cout << "Loaded Systems: " << loaded_systems << std::endl;

    /// TEST Systems
    auto system = systemManager->create<Physics2D>(manager->data(), Position); // id & mask defined in
    system->setName("CustomSystem");
    manager->setSystem(system);

    for (auto &id : manager->sys()->reg_systems)
    {
        std::cout << "System Name : " << manager->sys()->systems[id]->name() << std::endl;
    }

    // TODO: Modify destroyEC method to properly delete an entity
//    manager->destroyEC(1);
//    manager->destroyEC(2);
//    manager->destroyEC(3);

    /// NOTE: the simulation can alterate the data (saved)
    manager->simulate();
    manager->save();

//    for(auto& x : manager->entity_instances)
//    {
//        std::cout << "E = " << x.first << " ; " << " I = " << x.second << std::endl;
//    }
//
//    std::cout << "Instance_IDs | ";
//    for(auto& op : manager->instance_ids)
//    {
//        std::cout << op << " | ";
//    }
//    std::cout << std::endl;

}