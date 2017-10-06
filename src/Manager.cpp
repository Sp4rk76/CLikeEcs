//
// Created by Sp4rk on 03-10-17.
//

#include <System.h>
#include "Manager.h"

// TODO: custom allocation for systems ?
Manager::Manager()
{
    allocate(3200);

    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    jsonLoader_ = new JSONLoader();
}

Manager::Manager(size_t size)
{
    allocate(size);

    sys_.systems = (System **) malloc(MAX_NUMBER_OF_SYSTEMS * sizeof(System *));

    jsonLoader_ = new JSONLoader();
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

    delete jsonLoader_;
    jsonLoader_ = nullptr;
}

void Manager::allocate(unsigned size)
{
    /// for the data
    data_.size = size;
    std::cout << data_.size << std::endl;

    if (size > data_.size)
    {
        std::cout << "size > data_.size !" << std::endl;
    }

    InstanceData newData;

    const unsigned int bytes = size * (sizeof(Entity) + sizeof(float) + (3 * sizeof(Vector3)));
    newData.buffer = malloc(bytes);
    newData.size = data_.size;
    newData.capacity = size;

    newData.entity = (Entity *) (newData.buffer);
    newData.mass = (float *) (newData.entity + size);
    newData.position = (Vector3 *) (newData.mass + size);
    newData.velocity = newData.position + size; // still Vector3
    newData.acceleration = newData.velocity + size;

    data_ = newData;
}

Instance Manager::make_instance(int i)
{
    instance_.i = i;
    return instance_;
}

Instance Manager::lookup(Entity entity)
{
    // TODO: pertinent ?
    if (map_.count(entity.id) == 0)
    {
        // TODO: Put first free entity id ?
        map_[entity.id] = entity.id;
    }

    return make_instance(map_[entity.id]);
}

Entity Manager::entity(Instance instance)
{
    return data_.entity[instance.i];
}

void Manager::setEntity(Instance instance, Entity entity)
{
    data_.entity[instance.i] = entity;
}

float Manager::mass(Instance instance)
{
    return data_.mass[instance.i];
}

void Manager::setMass(Instance instance, float mass)
{
    data_.mass[instance.i] = mass;
}

Vector3 Manager::position(Instance instance)
{
    return data_.position[instance.i];
}

void Manager::setPosition(Instance instance, Vector3 position)
{
    data_.position[instance.i] = position;
}

Vector3 Manager::velocity(Instance instance)
{
    return data_.velocity[instance.i];
}

void Manager::setVelocity(Instance instance, Vector3 velocity)
{
    data_.velocity[instance.i] = velocity;
}

Vector3 Manager::acceleration(Instance instance)
{
    return data_.acceleration[instance.i];
}

void Manager::setAcceleration(Instance instance, Vector3 acceleration)
{
    data_.acceleration[instance.i] = acceleration;
}

// TODO: make JSON loading code safier
// TODO: Return an int => number of entities
// TODO: Register entities here in the future ?.. processus should be: [ (1)loadSystems/(2)loadEntities/(2.1)registerEntity-to-System ]
void Manager::loadEntities(EntityManager *entityManager)
{
    rapidjson::Document document = jsonLoader_->read("data/entities.json");

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

        instance_ = lookup(e);

        data_.entity[instance_.i] = e;

        data_.mass[instance_.i] = e_mass;

///     NOTE: can't have errors from reading, except type mismath ?
        if (!entity.HasMember("position"))
        {
            std::cout << "Error: missing position values in document on entity with id = " << e.id << std::endl;
        } else
        {
            data_.position[instance_.i].x = entity["position"]["x"].GetFloat();
            data_.position[instance_.i].y = entity["position"]["y"].GetFloat();
            data_.position[instance_.i].z = entity["position"]["z"].GetFloat();
        }

        if (!entity.HasMember("velocity"))
        {
            std::cout << "Error: missing velocity values in document on entity with id = " << e.id << std::endl;
        } else
        {
            data_.position[instance_.i].x = entity["velocity"]["x"].GetFloat();
            data_.position[instance_.i].y = entity["velocity"]["y"].GetFloat();
            data_.position[instance_.i].z = entity["velocity"]["z"].GetFloat();
        }

        if (!entity.HasMember("acceleration"))
        {
            std::cout << "Error: missing acceleration values in document on entity with id = " << e.id << std::endl;
        } else
        {
            data_.acceleration[instance_.i].x = entity["acceleration"]["x"].GetFloat();
            data_.acceleration[instance_.i].y = entity["acceleration"]["y"].GetFloat();
            data_.acceleration[instance_.i].z = entity["acceleration"]["z"].GetFloat();
        }

        /// Non-bloquant
        if (!entity.HasMember("name"))
        {
            std::cout << "Entity number " << e.id << " has no name." << std::endl;
        } else
        {
            // TODO: declare above first
            auto name = entity["name"].GetString();
            std::cout << "id: " << e.id << ", " << "name: " << name << std::endl;
        }
    }

    jsonLoader_->close();
}

// TODO: return an integer => number of systems
void Manager::loadSystems()
{
    rapidjson::Document document = jsonLoader_->read("data/systems.json");

    assert(document.IsObject());

    auto root = document.GetObject();
    auto systems = root["systems"].GetArray();

    // TODO: get data from JSON
    for (auto &system : systems)
    {
        size_t sys_id = 0;
        const char *sys_name = "";
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
                sys_name = system["name"].GetString();
            }

            // ..so it is "Validated"
            sys_.id.insert(sys_id);
            // TODO: insert name ?
            sys_.systems[sys_id] = new System();
            sys_.systems[sys_id]->setRequiredMask(sys_mask);
            sys_.systems[sys_id]->setName(sys_name);

            Entity e;

            // get all entities
            for (auto &it : map_)
            {
                e.id = map_[it.second];
                instance_ = lookup(e);
                e = data_.entity[instance_.i];

                if (isValidMask(e.mask, sys_.systems[sys_id]->requiredMask()))
                {
                    std::cout << "----------" << std::endl;
                    std::cout << "REGISTERED !" << std::endl;
                    std::cout << "sEntity.id: " << e.id << std::endl;
                    std::cout << "sEntity.mask: " << e.mask << std::endl;
                    std::cout << "sRequiredMask: " << sys_.systems[sys_id]->requiredMask() << std::endl;
                    std::cout << "sName: " << sys_.systems[sys_id]->name() << std::endl;
                    matchSystem(sys_.systems[sys_id], e.id);
                }

            }
        }
    }

    jsonLoader_->close();
}

// TODO: simulate only with registered entities
void Manager::simulate(float dt)
{
    // for each system set
    // update system at each index found

    for (auto &id : sys_.id)
    {

        std::cout << "SYS_ID" << id << std::endl;
        sys_.systems[id]->simulate();
    }

//    std::cout << "data size: " << data_.size << std::endl;
//    std::cout << "map size: " << map_.size() << std::endl;
//    for (auto &it : map_)
//    {
//        std::cout << "MAPPED index = " << it.second << std::endl;
//
//        std::cout << "Acceleration(x) from entity " << it.first << ": " << data_.acceleration[it.second].x << std::endl;
//
//        data_.velocity[it.second] += (data_.acceleration[it.second]);
//        data_.position[it.second] += (data_.velocity[it.second]);
//
//        std::cout << "Simulate VELOCITY.X (e=" << data_.entity[it.second].index() << "): "
//                  << data_.velocity[it.second].x << std::endl;
//        std::cout << "Simulate POSITION.X (e=" << data_.entity[it.second].index() << "): "
//                  << data_.position[it.second].x << std::endl;
//        std::cout << "map contains (" << it.first << " ; " << it.second << ")" << std::endl;
//    }
}

void Manager::destroy(unsigned i)
{
    if (i <= 0) // invalid index
    {
        return;
    }

    unsigned last = data_.size - 1;
    std::cout << "last 'entity' to swap (id): " << last << std::endl;

    Entity entity = data_.entity[i]; // or Entity
    //Entity lastEntity = data_.entity[last]; // or Entity

    data_.entity[i] = data_.entity[last];
    data_.mass[i] = data_.mass[last];
    data_.position[i] = data_.position[last];
    data_.velocity[i] = data_.velocity[last];
    data_.acceleration[i] = data_.acceleration[last];

    std::cout << "destroy entity id = " << entity.id << std::endl;

    /// ?
    ///map_[lastEntity.id] = i;
    map_.erase(entity.id);

    std::cout << "New MAP size: " << map_.size() << std::endl;

    if (data_.size > 0)
    {
        --data_.size; // or (--_n)
    }
}

bool Manager::isValidMask(unsigned entityMask, unsigned systemMask)
{
    return ((entityMask & systemMask) == systemMask);
}

void Manager::testValues()
{
    // TODO: see if it keeps components alive !
    // NOTE: destroy 1st entity and only leave 3rd entity
    Instance i1 = lookup(data_.entity[1]);
    Instance i2 = lookup(data_.entity[2]);
    Instance i3 = lookup(data_.entity[3]);

    std::cout << position(i1).x << std::endl; // return 50 (from file)
    //manager->destroy(i1.i); // destroy !
    //std::cout << manager->position(i1).x << std::endl; // return 0 (default)
    std::cout << position(i2).x << std::endl; // return 0 (default)
    std::cout << position(i3).x << std::endl;
}

void Manager::matchSystem(System *system, std::size_t id)
{
    system->setEntityMatch(id);
}