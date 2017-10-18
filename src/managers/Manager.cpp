//
// Created by Sp4rk on 03-10-17.
//

#include <fstream>
#include <systems/Physics2D.h>
#include <systems/DefaultSystem.h>
#include <systems/Renderer2D.h>
#include "managers/Manager.h"

// TODO: custom allocation for systems ?
Manager::Manager()
{
    allocate(3200);

    setDefaultEntity();

    setDefaultSystem();

    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    jsonHandler_ = new JSONHandler();
}

Manager::Manager(size_t size)
{
    allocate(size);

    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    setDefaultEntity();

    setDefaultSystem();

    jsonHandler_ = new JSONHandler();
}

Manager::~Manager()
{
    for (auto n : sys_.reg_systems)
    {
        delete sys_.systems[n];
        sys_.systems[n] = nullptr;
    }

    delete sys_.systems;
    sys_.systems = nullptr;

    free(data_.buffer);

    // TODO: call jsonHandler_->close, which calls free itself ?
    jsonHandler_->free();
    delete jsonHandler_;
    jsonHandler_ = nullptr;
}

void Manager::allocate(unsigned size)
{
    data_.size = size;
    std::cout << "Allocated data size: " << data_.size << std::endl;

    const unsigned int bytes = size * (sizeof(Entity) + sizeof(float) + (3 * sizeof(Vector3)));
    data_.buffer = malloc(bytes);

    data_.entity = (Entity *) (data_.buffer);
    data_.mass = (float *) (data_.entity + size);
    data_.position = (Vector3 *) (data_.mass + size);
    data_.velocity = data_.position + size; // still Vector3
    data_.acceleration = data_.velocity + size;
}

void Manager::queryRegistration(Entity &entity)
{
    if (data_.reg_entities.count(entity.id) == 0)
    {
        data_.reg_entities.insert(entity.id);
    }

    for (auto &reg_id : sys_.reg_systems)
    {
        auto &system = sys_.systems[reg_id];

        // TODO: check if the entity is already in the system to query

        if (system->entityMatches().count(entity.id) == 0) // entity not already registered
        {
            if (isValidMask(entity.mask, system->requiredMask()))
            {
                std::cout << "Register entity " << entity.id << "(" << entity.mask << ")" << " to System '"
                          << system->name() << "'(" << system->requiredMask() << ")"
                          << std::endl;

                matchSystem(system, entity.id);
            }
        }
    }
}

void Manager::queryRegistration(System *system)
{
    if (sys_.reg_systems.count(system->id()) == 0)
    {
        sys_.reg_systems.insert(system->id());
    }

    for (auto &reg_id : data_.reg_entities)
    {
        auto &entity = data_.entity[reg_id];

        if (system->entityMatches().count(entity.id) == 0) // entity not already registered
        {
            if (isValidMask(entity.mask, system->requiredMask()))
            {
                // TODO: check if entity is already registered
                std::cout << "Register entity " << entity.id << "(" << entity.mask << ")" << " to System '"
                          << system->name() << "'(" << system->requiredMask() << ")"
                          << std::endl;

                matchSystem(system, entity.id);
            }
        }
    }
}

System *Manager::system(System *system)
{
    return sys_.systems[system->id()];
}

void Manager::setSystem(System *system)
{
    system->setData(&data_);

    system->start();

    sys_.systems[system->id()] = system;

    queryRegistration(system);
}

Entity Manager::entity(Entity entity)
{
    return data_.entity[entity.id];
}

void Manager::setEntity(Entity &entity)
{
    data_.entity[entity.id] = entity;

    queryRegistration(entity);
}

float Manager::mass(Entity entity)
{
    return data_.mass[entity.id];
}

void Manager::setMass(Entity entity, float mass)
{
    data_.mass[entity.id] = mass;
}

Vector3 Manager::position(Entity entity)
{
    return data_.position[entity.id];
}

void Manager::setPosition(Entity &entity, Vector3 &position)
{
    data_.position[entity.id] = position;
}

Vector3 Manager::velocity(Entity entity)
{
    return data_.velocity[entity.id];
}

void Manager::setVelocity(Entity &entity, Vector3 &velocity)
{
    data_.velocity[entity.id] = velocity;
}

Vector3 Manager::acceleration(Entity entity)
{
    return data_.acceleration[entity.id];
}

void Manager::setAcceleration(Entity &entity, Vector3 &acceleration)
{
    data_.acceleration[entity.id] = acceleration;
}

// TODO: make JSON loading code safier
size_t Manager::loadEntities(EntityManager *entityManager)
{
    size_t loadedEntities = 0;

    rapidjson::Document document = jsonHandler_->read("data/entities.json");

    assert(document.IsObject());

    auto root = document.GetObject();
    auto entities = root["entities"].GetArray();

    for (auto &entity : entities)
    {
        Entity e = entityManager->create();

        // TODO: see if mass should be referering to physics or not
        if (!entity.HasMember("id") || !entity.HasMember("mask") || !entity.HasMember("mass"))
        {
            std::cout << "Error: id|mask|mass group missing in document" << std::endl;
            return 0;
        }

        e.id = entity["id"].GetUint();
        e.mask = entity["mask"].GetUint();

        auto e_mass = entity["mass"].GetFloat();

        if (e.id <= 0 || e.mask <= None || e_mass < 0)
        {
            std::cout << "Error: the document has invalid values" << std::endl;
            return 0;
        }

        data_.mass[e.id] = e_mass;

///     NOTE: can't have errors from reading, except type mismath ?
        if (!entity.HasMember("position"))
        {
            std::cout << "Error: missing position values in document on entity with id = " << e.id << std::endl;
        } else
        {
            data_.position[e.id].x = entity["position"]["x"].GetFloat();
            data_.position[e.id].y = entity["position"]["y"].GetFloat();
            data_.position[e.id].z = entity["position"]["z"].GetFloat();
        }

        if (!entity.HasMember("velocity"))
        {
            std::cout << "Error: missing velocity values in document on entity with id = " << e.id << std::endl;
        } else
        {
            data_.velocity[e.id].x = entity["velocity"]["x"].GetFloat();
            data_.velocity[e.id].y = entity["velocity"]["y"].GetFloat();
            data_.velocity[e.id].z = entity["velocity"]["z"].GetFloat();
        }

        if (!entity.HasMember("acceleration"))
        {
            std::cout << "Error: missing acceleration values in document on entity with id = " << e.id << std::endl;
        } else
        {
            data_.acceleration[e.id].x = entity["acceleration"]["x"].GetFloat();
            data_.acceleration[e.id].y = entity["acceleration"]["y"].GetFloat();
            data_.acceleration[e.id].z = entity["acceleration"]["z"].GetFloat();
        }

        setEntity(e);

        loadedEntities++;
    }

    jsonHandler_->close();

    return loadedEntities;
}

// TODO: improve "human langage style" when writing JSON masks
size_t Manager::loadSystems(SystemManager *systemManager)
{
    size_t loadedSystems = 0;

    rapidjson::Document document = jsonHandler_->read("data/systems.json");

    assert(document.IsObject());

    auto root = document.GetObject();
    auto systems = root["systems"].GetArray();

    // TODO: get data from JSON
    for (auto &system : systems)
    {
        size_t sys_id = 0;
        std::string sys_name;
        size_t sys_mask = None;

        if (!system.HasMember("id"))
        {
            std::cout << "Error: Could not load system id" << std::endl;
            continue;
        } else // system has an id...
        {
            sys_id = system["id"].GetUint();

            if (!system.HasMember("requiredMask"))
            {
                std::cout << "Warning: System has 'None' required mask" << std::endl;
            } else
            {
                sys_mask = system["requiredMask"].GetUint();
//                auto maskArray = system["requiredMask"].GetArray();
//                for(auto maskPart = maskArray.Begin(); maskPart != maskArray.End(); maskPart++)
//                {
//                    sys_mask += maskMapper.get(maskPart->GetString());
//                }
            }

            if (!system.HasMember("name"))
            {
                std::cout << "Warning: System has no name registered" << std::endl;
            } else
            {
                sys_name = (system["name"].GetString());
            }

            // ..so it is "Validated"

            System *s = nullptr;
            if(sys_name == "physics2D")
            {
                s = systemManager->create<Physics2D>(&data_, sys_mask);

            }
            if(sys_name == "renderer2D")
            {
                // TODO: test this ...
                s = systemManager->create<Renderer2D>(&data_, sys_mask);
            }
            else
            {
                // TODO: idem...
                s = systemManager->create<DefaultSystem>(&data_, None);
            }

            s->set_id(sys_id);
            s->setRequiredMask(sys_mask);
            s->setName(sys_name);

            setSystem(s);
        }

        loadedSystems++;
    }

    jsonHandler_->close();

    return loadedSystems;
}

void Manager::simulate(float dt)
{
    for (auto &id : sys_.reg_systems)
    {
        // update system at each index found
        sys_.systems[id]->simulate(1);
    }
}

// TODO: "erase" entity at index (i) => resert/invalid entity
void Manager::destroyEC(unsigned i)
{
    if (i <= 0) // invalid index
    {
        return;
    }

    // TODO: it do a "hole in the array" (Useless Occupied Memory)
    data_.entity[i] = data_.entity[INVALID_ENTITY];
    data_.entity[i].mask = None; // Reset mask
    data_.mass[i] = data_.mass[INVALID_ENTITY];
    data_.position[i] = data_.position[INVALID_ENTITY];
    data_.velocity[i] = data_.velocity[INVALID_ENTITY];
    data_.acceleration[i] = data_.acceleration[INVALID_ENTITY];

    data_.reg_entities.erase(i);
}

bool Manager::isValidMask(unsigned entityMask, unsigned systemMask)
{
    return ((entityMask & systemMask) == systemMask);
}

void Manager::matchSystem(System *system, std::size_t id)
{
    system->setEntityMatch(id);
}

void Manager::save(/* all E & S */)
{
    // TODO: verify data integrity ?
    jsonHandler_->querySave(sys_);
    jsonHandler_->querySave(data_);
}

void Manager::setMask(Entity entity, size_t mask)
{
    data_.entity[entity.id].mask = mask;
}

size_t Manager::mask(Entity entity)
{
    return data_.entity[entity.id].mask;
}

void Manager::setDefaultEntity()
{
    Entity default_entity = Entity();
    default_entity.id = DEFAULT;
    default_entity.mask = None;

    float default_mass = DEFAULT;

    Vector3 default_position = Vector3();
    default_position.x = DEFAULT;
    default_position.y = DEFAULT;
    default_position.z = DEFAULT;

    Vector3 default_velocity = Vector3();
    default_velocity.x = DEFAULT;
    default_velocity.y = DEFAULT;
    default_velocity.z = DEFAULT;

    Vector3 default_acceleration = Vector3();
    default_acceleration.x = DEFAULT;
    default_acceleration.y = DEFAULT;
    default_acceleration.z = DEFAULT;

    data_.entity[DEFAULT] = default_entity;
    data_.mass[DEFAULT] = default_mass;
    data_.position[DEFAULT] = default_position;
    data_.velocity[DEFAULT] = default_velocity;
    data_.acceleration[DEFAULT] = default_acceleration;
}

void Manager::setDefaultSystem()
{
    // TODO: pass data pertinent ?
    auto default_system = new DefaultSystem(&data_); // TODO: leave this to null ?
    default_system->set_id(DEFAULT);
    default_system->setRequiredMask(DEFAULT);
    default_system->setName("DEFAULT");

    sys_.systems[DEFAULT] = default_system;
}

InstanceData *Manager::data()
{
    return &data_;
}

InstanceSystem *Manager::sys()
{
    return &sys_;
}