//
// Created by Sp4rk on 03-10-17.
//

#include "System.h"

System::System()
{
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

void System::loadEntities(EntityManager &entityManager)
{
    rapidjson::Document document = jsonLoader_->read("data/entities.json");

    assert(document.IsObject());

    auto root = document.GetObject();
    auto entities = root["entities"].GetArray();

    for (auto &entity : entities)
    {
        auto id = entity["id"].GetInt();
        auto name = entity["name"].GetString();
        std::cout << "id: " << id << ", " << "name: " << name << std::endl;

        Entity e = entityManager.create();

        e.id = (unsigned) entity["id"].GetInt();
        instance_ = lookup(e);

        setEntity(instance_, e);
    }

    jsonLoader_->close();
}

void System::loadComponents()
{
    Entity e; // fictive entity

    rapidjson::Document document = jsonLoader_->read("data/components.json");

    assert(document.IsObject());

    auto components = document["components"].GetArray();

    for (auto &component : components)
    {
        auto componentId = component["id"].GetInt();

        auto entityId = component["entity"]["id"].GetInt();
        auto entityName = component["entity"]["name"].GetString();

        e.id = (unsigned) entityId; // fictive entity
        instance_ = lookup(e);

        data_.mass[instance_.i] = component["mass"].GetFloat();

        data_.position[instance_.i].x = component["position"]["x"].GetFloat();
        data_.position[instance_.i].y = component["position"]["y"].GetFloat();
        data_.position[instance_.i].z = component["position"]["z"].GetFloat();

        data_.velocity[instance_.i].x = component["velocity"]["x"].GetFloat();
        data_.velocity[instance_.i].y = component["velocity"]["y"].GetFloat();
        data_.velocity[instance_.i].z = component["velocity"]["z"].GetFloat();

        data_.acceleration[instance_.i].x = component["acceleration"]["x"].GetFloat();
        data_.acceleration[instance_.i].y = component["acceleration"]["y"].GetFloat();
        data_.acceleration[instance_.i].z = component["acceleration"]["z"].GetFloat();
    }

    jsonLoader_->close();
}

void System::simulate(float dt)
{
    std::cout << data_.size << std::endl;
    std::cout << "map : " << map_.size() << std::endl;
    for (unsigned j = 1; j < data_.size; j++)
    {
        data_.velocity[j] += (data_.acceleration[j]);
        data_.position[j] += (data_.velocity[j]);
        std::cout << "I = " << j << std::endl;
        std::cout << "Simulate VELOCITY.X (e=" << data_.entity[j].index() << "): " << data_.velocity[j].x
                  << std::endl;
        std::cout << "Simulate POSITION.X (e=" << data_.entity[j].index() << "): " << data_.position[j].x
                  << std::endl;
    }
}

void System::destroy(unsigned i)
{
    unsigned last = data_.size - 1;
    std::cout << "last 'entity' to swap (id): " << last << std::endl;

    unsigned e = data_.entity[i].id; // or Entity
    unsigned last_e = data_.entity[last].id; // or Entity

    data_.entity[i] = data_.entity[last];
    data_.mass[i] = data_.mass[last];
    data_.position[i] = data_.position[last];
    data_.velocity[i] = data_.velocity[last];
    data_.acceleration[i] = data_.acceleration[last];

    map_[last_e] = i;
    map_.erase(e);

    std::cout << "New MAP size: " << map_.size() << std::endl;

    --data_.size; // or (--_n)
}
