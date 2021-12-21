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
    world.add_component_manager<Texture>();
    world.add_component_manager<Physics>();
    // Systems
    world.add_system<MotionSystem>();

    // Init
    world.init();

    EntityHandle e1 = world.create_entity();

    e1.add_component<Transform>(3.f, 4.f);
    e1.add_component<Physics>();
    e1.add_component<Texture>(720, 1080, 4);

    ComponentHandle<Transform> handle;
    world.unpack_component(e1.entity, handle);

    // Main loop
     printf("Begin loop\n");

    for (int i = 0; i < 20; ++i)
    {
        world.update(1.f);

        if (i == 5)
            e1.remove_component<Physics>();

        if (i == 15)
            e1.add_component<Physics>();

        printf("pos x: %f\n", handle->position.x);
    }

    printf("End loop\n");
}