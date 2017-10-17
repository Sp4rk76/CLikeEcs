//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_SYSTEMMANAGER_H
#define CLIKEECS_SYSTEMMANAGER_H

#include <cstring>
#include <vector>
#include <deque>
#include "entities/Mask.h"
#include "systems/System.h"

class SystemManager
{
public:
    std::vector<char> generation_;
    std::deque<size_t> free_indices_;

    explicit SystemManager();

    template <class T>
    T* make_system(InstanceData *data, size_t index, size_t mask)
    {
        generation_[index] = 0;

        auto system = new T(data);
        system->set_id(index);
        system->setRequiredMask(mask);
        system->start();

        return system;
    }

    template <class T>
    T* create(InstanceData *data, size_t mask)
    {
        size_t index = 0;

        if (!free_indices_.empty())
        {
            index = free_indices_.front();
            free_indices_.pop_front();
        } else
        {
            generation_.emplace_back(0);
            index = generation_.size() - 1;
        }

        return make_system<T>(data, index, mask);
    }

    bool alive(System &system);

    bool running(System &system);

    void destroy(System &system);
};

#endif //CLIKEECS_SYSTEMMANAGER_H
