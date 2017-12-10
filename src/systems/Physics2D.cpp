//
// Created by Sp4rk on 12-10-17.
//

#include "systems/Physics2D.h"

Physics2D::Physics2D(InstanceData *data) : System(data)
{}

void Physics2D::simulate(float dt)
{
    for (auto &entity : matches_)
    {
//        position = &data_->position[entity];
//        velocity = &data_->velocity[entity];
//        acceleration = &data_->acceleration[entity];
//        std::cout << "simulate entity's position.x => " << position->x << std::endl;

    }

    std::cout << "\nDEBUG system matches (Physics 2D)" << std::endl;
    for (auto &x : matches_)
    {
        std::cout << "E = " << data_->entity[x].id << " ; " << " I = " << x << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}

void Physics2D::setLocal(size_t instance_id, const glm::mat4 &matrix)
{
    data_->local[instance_id] = matrix;
    int parent = data_->parent[instance_id];
    glm::mat4 parent_transform = isValid(parent) ? data_->world[instance_id] : matrix4x4Identity();
}

void Physics2D::transform(const glm::mat4 &parent, int instance_id)
{
    data_->world[instance_id] = (data_->local[instance_id] * parent);

    // Get First Child for the given instance_id
    int child = data_->first_child[instance_id];
    while(isValid(child))
    {
        transform(data_->world[instance_id], child);
        child = data_->next_sibling[child];
    }
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

bool Physics2D::isValid(int instance_id)
{
    return instance_id >= 0;
}

glm::mat4 Physics2D::matrix4x4Identity()
{
    return glm::mat4(1.0);
}

