//
// Created by Sp4rk on 11-10-17.
//

#include "SystemManager.h"

SystemManager::SystemManager()
{
    generation_.emplace_back(0);
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