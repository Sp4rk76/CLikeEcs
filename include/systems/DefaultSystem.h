//
// Created by Sp4rk on 16-10-17.
//

#ifndef CLIKEECS_DEFAULTSYSTEM_H
#define CLIKEECS_DEFAULTSYSTEM_H

#include "System.h"

class DefaultSystem : public System
{
public:
    explicit DefaultSystem(InstanceData *data);

    void simulate(float dt) override;

public:

};

#endif //CLIKEECS_DEFAULTSYSTEM_H
