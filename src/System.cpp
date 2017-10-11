//
// Created by Sp4rk on 05-10-17.
//

#include <malloc.h>
#include <iostream>
#include <System.h>
#include <Manager.h>
#include <algorithm>

#define INVALID_MATCHING_ID 0

System::System()  // Test
{

    ///NOTE: as matches_ begin to 0 index, to get real entity index,
    /// we need to do "entity_index - 1";
    id_ = 0;
    name_ = "";
    requiredMask_ = DEFAULT;
}

void System::simulate(float dt)
{
    // For each entity match
    for (auto entity : matches_)
    {
        std::cout << "simulate entity => " << entity << std::endl;
    }

    // simulate entity


    std::cout << "Simulate this system !" << std::endl;
}

unsigned int System::requiredMask()
{
    return requiredMask_;
}

std::vector<size_t> System::entityMatches() const
{
    return matches_;
}

unsigned int System::entityMatch(Entity *entity)
{
    return matches_[entity->id - 1];
}

unsigned int System::entityMatch(std::size_t matchingEntity)
{
    return matches_[matchingEntity - 1];
}

void System::setEntityMatch(std::size_t id)
{
    // TODO: replace by INVALID_ENTITY
    if (id <= INVALID_MATCHING_ID)
    {
        std::cout << "Error: Trying to set (register) an invalid entity to a system (invalid id)" << std::endl;
        return;
    } else
    {
        matches_.emplace_back(id);
    }
}

void System::unsetEntityMatch(std::size_t id)
{
    matches_.erase(std::remove(matches_.begin(), matches_.end(), id), matches_.end());
}

void System::setRequiredMask(std::size_t requiredMask)
{
    requiredMask_ = requiredMask;
}

void System::clear()
{
    matches_.clear();
}

void System::free()
{
    clear();

    requiredMask_ = 0;

//    delete name_;
}

void System::setName(const std::string &name)
{
    name_ = name;
}

std::string System::name() const
{
    return name_;
}
