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
#include "InstanceSystem.h"
#include "EntityManager.h"
#include "rapidjson/document.h"
#include "Instance.h"

/// NOTE: This is an "example of system design"
/// TODO: each system should have a list of registered id ?
class Manager
{
public:
    explicit Manager();

    explicit Manager(size_t size);

    ~Manager();

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
    void loadEntities(EntityManager *entityManager);

    void simulate(float dt = 1);

    void destroy(unsigned i);

    bool isValid(rapidjson::Document document);

    bool isValidMask(unsigned entityMask, unsigned systemMask);

    void matchSystem(System *sys, Instance i);

    void testValues();

    InstanceData data_;

    System* systems_[MAX_NUMBER_OF_SYSTEMS];
private:
    Instance instance_;

    JSONLoader *jsonLoader_;

    std::map<unsigned, unsigned> map_; // Entity component
};


#endif //CLIKEECS_DATAACCESSMANAGER_H
