//
// Created by Sp4rk on 13-11-17.
//

#ifndef CLIKEECS_TRANSFORMCOMPONENT_H
#define CLIKEECS_TRANSFORMCOMPONENT_H

#include "System.h"

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

    void setLocal(size_t id, const Matrix4x4 &matrix)
    {
        data_->local[id] = matrix;

        size_t parent = data_->parent[id];

        Matrix4x4 parent_tm = isValid(parent) ? data_->world[parent] : matrix4x4_identity();
    }

    /// CHILDworld = PARENTworld * CHILDlocal
    void transform(const Matrix4x4 &parent, size_t id)
    {
        data_->world[id] = data_->local * parent; /// not sure about this line
    }


};

#endif //CLIKEECS_TRANSFORMCOMPONENT_H
