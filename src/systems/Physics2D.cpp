//
// Created by Sp4rk on 12-10-17.
//

#include "systems/Physics2D.h"

Physics2D::Physics2D(InstanceData *data) : System(data) { }

void Physics2D::simulate(float dt)
{
    // Get ENTITY_ID
    for (auto &entity : matches_)
    {
        position = &data_->position[entity];
        velocity = &data_->velocity[entity];
        acceleration = &data_->acceleration[entity];

        std::cout << "simulate entity's position.x => " << position->x << std::endl;
    }

    std::cout << "\nDEBUG system matches (Physics 2D)" << std::endl;
    for(auto& x : matches_)
    {
        std::cout << "E = " << data_->entity[x].id << " ; " << " I = " << x << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}

Physics2D::~Physics2D()
{
    delete position;
    delete velocity;
    delete acceleration;
    position = nullptr;
    velocity = nullptr;
    acceleration = nullptr;
}
