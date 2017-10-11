//
// Created by Sp4rk on 03-10-17.
//

#include "EntityManager.h"

Entity EntityManager::create(size_t mask)
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

    return make_entity(index, mask);
}

Entity EntityManager::make_entity(unsigned index, size_t mask)
{
    generation_[index] = 0;

    Entity entity;
    entity.id = index;
    entity.mask = mask;

    return entity;
}

bool EntityManager::alive(Entity &e) const
{
    return generation_[e.index()] == e.generation();
}

void EntityManager::destroy(Entity &e)
{
    const unsigned index = e.index();
    ++generation_[index];
    free_indices_.push_back(index);

    // TODO: review ?
    e.id = DEFAULT;
    e.mask = DEFAULT;
}

