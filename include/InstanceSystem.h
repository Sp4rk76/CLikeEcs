//
// Created by Sp4rk on 05-10-17.
//

#ifndef CLIKEECS_INSTANCESYSTEM_H
#define CLIKEECS_INSTANCESYSTEM_H

#define MAX_NUMBER_OF_SYSTEMS 10
#define INVALID_SYSTEM 0

#include <set>
#include "System.h"

struct InstanceSystem
{
    std::set<size_t> reg_systems;
    unsigned numSystems = 0; ///< Number of systems
    unsigned size = MAX_NUMBER_OF_SYSTEMS;

    System** systems = nullptr;
};

#endif //CLIKEECS_INSTANCESYSTEM_H
