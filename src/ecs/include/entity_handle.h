#pragma once

#include "entity.h"
#include "world.h"

struct EntityHandle
{
public:
	Entity entity;
	World* world;

	// Destroy the entity connected to the handle. 
	void destroy()
	{
		world->destroy_entity(entity);
	}

	// Add a component to the entity connected to the handle.
	template <typename ComponentType, typename... Args>
	void add_component(Args... args)
	{
		world->add_component(entity, ComponentType(args...));
	}

	// Remove a component to the entity connected to the handle.
	template <typename ComponentType>
	void remove_component()
	{
		world->remove_component<ComponentType>(entity);
	}
	
};