//
// Created by Sp4rk on 03-10-17.
//

#include <System.h>
#include <fstream>
#include "Manager.h"

// TODO: custom allocation for systems ?
Manager::Manager()
{
    allocate(3200);

    setDefaultEntity();

    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    jsonHandler_ = new JSONHandler();
}

Manager::Manager(size_t size)
{
    allocate(size);

    setDefaultEntity();

    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    jsonHandler_ = new JSONHandler();
}

Manager::~Manager()
{
    for (auto n : sys_.id)
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

    InstanceData newData;

    const unsigned int bytes = size * (sizeof(Entity) + sizeof(float) + (3 * sizeof(Vector3)));
    newData.buffer = malloc(bytes);
    newData.size = data_.size;

    newData.entity = (Entity *) (newData.buffer);
    newData.mass = (float *) (newData.entity + size);
    newData.position = (Vector3 *) (newData.mass + size);
    newData.velocity = newData.position + size; // still Vector3
    newData.acceleration = newData.velocity + size;

    data_ = newData;
}

//Entity Manager::make_instance(int i)
//{
//    instance_.i = i;
//    return instance_;
//}

void Manager::register_as(Entity entity)
{
    // TODO: pertinent ?
    if (data_.reg_entities.count(entity.id) == 0)
    {
        // TODO: Put first free entity id ?
        data_.reg_entities.insert(entity.id);
    }
}

Entity Manager::entity(Entity entity)
{
    return data_.entity[entity.id];
}

void Manager::setEntity(Entity entity)
{
    data_.entity[entity.id] = entity;
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

void Manager::setPosition(Entity entity, Vector3 position)
{
    data_.position[entity.id] = position;
}

Vector3 Manager::velocity(Entity entity)
{
    return data_.velocity[entity.id];
}

void Manager::setVelocity(Entity entity, Vector3 velocity)
{
    data_.velocity[entity.id] = velocity;
}

Vector3 Manager::acceleration(Entity entity)
{
    return data_.acceleration[entity.id];
}

void Manager::setAcceleration(Entity entity, Vector3 acceleration)
{
    data_.acceleration[entity.id] = acceleration;
}

// TODO: make JSON loading code safier
// TODO: Return an int => number of entities
// TODO: Register entities here in the future ?.. processus should be: [ (1)loadSystems/(2)loadEntities/(2.1)registerEntity-to-System ]
void Manager::loadEntities(EntityManager *entityManager)
{
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
            return;
        }

        e.id = entity["id"].GetUint();
        e.mask = entity["mask"].GetUint();

        auto e_mass = entity["mass"].GetFloat();

        if (e.id <= 0 || e.mask <= None || e_mass < 0)
        {
            std::cout << "Error: the document has invalid values" << std::endl;
            return;
        }

        data_.entity[e.id] = e;

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

        register_as(e);
    }

    jsonHandler_->close();
}

// TODO: return an integer => number of systems
void Manager::loadSystems()
{
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
            }

            if (!system.HasMember("name"))
            {
                std::cout << "Warning: System has no name registered" << std::endl;
            } else
            {
                sys_name = (system["name"].GetString());
            }

            // ..so it is "Validated"
            sys_.id.insert(sys_id);
            // TODO: insert name ?
            sys_.systems[sys_id] = new System();
            sys_.systems[sys_id]->setRequiredMask(sys_mask);
            sys_.systems[sys_id]->setName(sys_name);

            Entity e;

            // get all entities
            for (auto &reg_id : data_.reg_entities)
            {
                e.id = *(data_.reg_entities.find(reg_id));
                e = data_.entity[e.id];

                if (isValidMask(e.mask, sys_.systems[sys_id]->requiredMask()))
                {
                    std::cout << "Register entity " << e.id << "(" << e.mask << ")" << " to System '"
                              << sys_.systems[sys_id]->name() << "'(" << sys_.systems[sys_id]->requiredMask() << ")"
                              << std::endl;
                    matchSystem(sys_.systems[sys_id], e.id);
                }
            }
        }
    }

    jsonHandler_->close();
}

// TODO: simulate only with registered entities
void Manager::simulate(float dt)
{
    // for each system set
    for (auto &id : sys_.id)
    {
        // update system at each index found
        std::cout << "SYS_ID" << id << std::endl;
        sys_.systems[id]->simulate();
    }
}

// TODO: "erase" entity at index (i) => resert/invalid entity
void Manager::destroy(unsigned i)
{
    if (i <= 0) // invalid index
    {
        return;
    }

    data_.entity[i] = data_.entity[INVALID_ENTITY];
    data_.position[i] = data_.position[INVALID_ENTITY];
    data_.velocity[i] = data_.velocity[INVALID_ENTITY];
    data_.acceleration[i] = data_.acceleration[INVALID_ENTITY];

    data_.reg_entities.erase(i);
}

bool Manager::isValidMask(unsigned entityMask, unsigned systemMask)
{
    return ((entityMask & systemMask) == systemMask);
}

void Manager::testValues()
{
    // TODO: see if it keeps components alive !
    // NOTE: destroy 1st entity and only leave 3rd entity
//    Instance i1 = lookup(data_.entity[1]);
//    Instance i2 = lookup(data_.entity[2]);
//    Instance i3 = lookup(data_.entity[3]);
//
//    std::cout << position(i1).x << std::endl; // return 50 (from file)
//    //manager->destroy(i1.i); // destroy !
//    //std::cout << manager->position(i1).x << std::endl; // return 0 (default)
//    std::cout << position(i2).x << std::endl; // return 0 (default)
//    std::cout << position(i3).x << std::endl;
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
    default_entity.id = INVALID_ENTITY;
    default_entity.mask = None;

    Vector3 default_position = Vector3();
    default_position.x = DEFAULT_POSITION;
    default_position.y = DEFAULT_POSITION;
    default_position.z = DEFAULT_POSITION;

    Vector3 default_velocity = Vector3();
    default_velocity.x = DEFAULT_VELOCITY;
    default_velocity.y = DEFAULT_VELOCITY;
    default_velocity.z = DEFAULT_VELOCITY;

    Vector3 default_acceleration = Vector3();
    default_acceleration.x = DEFAULT_ACCELERATION;
    default_acceleration.y = DEFAULT_ACCELERATION;
    default_acceleration.z = DEFAULT_ACCELERATION;

    setEntity(default_entity);
    setPosition(default_entity, default_position);
    setVelocity(default_entity, default_velocity);
    setAcceleration(default_entity, default_acceleration);
}
