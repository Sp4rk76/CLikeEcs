//
// Created by Sp4rk on 05-10-17.
//

#ifndef CLIKEECS_SYSTEM_H
#define CLIKEECS_SYSTEM_H

#define MAX_NUMBER_OF_SYSTEMS 10

#include "Entity.h"
#include "Instance.h"

class System
{
public:
    System();

    void simulate(float dt);

    unsigned int requiredMask();

    unsigned int *entityMatches() const;

    unsigned int entityMatch(Entity *entity);

    unsigned int entityMatch(unsigned int matchingEntity);

    void setEntityMatch(Instance instance);

    void unsetEntityMatch(Instance instance);

    // const ? if need to remove one component verification ? for some game it can be problematic ? => need to refresh entity subscriptions.
    unsigned int requiredMask_;
private:

    unsigned int* entityMatches_;
};

#endif //CLIKEECS_SYSTEM_H
