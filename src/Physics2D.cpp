//
// Created by Sp4rk on 12-10-17.
//

#include "Physics2D.h"

Physics2D::Physics2D(InstanceData *data) : System(data) { }

void Physics2D::simulate(float dt)
{
    // For each entity match
    for (auto &entity : matches_)
    {
        std::cout << "PHYSICS simulation for system (id: " << id_ << ")" << std::endl;

        position = &data_->position[entity];
        velocity = &data_->velocity[entity];
        acceleration = &data_->acceleration[entity];

        velocity->x += 500;
        position->x += (velocity->x + acceleration->x);

        std::cout << "simulate entity => " << entity << std::endl;
    }

    delete position;
    delete velocity;
    delete acceleration;
    position = nullptr;
    velocity = nullptr;
    acceleration = nullptr;

    std::cout << "Simulate this system !" << std::endl;
}
