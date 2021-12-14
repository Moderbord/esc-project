#include <iostream>

#include "world.h"
#include "entity_handle.h"

void test(World& world)
{

    EntityHandle e2 = world.create_entity();

    e2.add_component<Transform>(3, 4);
}

int main()
{
    EntityManager emgr = EntityManager();
    World world = World(&emgr);
    world.init();

    test(world);

    EntityHandle e1 = world.create_entity();

    ComponentHandle<Transform> h1 = world.component_handle<Transform>({ 1 });
    h1->x += 5;
    printf("End of main\n");
    


}