#include <EntityManager.h>
#include <System.h>

int main()
{
    auto entityManager = new EntityManager();
    auto system = new System();

    // allocate nb of registered entities or more ?
    system->allocate(3200);

    system->loadEntities(*entityManager);

    // TODO: see if it keeps components alive !
    // NOTE: destroy 1st entity and only leave 3rd entity
    Instance i1 = system->lookup(system->data_.entity[1]);
    Instance i2 = system->lookup(system->data_.entity[2]);
    Instance i3 = system->lookup(system->data_.entity[3]);

    std::cout << system->position(i1).x << std::endl; // return 50 (from file)
    //system->destroy(i1.i); // destroy !
    //std::cout << system->position(i1).x << std::endl; // return 0 (default)
    std::cout << system->position(i2).x << std::endl; // return 0 (default)
    std::cout << system->position(i3).x << std::endl;

    system->simulate();

    return 0;
}



















































/// Debug !
//std::cout << "e1 (id)= " << e1.id << std::endl;
//std::cout << "e1 (i) = " << e1.index() << std::endl;
//std::cout << "e2 (id)= " << e2.id << std::endl;
//std::cout << "e2 (i) = " << e2.index() << std::endl;

//    System componentManager;
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

