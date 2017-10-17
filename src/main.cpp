#include <Manager.h>
#include <Physics2D.h>

int main()
{
    auto entityManager = new EntityManager();
    auto systemManager = new SystemManager();
    auto manager = new Manager(5);

    size_t loaded_entities = manager->loadEntities(entityManager);
    std::cout << "Loaded Entities: " << loaded_entities << std::endl;

    size_t loaded_systems = manager->loadSystems(systemManager);
    std::cout << "Loaded Systems: " << loaded_systems << std::endl;

    /// TEST Systems
    auto system = systemManager->create<Physics2D>(manager->data(), Position); // id & mask defined in
    system->setName("CustomSystem");
    manager->setSystem(system);

    for(int i = 0; i < manager->sys()->reg_systems.size(); i++)
    {
        std::cout << "System Name : " << manager->sys()->systems[i]->name() << std::endl;
    }

    auto e = entityManager->create(2);
    manager->setEntity(e);

    manager->simulate();

    manager->save();

    return 0;
}



















































/// Debug !
//std::cout << "e1 (id)= " << e1.id << std::endl;
//std::cout << "e1 (i) = " << e1.index() << std::endl;
//std::cout << "e2 (id)= " << e2.id << std::endl;
//std::cout << "e2 (i) = " << e2.index() << std::endl;

//    Manager componentManager;
//    EntityManager entityManager;
//
//    // Buffer Size && Allocation(for component system)
//    componentManager.allocate(1500 + 1); // (size => max_entities_to_allocate - 1) (mandatory)
//
//    for(int cpt = 1; cpt < componentManager.data_.size - 1; cpt++) // <=> (0 < data_.size - 1)
//    {
//        Entity e = entityManager.create();
//
//        Instance instance = componentManager.lookup(e);
//
//        auto v3 = Vector3();
//        v3.x = 1; v3.y = 1; v3.z = 1;
//        v3 += 4;
//
//        componentManager.setEntity(instance, e);
//        componentManager.setMass(instance, (cpt * 5));
//        componentManager.setPosition(instance, v3);
//        componentManager.setVelocity(instance, v3);
//        componentManager.setAcceleration(instance, v3);
//
//        cout << "Entity " << e.id
//             << " has mass = " << componentManager.mass(instance)
//             << " with p.x = " << componentManager.position(instance).x
//             << ", v.x = " << componentManager.velocity(instance).x
//             << ", a.x = " << componentManager.acceleration(instance).x << endl;
//    }
//
//
//    // last entity
//    Entity e = entityManager.create();
//
//    Instance instance = componentManager.lookup(e);
//
//    cout << "E.ID => " << e.id << endl;
//
//    Vector3 vLast = Vector3();
//    vLast.x = 2; vLast.y = 2; vLast.z = 2;
//
//    componentManager.setEntity(instance, e);
//    componentManager.setMass(instance, (50));
//    componentManager.setPosition(instance, vLast);
//    componentManager.setVelocity(instance, vLast);
//    componentManager.setAcceleration(instance, vLast);
//
//    cout << "Entity " << e.id
//         << " has mass = " << componentManager.mass(instance)
//         << " with p.x = " << componentManager.position(instance).x
//         << ", v.x = " << componentManager.velocity(instance).x
//         << ", a.x = " << componentManager.acceleration(instance).x << endl;
//    // end last entity
//
////    componentManager.destroy(instance.i - 10);
//
//    componentManager.simulate();
//
//
//
//    cout << "SIZE => " << componentManager.data_.size << endl;

