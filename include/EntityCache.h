//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_ENTITYCACHE_H
#define CLIKEECS_ENTITYCACHE_H

#include <cstring>
#include <deque>

struct EntityCache
{
    std::deque<size_t> unreg_entities;
    std::deque<size_t> unreg_systems;
};

#endif //CLIKEECS_ENTITYCACHE_H
