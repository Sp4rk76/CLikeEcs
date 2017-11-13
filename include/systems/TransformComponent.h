//
// Created by Sp4rk on 13-11-17.
//

#ifndef CLIKEECS_TRANSFORMCOMPONENT_H
#define CLIKEECS_TRANSFORMCOMPONENT_H

#include "System.h"

#include <iostream>

class TransformComponent : public System
{
public:
    TransformComponent(InstanceData *data) : System(data)
    {}

    bool isValid(size_t id)
    { return id > -1; }

    Matrix4x4 matrix4x4_identity()
    {
        Matrix4x4 matrix4x4;
        return matrix4x4;
    }

    void setLocal(size_t id, const glm::mat4 &matrix)
    {
        data_->local[id] = matrix;

        size_t parent = data_->parent[id];

        Matrix4x4 parent_tm = isValid(parent) ? data_->world[parent] : matrix4x4_identity();
    }

    /// CHILDworld = PARENTworld * CHILDlocal
    void transform(const glm::mat4 &parent, size_t id)
    {
        data_->world[id] = data_->local * parent; /// not sure about this line

        size_t child = data_->first_child[id];

        while (isValid(child))
        {
            transform(data_->world[id], child);
            child = data_->next_sibling[child];
            std::cout << "hello it's gregou" << std::endl;
        }
    }

//    Possible Solution:
//    // Move element at A (and references to it) to size.
//    [size] <--- [A]
//
//    //Now nothing refers to A, so we can safely move element at B (and references to it) to A.
//    [A] <--- [B]
//
//    //And finally move the element at size to B.
//    [B] <-- [size]

};

#endif //CLIKEECS_TRANSFORMCOMPONENT_H
