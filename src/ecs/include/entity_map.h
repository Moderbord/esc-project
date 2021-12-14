#pragma once
#include <array>
#include <map>
#include "entity.h"

const int MAX_COMPONENTS_PER_TYPE = 1024;
typedef unsigned int ComponentInstance;

struct EntityMap
{
public:
	Entity get_entity(ComponentInstance instance) { return instance_to_entity.at(instance); }
	ComponentInstance get_instance(Entity entity) { return entity_to_instance.at(entity); }

	void add(Entity entity, ComponentInstance instance)
	{
		entity_to_instance.insert({entity, instance});
		instance_to_entity.insert({instance, entity});
	}

	void update(Entity entity, ComponentInstance instance)
	{
		entity_to_instance.at(entity) = instance;
		instance_to_entity.at(instance) = entity;
	}

	void remove(Entity entity)
	{
		instance_to_entity.erase(get_instance(entity));
		entity_to_instance.erase(entity);
	}

	void remove(ComponentInstance instance)
	{
		entity_to_instance.erase(get_entity(instance));
		instance_to_entity.erase(instance);
	}

private:
	std::map<Entity, ComponentInstance> entity_to_instance;
	std::map<ComponentInstance, Entity> instance_to_entity;
};