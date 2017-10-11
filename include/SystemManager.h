//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_SYSTEMMANAGER_H
#define CLIKEECS_SYSTEMMANAGER_H

#include <cstring>
#include <vector>
#include <deque>
#include "Mask.h"
#include "System.h"

class SystemManager
{
public:
    std::vector<char> generation_;
    std::deque<size_t> free_indices_;

    explicit SystemManager()
    {
        generation_.emplace_back(0);
    }

    System create(size_t mask = None);

    System make_system(size_t index, size_t mask);

    bool alive(System &system)
    {
        return (generation_[system.id()] == system.generation());
    }

    bool running(System &system)
    {
        return (alive(system) && system.running());
    }

    void destroy(System &system)
    {
        const size_t index = system.id();

        system.stop();

        ++generation_[index];

        free_indices_.emplace_back(index);
    }


};

System SystemManager::create(size_t mask)
{
    size_t index = 0;

    if (!free_indices_.empty())
    {
        index = free_indices_.front();
        free_indices_.pop_front();
    }
    else
    {
        generation_.emplace_back(0);
        index = generation_.size() - 1;
    }

    return make_system(index, mask);
}

System SystemManager::make_system(size_t index, size_t mask)
{
    generation_[index] = 0;

    System system;
    system.set_id(index);
    system.setRequiredMask(mask);
    system.start();
    return system;
}

#endif //CLIKEECS_SYSTEMMANAGER_H
