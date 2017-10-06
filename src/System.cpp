//
// Created by Sp4rk on 05-10-17.
//

#include <malloc.h>
#include <iostream>
#include <System.h>
#include <Manager.h>

System::System()  // Test
{
    requiredMask_ = 1;
    entityMatches_ = (unsigned int*) malloc(2000000); // 2M
}

void System::simulate(float dt)
{
    // For each entity match

    // simulate entity


    std::cout << "Simulate this system !" << std::endl;
}

unsigned int System::requiredMask()
{
    return requiredMask_;
}

unsigned int *System::entityMatches() const
{
    return entityMatches_;
}

unsigned int System::entityMatch(Entity *entity)
{
    return entityMatches_[entity->id];
}

unsigned int System::entityMatch(unsigned int matchingEntity)
{
    return entityMatches_[matchingEntity];
}

void System::setEntityMatch(Instance instance)
{
    entityMatches_[instance.i] = (unsigned int)instance.i;
}

void System::unsetEntityMatch(Instance instance)
{
    entityMatches_[instance.i] = (unsigned int)instance.i;
}
