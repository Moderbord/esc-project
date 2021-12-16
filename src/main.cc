#include <iostream>
#include "world.h"
#include "component.h"
#include "entity_handle.h"
#include "sys_physics.h"

int main()
{
    // Pre initiations
    EntityManager emgr = EntityManager();
    World world = World(&emgr);
    // Managers
    world.add_component_manager<Transform>();
    world.add_component_manager<Physics>();
    world.add_component_manager<Texture>();
    // Systems
    world.add_system<MotionSystem>();

    // Init
    world.init();

    EntityHandle e1 = world.create_entity();

    e1.add_component<Transform>(3.f, 4.f);
    e1.add_component<Physics>();
    e1.add_component<Texture>(720, 1080, 4);

    world.component_handle<Transform>(e1.entity)->position.x += 5;

    // Main loop
     printf("Begin loop\n");

    for (int i = 0; i < 10; ++i)
    {
        world.update(1.f);
    }

    printf("End loop\n");
}