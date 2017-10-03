//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_ENTITYMANAGER_H
#define CLIKEECS_ENTITYMANAGER_H

#include <vector>
#include <deque>
#include <iostream>
#include "Entity.h"
#include "JSONLoader.h"

const unsigned MINIMUM_FREE_INDICES = 0;

class EntityManager
{
public:
    EntityManager()
    {
        // TODO: Change smth here?
        generation_.emplace_back(0);
    }

    Entity create();

    Entity make_entity(unsigned index);

    bool alive(Entity e) const;

    void destroy(Entity e);

private:
    std::vector<unsigned char> generation_; // size for index limit

    std::deque<unsigned int> free_indices_;
};


#endif //CLIKEECS_ENTITYMANAGER_H
