//
// Created by Sp4rk on 12-10-17.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "systems/Physics2D.h"

Physics2D::Physics2D(InstanceData *data) : System(data)
{}


// TODO: there are problems because of ENTITY LOOKUP (which is MISSING !);
void Physics2D::simulate(float dt)
{
    for (auto &entity : matches_)
    {
//        position = &data_->position[entity];
//        velocity = &data_->velocity[entity];
//        acceleration = &data_->acceleration[entity];
//        std::cout << "simulate entity's position.x => " << position->x << std::endl;

        auto car = data_->entity[entity].id;
        if(car == 1)
        {
            // should init local to identity mat4

            // Set (translate) car and all car's children entities to 2000.0f (for x,y and z);
            setLocal(entity, glm::translate(matrix4x4Identity(), glm::vec3(2000.0f, 2000.0f, 2000.0f)));
        }
    }

    std::cout << "Body debug!" << std::endl;
    double dArray[16] = {0.0};
    const float *pSource = (const float*)glm::value_ptr(data_->world[2]);
    for (int i = 0; i < 16; ++i){
        if((i % 4) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << (dArray[i] = pSource[i]);
    }
    std::cout << "Body debug!" << std::endl;

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
    transform(parent_transform, instance_id);
}

void Physics2D::transform(const glm::mat4 &parent, int instance_id)
{
    data_->world[instance_id] = (data_->local[instance_id]) * parent;

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

