#include <managers/Manager.h>
#include <systems/Physics2D.h>

int main()
{
    auto entityManager = new EntityManager();
    auto systemManager = new SystemManager();
    auto manager = new Manager(10);

    size_t loaded_entities = manager->loadEntities(entityManager);
    std::cout << "Loaded Entities: " << loaded_entities << std::endl;

    size_t loaded_systems = manager->loadSystems(systemManager);
    std::cout << "Loaded Systems: " << loaded_systems << std::endl;

    /// TEST Systems
    auto system = systemManager->create<Physics2D>(manager->data(), Position); // id & mask defined in
    system->setName("CustomSystem");
    manager->setSystem(system);

    for(auto &id : manager->sys()->reg_systems)
    {
        std::cout << "System Name : " << manager->sys()->systems[id]->name() << std::endl;
    }

    // TODO: Modify destroyEC method to properly delete an entity
    manager->destroyEC(1);
//    manager->destroyEC(2);
    manager->destroyEC(3);

    /// NOTE: the simulation can alterate the data (saved)
    manager->simulate();
    manager->save();



//    auto toto = entityManager->create(14);
//    auto new_instance_id = manager->generateInstanceId();
//    manager->setEntityInstance(toto.id, new_instance_id);
//    manager->setEntity(new_instance_id, toto);
//    manager->destroyEC(4);

    for(auto& x : manager->entity_instances)
    {
        std::cout << "E = " << x.first << " ; " << " I = " << x.second << std::endl;
    }

    std::cout << "Instance_IDs | ";
    for(auto& op : manager->instance_ids)
    {
        std::cout << op << " | ";
    }
    std::cout << std::endl;

    return 0;
}

// TODO: when setting a new Entity instance in map, check if it already exists !