//
// Created by Sp4rk on 13-11-17.
//

#ifndef CLIKEECS_TRANSFORMCOMPONENT_H
#define CLIKEECS_TRANSFORMCOMPONENT_H

#include "systems/System.h"

#include <iostream>

//    Possible Solution:
//    // Move element at A (and references to it) to size.
//    [size] <--- [A]
//
//    //Now nothing refers to A, so we can safely move element at B (and references to it) to A.
//    [A] <--- [B]
//
//    //And finally move the element at size to B.
//    [B] <-- [size]

class TransformManager
{
public:
    explicit TransformManager(InstanceData *data);

    bool isValid(size_t id);

    Matrix4x4 matrix4x4_identity();

    int setDirty(size_t instance);

    int setClean(size_t instance);

    bool isDirty(size_t instance);

private:
    InstanceData *data_;
};

#endif //CLIKEECS_TRANSFORMCOMPONENT_H
