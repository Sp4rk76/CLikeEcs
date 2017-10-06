//
// Created by Sp4rk on 05-10-17.
//

#ifndef CLIKEECS_INSTANCESYSTEM_H
#define CLIKEECS_INSTANCESYSTEM_H

#include "System.h"

struct InstanceSystem
{
    unsigned n = MAX_NUMBER_OF_SYSTEMS; ///< Number of systems
    void *buffer; ///< Buffer with instance data

    System* system;
};

#endif //CLIKEECS_INSTANCESYSTEM_H
