#include "world.h"
#include "entity_handle.h"

World::World(EntityManager* entity_manager) : entity_manager(entity_manager)
{
	component_managers.reserve(32);
}

void World::init()
{
	for (auto& system : systems)
	{
		system->register_world(this);
		system->init();
	}
}

void World::update(float dt)
{
	for (auto& system : systems)
	{
		system->update(dt);
	}
}

void World::render()
{
	for (auto& system : systems)
	{
		system->render();
	}
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