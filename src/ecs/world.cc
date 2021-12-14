#include "world.h"
#include "entity_handle.h"

World::World(EntityManager* entity_manager) : entity_manager(entity_manager)
{

}

void World::init()
{
	component_managers.reserve(32);

	ComponentManager<Transform> trans_mgr = ComponentManager<Transform>();
	add_component_manager(std::move(trans_mgr));

	ComponentManager<Texture> text_mgr = ComponentManager<Texture>();
	add_component_manager(std::move(text_mgr));
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