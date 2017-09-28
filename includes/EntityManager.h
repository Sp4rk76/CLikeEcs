//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_ENTITYMANAGER_H
#define CLIKEECS_ENTITYMANAGER_H

#include <vector>
#include <deque>
#include <iostream>
#include "Entity.h"

const unsigned MINIMUM_FREE_INDICES = 0;

class EntityManager
{
public:
    Entity create();

    Entity make_entity(unsigned index);

    bool alive(Entity e) const;

    void destroy(Entity e);

    std::vector<unsigned int> generation_; // size for index limit

    std::deque<unsigned int> free_indices_;
};

Entity EntityManager::create()
{
    unsigned int index = 0;
    if (!free_indices_.empty())
    {
        index = free_indices_.front();
        free_indices_.pop_front();
    } else
    {
        generation_.emplace_back(0);
        index = generation_.size() - 1;
    }

    return make_entity(index);
}

Entity EntityManager::make_entity(unsigned index)
{
    generation_[index] = 0;

    Entity entity;
    entity.id = index;
    return entity;
}

bool EntityManager::alive(Entity e) const
{
    return generation_[e.index()] == e.generation();
}

void EntityManager::destroy(Entity e)
{
    const unsigned index = e.index();
    ++generation_[index];
    std::cout << "G => " << generation_[index] << std::endl;
    free_indices_.push_back(index);
}


#endif //CLIKEECS_ENTITYMANAGER_H
