#include "world.h"
#include "entity_handle.h"

World::World(EntityManager* entity_manager) : entity_manager(entity_manager)
{

}

void World::init()
{
	component_managers.reserve(32);

	add_component_manager<Transform>();
	add_component_manager<Texture>();
}

// Creates a new entity
EntityHandle World::create_entity()
{
	Entity new_entity = entity_manager->create();
	return { new_entity, this };
}

// Destroys an Entity from the world along with all of its components
void World::destroy_entity(Entity entity)
{
	// Notify Entity Manager
	entity_manager->recycle(entity);
	// TODO remove entity from each comp manager
}