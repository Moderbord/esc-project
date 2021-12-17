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
	// Add component mask for entity
	entity_masks.insert({ new_entity, ComponentMask() });
	return { new_entity, this };
}

// Destroys an Entity from the world along with all of its components
void World::destroy_entity(Entity entity)
{
	// Notify Entity Manager
	entity_manager->recycle(entity);
	// TODO remove entity from each comp manager
}

void World::update_entity_mask(Entity entity, ComponentMask new_mask, ComponentMask old_mask)
{
	for (auto& system : systems)
	{
		const ComponentMask system_mask = system->get_signature();

		if (new_mask.matches(system_mask) && !old_mask.matches(system_mask))
			system->register_entity(entity);
		else if (!new_mask.matches(system_mask) && old_mask.matches(system_mask))
			system->unregister_entity(entity);
	}
}
