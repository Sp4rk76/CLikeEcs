//
// Created by Sp4rk on 11-10-17.
//

#include "SystemManager.h"

System* SystemManager::create(size_t mask)
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

    return make_system(index, mask);
}

SystemManager::SystemManager()
{
    generation_.emplace_back(0);
}

System* SystemManager::make_system(size_t index, size_t mask)
{
    generation_[index] = 0;

    auto system = new System();
    system->set_id(index);
    system->setRequiredMask(mask);
    system->start();

    return system;
}

bool SystemManager::alive(System &system)
{
    return (generation_[system.id()] == system.generation());
}

bool SystemManager::running(System &system)
{
    return (alive(system) && system.running());
}

void SystemManager::destroy(System &system)
{
    const size_t index = system.id();

    system.stop();
    system.set_id(DEFAULT);
    system.setRequiredMask(None);
    system.setName("");

    ++generation_[index];

    free_indices_.emplace_back(index);
}