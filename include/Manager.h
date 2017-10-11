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

#define INVALID_ENTITY 0

/// NOTE: This is an "example of system design"
/// TODO: each system should have a list of registered id ?
class Manager
{
public:
    explicit Manager();

    explicit Manager(size_t size);

    ~Manager();

    void allocate(unsigned size);

//    Entity make_instance(int i);

    void register_as(Entity entity); ///< Call this function to look for an entity

    Entity entity(Entity entity);

    void setMask(Entity entity, size_t mask);

    size_t mask(Entity entity);

    void setEntity(Entity entity);

    float mass(Entity entity);

    void setMass(Entity entity, float mass);

    Vector3 position(Entity entity);

    void setPosition(Entity entity, Vector3 position);

    Vector3 velocity(Entity entity);

    void setVelocity(Entity entity, Vector3 velocity);

    Vector3 acceleration(Entity entity);

    void setAcceleration(Entity entity, Vector3 acceleration);

    // TODO: Create a validation function => check JSON file validity according (once !) before loading all entities/components
    void loadEntities(EntityManager *entityManager);

    void save(/* all E & S */);

    void simulate(float dt = 1);

    void destroy(unsigned i);

    bool isValidMask(unsigned entityMask, unsigned systemMask);

    void matchSystem(System *sys, std::size_t id);

    void setDefaultEntity();

    void loadSystems();

    void testValues();

    InstanceData data_;

    InstanceSystem sys_;
private:
//    Instance instance_;

    JSONHandler *jsonHandler_;

//    std::map<unsigned, unsigned> map_; // Entity component
};


#endif //CLIKEECS_DATAACCESSMANAGER_H
