//
// Created by Sp4rk on 03-10-17.
//

#include "System.h"

System::System()
{
    Vector3 t;
    jsonLoader_ = new JSONLoader();
}

System::~System()
{
    free(data_.buffer);

    delete jsonLoader_;
    jsonLoader_ = nullptr;
}

void System::allocate(unsigned size)
{
    data_.size = size;
    std::cout << data_.size << std::endl;

    if (size > data_.size)
    {
        std::cout << "size > data_.size !" << std::endl;
    }

    InstanceData newData_;

    const unsigned int bytes = size * (sizeof(Entity) + sizeof(float) + (3 * sizeof(Vector3)));
    newData_.buffer = malloc(bytes);
    newData_.size = data_.size;
    newData_.capacity = size;

    newData_.entity = (Entity *) (newData_.buffer);
    newData_.mass = (float *) (newData_.entity + size);
    newData_.position = (Vector3 *) (newData_.mass + size);
    newData_.velocity = newData_.position + size; // still Vector3
    newData_.acceleration = newData_.velocity + size;

    data_ = newData_;
}

Instance System::make_instance(int i)
{
    instance_.i = i;
    return instance_;
}

Instance System::lookup(Entity entity)
{
    // TODO: pertinent ?
    if (map_.count(entity.id) == 0)
    {
        // TODO: Put first free entity id ?
        map_[entity.id] = entity.id;
    }

    std::cout << "we map: (e ; i) as " << "(" << entity.id << " ; " << map_[entity.id] << std::endl;

    return make_instance(map_[entity.id]);
}

Entity System::entity(Instance instance)
{
    return data_.entity[instance.i];
}

void System::setEntity(Instance instance, Entity entity)
{
    data_.entity[instance.i] = entity;
}

float System::mass(Instance instance)
{
    return data_.mass[instance.i];
}

void System::setMass(Instance instance, float mass)
{
    data_.mass[instance.i] = mass;
}

Vector3 System::position(Instance instance)
{
    return data_.position[instance.i];
}

void System::setPosition(Instance instance, Vector3 position)
{
    data_.position[instance.i] = position;
}

Vector3 System::velocity(Instance instance)
{
    return data_.velocity[instance.i];
}

void System::setVelocity(Instance instance, Vector3 velocity)
{
    data_.velocity[instance.i] = velocity;
}

Vector3 System::acceleration(Instance instance)
{
    return data_.acceleration[instance.i];
}

void System::setAcceleration(Instance instance, Vector3 acceleration)
{
    data_.acceleration[instance.i] = acceleration;
}

// TODO: make JSON loading code safier
void System::loadEntities(EntityManager &entityManager)
{
    rapidjson::Document document = jsonLoader_->read("data/entities.json");

    assert(document.IsObject());

    auto root = document.GetObject();
    auto entities = root["entities"].GetArray();

    for (auto &entity : entities)
    {
        Entity e = entityManager.create();
        e.id = (unsigned int) entity["id"].GetInt();

        auto e_mass = entity["mass"].GetFloat();

        // TODO: bool function, detect invalid data for each entity
        if (e.id <= 0 || e_mass < 0)
        {
            std::cout << "Error: the document has invalid values" << std::endl;
            return;
        }

        instance_ = lookup(e);

        data_.entity[instance_.i] = e;

        data_.mass[instance_.i] = e_mass;

///     NOTE: can't have errors from reading, except type mismath ?
        if (entity.HasMember("position"))
        {
            data_.position[instance_.i].x = entity["position"]["x"].GetFloat();
            data_.position[instance_.i].y = entity["position"]["y"].GetFloat();
            data_.position[instance_.i].z = entity["position"]["z"].GetFloat();
        }

        if (entity.HasMember("velocity"))
        {
            data_.position[instance_.i].x = entity["velocity"]["x"].GetFloat();
            data_.position[instance_.i].y = entity["velocity"]["y"].GetFloat();
            data_.position[instance_.i].z = entity["velocity"]["z"].GetFloat();
        }

        if (entity.HasMember("acceleration"))
        {
            data_.acceleration[instance_.i].x = entity["acceleration"]["x"].GetFloat();
            data_.acceleration[instance_.i].y = entity["acceleration"]["y"].GetFloat();
            data_.acceleration[instance_.i].z = entity["acceleration"]["z"].GetFloat();

        }

        auto name = entity["name"].GetString();
        std::cout << "id: " << e.id << ", " << "name: " << name << std::endl;
    }

    jsonLoader_->close();
}

// TODO: simulate only with registered entities
void System::simulate(float dt)
{





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

void System::destroy(unsigned i)
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

// TODO: Implement this functionnality ?
bool System::isValid(rapidjson::Document document)
{
    return false;
}

bool System::isValidMask(unsigned entityMask, unsigned systemMask)
{
    return ((entityMask & systemMask) == systemMask);
}
