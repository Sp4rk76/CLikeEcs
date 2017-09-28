//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_DATAACCESSMANAGER_H
#define CLIKEECS_DATAACCESSMANAGER_H

#include <unordered_map>
#include <cstring>
#include <cstdlib>
#include "Entity.h"
#include "Vector3.h"
#include "InstanceData.h"
#include "EntityManager.h"

struct Instance { int i; }; ///< Selected Entity Instance ('i' is the Entity id (to look at))

class ComponentManager
{
public:
    void allocate(unsigned size)
    {
        if (size > data_.size)
        {
            return;
        }

        InstanceData newData_;
        const unsigned bytes = size * (sizeof(Entity) + sizeof(float) + 3 * sizeof(Vector3));
        newData_.buffer = allocator_.allocate(bytes);
        newData_.size = data_.size;
        newData_.capacity = size;

        newData_.entity = (Entity *)(newData_.buffer);
        newData_.mass = (float*)(newData_.entity + size);
        newData_.position = (Vector3 *)(newData_.mass + size);
        newData_.velocity = newData_.position + size;
        newData_.acceleration = newData_.acceleration + size;

        memcpy(newData_.entity, data_.entity, data_.size * sizeof(Entity));
        memcpy(newData_.mass, data_.mass, data_.size * sizeof(float));
        memcpy(newData_.position, data_.position, data_.size * sizeof(Vector3));
        memcpy(newData_.velocity, data_.velocity, data_.size * sizeof(Vector3));
        memcpy(newData_.acceleration, data_.acceleration, data_.size * sizeof(Vector3));

        allocator_.deallocate(data_.buffer, size); // size added
        data_ = newData_;
    }

    Instance make_instance(int i)
    {
        instance_.i = i;
        return instance_;
    }

    Instance lookup(Entity e) ///< Call this function to look for an entity
    {
        return make_instance(map_[e]);
    }

    float mass(Instance instance)
    {
        return data_.mass[instance.i];
    }

    void setMass(Instance instance, float mass)
    {
        data_.mass[instance.i] = mass;
    }

    Vector3 position(Instance instance)
    {
        return data_.position[instance.i];
    }

    void setPosition(Instance instance, Vector3 position)
    {
        data_.position[instance.i] = position;
    }

    Vector3 velocity(Instance instance)
    {
        return data_.velocity[instance.i];
    }

    void setVelocity(Instance instance, Vector3 velocity)
    {
        data_.velocity[instance.i] = velocity;
    }

    Vector3 acceleration(Instance instance)
    {
        return data_.acceleration[instance.i];
    }

    void setAcceleration(Instance instance, Vector3 acceleration)
    {
        data_.acceleration[instance.i] = acceleration;
    }

    void simulate(float dt)
    {
        for (unsigned i=0; i<data_.size; ++i) {
            data_.velocity[i] += data_.acceleration[i] * dt;
            data_.position[i] += data_.velocity[i] * dt;
        }
    }

    void destroy(unsigned i)
    {
        unsigned last = data_.size - 1;
        Entity e = data_.entity[i];
        Entity last_e = data_.entity[last];

        data_.entity[i] = data_.entity[last];
        data_.mass[i] = data_.mass[last];
        data_.position[i] = data_.position[last];
        data_.velocity[i] = data_.velocity[last];
        data_.acceleration[i] = data_.acceleration[last];

        map_[last_e] =  i;
        map_.erase(e);

        --data_.size; // unsure about this (--_n;)
    }

    void gc(const EntityManager &em)
    {
        unsigned alive_in_row = 0;
        while (data_.size > 0 && alive_in_row < 4) {
            unsigned i = rand() % (data_.size - 1); // random_in_range(0, data_.size - 1);
            if (em.alive(data_.entity[i])) {
                ++alive_in_row;
                continue;
            }
            alive_in_row = 0;
            destroy(i);
        }
    }

private:
    InstanceData data_;

    std::allocator allocator_;

    // TODO: entity-component ID mapping and looking
    std::unordered_map<Entity, unsigned> map_;

    Instance instance_;
};


#endif //CLIKEECS_DATAACCESSMANAGER_H
