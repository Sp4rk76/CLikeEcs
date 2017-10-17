//
// Created by Sp4rk on 17-10-17.
//

#ifndef CLIKEECS_TRANSFORM_H
#define CLIKEECS_TRANSFORM_H

#include "Vector3.h"

struct Transform
{
    Vector3 position = Vector3(0,0,0);
    Vector3 scale = Vector3(0,0,0);
    Vector3 rotation = Vector3(0,0,0);
};

#endif //CLIKEECS_TRANSFORM_H
