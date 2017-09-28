#include <iostream>
#include "../includes/Entity.h"
#include "../includes/EntityManager.h"

const unsigned MAX_ENTITIES = 2048;


int main()
{
    EntityManager entityManager;

    Entity e1 = entityManager.create();
    Entity e2 = entityManager.create();

    std::cout << "e1 (id)= \n" << e1.id << std::endl;
    std::cout << "e1 (i) = " << e1.index() << std::endl;
    std::cout << "e1 (g) = " << e1.generation() << std::endl;

    std::cout << "e2 (id)= " << e2.id << std::endl;
    std::cout << "e2 (i) = " << e2.index() << std::endl;
    std::cout << "e2 (g) = " << e2.generation() << std::endl;


    auto entities = new Entity[MAX_ENTITIES];

    for(int i = 0; i < MAX_ENTITIES; ++i)
    {
        entities[i] = entityManager.create();

        std::cout << "entity " << i << " id => " << entities[i].id << std::endl;
        std::cout << "entity " << i << " index() => " << entities[i].index() << std::endl;
        std::cout << "entity " << i << " generation() => " << entities[i].generation() << std::endl;
    }

    entityManager.destroy(entities[10]);

    std::cout << "ALIVE (0) = " << entityManager.alive(entities[10]) << std::endl;

    entities[10] = entityManager.create();

    std::cout << "ALIVE (1) = " << entityManager.alive(entities[10]) << std::endl;

    Entity o = entityManager.create();
    std::cout << entityManager.alive(o) << std::endl;

    return 0;
}