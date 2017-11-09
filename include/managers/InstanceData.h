//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_INSTANCEDATA_H
#define CLIKEECS_INSTANCEDATA_H

#include <iostream>

#include "components/Vector3.h"
#include "entities/Entity.h"
#include "components/Sprite.h"
#include "components/Transform.h"
#include <set>

// TODO (suggestion): can improve performance by iterating over entities from 1 to n - 1 instead of a set of reg_entities;
// TODO: Pb: in this case, we have to keep a map of <EntityID,InstanceID> to retrieve the real entity[InstanceID] with the entity id (EntityID);
/// ex: it would give:
/// Instance inst = map[entity.id];
/// data_.entity[inst];
struct InstanceData
{
    size_t n = 0;
    size_t size = 0; ///< Max instanciable instances
    void *buffer = nullptr; ///< Buffer with instance data

    std::set<size_t> reg_entities;

    Entity *entity = nullptr;
    float *mass = nullptr;
    Vector3 *position = nullptr;
    Vector3 *velocity = nullptr;
    Vector3 *acceleration = nullptr;
    // TODO: review this code & all dependencies
//    Transform *transform = nullptr;
    Sprite2D *sprite = nullptr;
};

#endif //CLIKEECS_INSTANCEDATA_H
