//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_DATAACCESSMANAGER_H
#define CLIKEECS_DATAACCESSMANAGER_H

#include <map>
#include <cstring>
#include <cstdlib>
#include "Entity.h"
#include "Vector3.h"
#include "InstanceData.h"
#include "EntityManager.h"

#include "rapidjson/document.h"

struct Instance
{
    int i = 1;
}; ///< Selected Entity Instance ('i' is the Entity id (to look at))

class System
{
public:
    explicit System();

    ~System();

    void allocate(unsigned size);

    Instance make_instance(int i);


    Instance lookup(Entity entity); ///< Call this function to look for an entity

    Entity entity(Instance instance);

    void setEntity(Instance instance, Entity entity);

    float mass(Instance instance);

    void setMass(Instance instance, float mass);

    Vector3 position(Instance instance);

    void setPosition(Instance instance, Vector3 position);

    Vector3 velocity(Instance instance);

    void setVelocity(Instance instance, Vector3 velocity);

    Vector3 acceleration(Instance instance);

    void setAcceleration(Instance instance, Vector3 acceleration);

    // TODO: Create a validation function => check JSON file validity according (once !) before loading all entities/components
    void loadEntities(EntityManager &entityManager);

    // TODO: Idem
    void loadComponents();

    void simulate(float dt = 1);

    void destroy(unsigned i);

    InstanceData data_;

private:
    Instance instance_;

    JSONLoader *jsonLoader_;

    std::map<unsigned, unsigned> map_; // Entity component
};


#endif //CLIKEECS_DATAACCESSMANAGER_H
