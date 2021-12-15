#include <iostream>

#include "world.h"
#include "entity_handle.h"

int main()
{
    EntityManager emgr = EntityManager();
    World world = World(&emgr);
    world.init();

    EntityHandle e1 = world.create_entity();
    EntityHandle e2 = world.create_entity();

    e2.add_component<Transform>(3, 4);
    e2.add_component<Texture>(720, 1080, 4);

    ComponentHandle<Transform> c_transform;
    ComponentHandle<Texture> c_texture;

    world.unpack_component(e2.entity, c_transform, c_texture);

    printf("End of main\n");
}