//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_DATAACCESSMANAGER_H
#define CLIKEECS_DATAACCESSMANAGER_H

#include <map>
#include <cstring>
#include <cstdlib>
#include "entities/Entity.h"
#include "components/Vector3.h"
#include "InstanceData.h"
#include "InstanceSystem.h"
#include "EntityManager.h"
#include <managers/SystemManager.h>
#include "rapidjson/document.h"

#define INVALID_ENTITY 0

typedef std::map<size_t, size_t> EntityInstanceMap;

/// NOTE: This is an "example of system design"
/// TODO: each system should have a list of registered id ?
class Manager
{
public:
    explicit Manager();

    explicit Manager(size_t size);

    ~Manager();

    void allocate(unsigned size);

    void queryRegistration(Entity &entity);

    void queryRegistration(System *system);

    size_t lookup(size_t entity_id);

    Entity entity(size_t instance_id);

    size_t mask(size_t instance_id);

    float mass(size_t instance_id);

    Vector3 position(size_t instance_id);

    Vector3 velocity(size_t instance_id);

    Vector3 acceleration(size_t instance_id);

    //TODO: signature validity ? viable ?
    void setEntity(int instance_id, Entity &entity);

    void setMask(size_t instance_id, size_t mask);

    void setMass(size_t instance_id, float &mass);

    void setPosition(size_t instance_id, Vector3 &position);

    void setVelocity(size_t instance_id, Vector3 &velocity);

    void setAcceleration(size_t instance_id, Vector3 &acceleration);

    // TODO: Create a validation function => check JSON file validity according (once !) before loading all entities/components
    size_t loadEntities(EntityManager *entityManager);

    size_t loadSystems(SystemManager *systemManager);

    void save(/* all E & S */);

    void simulate(float dt = 1);

    void destroyEC(unsigned id);

    bool isValidMask(unsigned entityMask, unsigned systemMask);

    void matchSystem(System *sys, std::size_t id);

    System *system(System *system);

    void setSystem(System *system);

    void setDefaultSystem();

    InstanceData *data();

    InstanceSystem *sys();

    EntityInstanceMap entity_instances = EntityInstanceMap();

    void setEntityInstance(size_t entity_id, int instance_id);

    int generateInstanceId();

    std::set<int> instance_ids;

private:
    InstanceData data_;

    InstanceSystem sys_;

    JSONHandler *jsonHandler_;
};


#endif //CLIKEECS_DATAACCESSMANAGER_H