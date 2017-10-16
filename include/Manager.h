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
#include <SystemManager.h>
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

    void queryRegistration(Entity &entity);

    void queryRegistration(System *system);

    Entity entity(Entity entity);

    void setMask(Entity entity, size_t mask);

    size_t mask(Entity entity);

    void setEntity(Entity &entity);

    float mass(Entity entity);

    void setMass(Entity entity, float mass);

    Vector3 position(Entity entity);

    void setPosition(Entity &entity, Vector3 &position);

    Vector3 velocity(Entity entity);

    void setVelocity(Entity &entity, Vector3 &velocity);

    Vector3 acceleration(Entity entity);

    void setAcceleration(Entity &entity, Vector3 &acceleration);

    // TODO: Create a validation function => check JSON file validity according (once !) before loading all entities/components
    size_t loadEntities(EntityManager *entityManager);

    size_t loadSystems(SystemManager *systemManager);

    void save(/* all E & S */);

    void simulate(float dt = 1);

    void destroy(unsigned i);

    bool isValidMask(unsigned entityMask, unsigned systemMask);

    void matchSystem(System *sys, std::size_t id);

    System *system(System *system);

    void setSystem(System *system);

    void setDefaultEntity();

    void setDefaultSystem();

    InstanceData *data();

    void configureSystem(System *s, size_t sys_id, size_t sys_mask, std::string& sys_name);

private:
    InstanceData data_;

    InstanceSystem sys_;

    JSONHandler *jsonHandler_;
};


#endif //CLIKEECS_DATAACCESSMANAGER_H