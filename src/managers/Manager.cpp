//
// Created by Sp4rk on 03-10-17.
//

#include <systems/Physics2D.h>
#include <systems/DefaultSystem.h>
#include <systems/Renderer2D.h>
#include "managers/Manager.h"

Manager::Manager()
{
    allocate(1 << 13); // 8192

    jsonHandler_ = new JSONHandler();
}

Manager::Manager(size_t size)
{
    allocate(size);

    jsonHandler_ = new JSONHandler();
}

Manager::~Manager()
{
    for (auto id : sys_.reg_systems)
    {
        delete sys_.systems[id];
        sys_.systems[id] = nullptr;
    }

    delete sys_.systems;
    sys_.systems = nullptr;

    free(data_.buffer);

    jsonHandler_->free();
    delete jsonHandler_;
    jsonHandler_ = nullptr;
}

void Manager::allocate(unsigned size)
{
    // System allocation & initialization
    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    // Data allocation & initialization
    data_.n = 0;
    data_.size = size;
    const unsigned int bytes = (size * (sizeof(Entity)
                                        + sizeof(float)
                                        + (3 * sizeof(Vector3))
                                        + (2 * sizeof(glm::mat4))
                                        + (4 * sizeof(int))))
                               + (2 * sizeof(size_t));
    data_.buffer = malloc(bytes);
    data_.entity = (Entity *) (data_.buffer);
    data_.mass = (float *) (data_.entity + size);
    data_.position = (Vector3 *) (data_.mass + size);
    data_.velocity = data_.position + size; // still Vector3
    data_.acceleration = data_.velocity + size;
    data_.local = (glm::mat4 *) (data_.acceleration + size);
    data_.world = data_.local + size;
    data_.parent = (int *) (data_.local + size);
    data_.first_child = data_.parent + size;
    data_.next_sibling = data_.first_child + size;
    data_.prev_sibling = data_.next_sibling + size;
}

void Manager::queryRegistration(Entity &entity)
{
    for (auto &system_id : sys_.reg_systems)
    {
        auto &system = sys_.systems[system_id];

        if (isValidMask(entity.mask, system->requiredMask()))
        {
            // TODO: unset this (only here for debug purposes)
            std::cout << "Register entity " << entity.id << "(" << entity.mask << ")" << " to System '"
                      << system->name() << "'(" << system->requiredMask() << ")"
                      << std::endl;

            /// IMPORTANT: registered id is not entity_i, but INSTANCE_ID for the concerned entity
            system->setEntityMatch(lookup(entity.id));
        }
    }
}

void Manager::queryRegistration(System *system)
{
    sys_.reg_systems.insert(system->id());

    for (size_t instance_id = 0; instance_id < data_.n; ++instance_id)
    {
        auto &entity = data_.entity[instance_id];

        if (isValidMask(entity.mask, system->requiredMask()))
        {
            // TODO: unset this (only here for debug purposes)
            std::cout << "Register entity " << entity.id << "(" << entity.mask << ")" << " to System '"
                      << system->name() << "'(" << system->requiredMask() << ")"
                      << std::endl;

            /// IMPORTANT: register instance_id !!!
            system->setEntityMatch(instance_id);
        }
    }
}

// Get instance(id) for a given entity(id)
size_t Manager::lookup(size_t entity_id)
{
    return entity_instances[entity_id];
}

Entity Manager::entity(size_t instance_id)
{
    return data_.entity[instance_id];
}

float Manager::mass(size_t instance_id)
{
    return data_.mass[instance_id];
}

Vector3 Manager::position(size_t instance_id)
{
    return data_.position[instance_id];
}

Vector3 Manager::velocity(size_t instance_id)
{
    return data_.velocity[instance_id];
}

Vector3 Manager::acceleration(size_t instance_id)
{
    return data_.acceleration[instance_id];
}

/// NOTE: It is possible to SET an Entity since we have its ID and MASK
void Manager::setEntity(int instance_id, Entity &entity)
{
    setEntityInstance(entity.id, instance_id);

    data_.entity[instance_id] = entity;

    data_.n++; // (used_instances + created_instance);

    queryRegistration(entity);
}

void Manager::setMass(size_t instance_id, float &mass)
{
    data_.mass[instance_id] = mass;
}

void Manager::setPosition(size_t instance_id, Vector3 &position)
{
    data_.position[instance_id] = position;
}

void Manager::setVelocity(size_t instance_id, Vector3 &velocity)
{
    data_.velocity[instance_id] = velocity;
}

void Manager::setAcceleration(size_t instance_id, Vector3 &acceleration)
{
    data_.acceleration[instance_id] = acceleration;
}

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

        if (!entity.HasMember("id") || !entity.HasMember("mask") || !entity.HasMember("mass"))
        {
            std::cout << "Error: id|mask|mass group missing in document" << std::endl;
            return 0;
        }

        e.id = entity["id"].GetUint();
        e.mask = entity["mask"].GetUint();

        int generated_id = generateInstanceId();

        auto e_mass = entity["mass"].GetFloat();

        if (e.id <= 0 || e.mask <= None || e_mass < 0)
        {
            std::cout << "Error: the document has invalid values" << std::endl;
            return 0;
        }

        setMass((size_t) generated_id, e_mass);

///     NOTE: can't have errors from reading, except type mismath ?
        if (!entity.HasMember("position"))
        {
            std::cout << "Error: missing position values in document on entity with id (instance) = " << generated_id
                      << std::endl;
        } else
        {
            data_.position[generated_id].x = entity["position"]["x"].GetFloat();
            data_.position[generated_id].y = entity["position"]["y"].GetFloat();
            data_.position[generated_id].z = entity["position"]["z"].GetFloat();
        }

        if (!entity.HasMember("velocity"))
        {
            std::cout << "Error: missing velocity values in document on entity with id (instance) = " << generated_id
                      << std::endl;
        } else
        {
            data_.velocity[generated_id].x = entity["velocity"]["x"].GetFloat();
            data_.velocity[generated_id].y = entity["velocity"]["y"].GetFloat();
            data_.velocity[generated_id].z = entity["velocity"]["z"].GetFloat();
        }

        if (!entity.HasMember("acceleration"))
        {
            std::cout << "Error: missing acceleration values in document on entity with id (instance) = "
                      << generated_id << std::endl;
        } else
        {
            data_.acceleration[generated_id].x = entity["acceleration"]["x"].GetFloat();
            data_.acceleration[generated_id].y = entity["acceleration"]["y"].GetFloat();
            data_.acceleration[generated_id].z = entity["acceleration"]["z"].GetFloat();
        }

        if (!entity.HasMember("parent"))
        {
            std::cout << "Error: missing parent value in document on entity with id (instance) = " << generated_id
                      << std::endl;
        } else
        {
            data_.parent[generated_id] = entity["parent"].GetInt();
        }

        if (!entity.HasMember("first-child"))
        {
            std::cout << "Error: missing first-child value in document on entity with id (instance) = " << generated_id
                      << std::endl;
        } else
        {
            data_.first_child[generated_id] = entity["first-child"].GetInt();
        }

        if (!entity.HasMember("next-sibling"))
        {
            std::cout << "Error: missing next-sibling value in document on entity with id (instance) = " << generated_id
                      << std::endl;
        } else
        {
            data_.next_sibling[generated_id] = entity["next-sibling"].GetInt();
        }

        if (!entity.HasMember("prev-sibling"))
        {
            std::cout << "Error: missing prev-sibling value in document on entity with id (instance) = " << generated_id
                      << std::endl;
        } else
        {
            data_.prev_sibling[generated_id] = entity["prev-sibling"].GetInt();
        }

        setEntity(generated_id, e);

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
            }

            if (!system.HasMember("name"))
            {
                std::cout << "Warning: System has no name registered" << std::endl;
            } else
            {
                sys_name = (system["name"].GetString());
            }

            // TODO: can be improved ? #ugly_code
            System *s = nullptr;
            if (sys_name == "physics2D")
            {
                s = systemManager->create<Physics2D>(&data_, sys_mask);

            }
            if (sys_name == "renderer2D")
            {
                s = systemManager->create<Renderer2D>(&data_, sys_mask);
            } else
            {
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

System *Manager::system(System *system)
{
    return sys_.systems[system->id()];
}

void Manager::setSystem(System *system)
{
    system->setData(&data_);

    sys_.systems[system->id()] = system;

    system->start();

    queryRegistration(system);
}

void Manager::simulate(float dt)
{
    for (auto &id : sys_.reg_systems)
    {
        // update system at each index found
        sys_.systems[id]->simulate(dt);
    }
}

void Manager::destroyEC(size_t entity_id)
{
    if (entity_id <= 0)
    {
        return;
    }

    // Get instance_id
    size_t id = lookup(entity_id);

    unsigned last = data_.n - 1;
    Entity e = data_.entity[id];
    Entity last_entity = data_.entity[last];

    data_.entity[id] = data_.entity[last];
    data_.mass[id] = data_.mass[last];
    data_.position[id] = data_.position[last];
    data_.velocity[id] = data_.velocity[last];
    data_.acceleration[id] = data_.acceleration[last];

    /// NOTE: erase entity (instance id) which has been moved to the end of the array
    instance_ids.erase(entity_instances[last_entity.id]);

    // TODO: put this into a function ??
    // check if replacement entity (instance) is compatible with system
    for (auto &system_id : sys_.reg_systems)
    {
        auto &system = sys_.systems[system_id];

        std::cout << "DESTROY : for E = " << entity_id << " we have (replaced) I = " << id << std::endl;

        if (!isValidMask(data_.entity[id].mask, system->requiredMask()))
        {
            /// Replaced entity does not match system mask (instance is not KEEPED in system "matches_" list)
            system->unsetEntityMatch(id);
        } else
        {
            system->setEntityMatch(id);
        }

        /// UnRegister destroyed Entity (instance) from all potential systems
        system->unsetEntityMatch(entity_instances[last_entity.id]);
    }

    entity_instances[last_entity.id] = id;
    entity_instances.erase(e.id);

    --data_.n;
}

/// TODO: id >= 0 check ?
void Manager::destroyS(size_t id) // System id or system instance id ?
{
    sys_.reg_systems.erase(id);

    /// No need to unRegister entities first.
    sys_.systems[id] = nullptr;
}

bool Manager::isValidMask(unsigned entityMask, unsigned systemMask)
{
    return ((entityMask & systemMask) == systemMask);
}

void Manager::save(/* all E & S */)
{
    // TODO: verify data integrity ?
    jsonHandler_->querySave(sys_);
    jsonHandler_->querySave(data_);
}

InstanceData *Manager::data()
{
    return &data_;
}

InstanceSystem *Manager::sys()
{
    return &sys_;
}

// TODO: remake this method (too slow because of "n² complexity")
int Manager::generateInstanceId()
{
    int instance_ids_size = instance_ids.size();

    for (int i = 0; i < instance_ids_size; i++)
    {
        if (!instance_ids.count(i))
        {
            instance_ids.insert(i);
            return i;
        } else
        {
            std::cout << "Info: Could not generate instance id (already exists)" << std::endl;
        }
    }

    instance_ids.insert(instance_ids_size);

    /// NOTE: var is assigned by VALUE, so it is not affected by the size modification from the line above, ...
    return instance_ids_size;
}

void Manager::setEntityInstance(size_t entity_id, int instance_id)
{
    entity_instances[entity_id] = (size_t) instance_id;
    // TODO: track instance IDs
    instance_ids.insert(instance_id);
}