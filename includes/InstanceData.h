//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_INSTANCEDATA_H
#define CLIKEECS_INSTANCEDATA_H

#include "Entity.h"
#include "Vector3.h"

struct InstanceData
{
    unsigned size; ///< Number of used instances
    unsigned capacity; ///< Number of allocated instances
    void *buffer; ///< Buffer with instance data

    Entity *entity;
    float *mass;
    Vector3 *position;
    Vector3 *velocity;
    Vector3 *acceleration;
};

#endif //CLIKEECS_INSTANCEDATA_H
