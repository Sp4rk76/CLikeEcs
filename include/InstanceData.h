//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_INSTANCEDATA_H
#define CLIKEECS_INSTANCEDATA_H

#include <iostream>

#include "Entity.h"
#include "Vector3.h"

const unsigned int MAX_ENTITY_REGISTERING = 1 << ENTITY_INDEX_BITS;

struct InstanceData
{
    unsigned size = 0; ///< Number of used instances
    unsigned capacity = 0; ///< Number of allocated instances
    void *buffer; ///< Buffer with instance data

    Entity *entity;
    float *mass;
    Vector3 *position;
    Vector3 *velocity;
    Vector3 *acceleration;
};

#endif //CLIKEECS_INSTANCEDATA_H
