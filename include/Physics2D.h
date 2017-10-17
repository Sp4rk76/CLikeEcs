//
// Created by Sp4rk on 12-10-17.
//

#ifndef CLIKEECS_PHYSICS2D_H
#define CLIKEECS_PHYSICS2D_H

#include "System.h"

class Physics2D : public System
{
public:
    explicit Physics2D(InstanceData *data);
    ~Physics2D();
    void simulate(float dt) override;
private:
    Vector3 *position = nullptr;
    Vector3 *velocity = nullptr;
    Vector3 *acceleration = nullptr;
};

#endif //CLIKEECS_PHYSICS2D_H
