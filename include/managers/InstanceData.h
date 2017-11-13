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
#include <components/Matrix4x4.h>

struct InstanceData
{
    size_t n = 0;
    size_t size = 0;
    void *buffer = nullptr;

    Entity *entity = nullptr;
    float *mass = nullptr;
    Vector3 *position = nullptr;
    Vector3 *velocity = nullptr;
    Vector3 *acceleration = nullptr;

    Matrix4x4 *local = nullptr;
    Matrix4x4 *world = nullptr;
    size_t *parent = nullptr;
    size_t *first_child = nullptr;
    size_t *next_sibling = nullptr;
    size_t *prev_sibling = nullptr;
};

#endif //CLIKEECS_INSTANCEDATA_H
