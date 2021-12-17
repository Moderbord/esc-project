#pragma once
#include <array>
#include <vector>

#include "entity.h"
#include "entity_map.h"


template <typename ComponentType>
struct ComponentData
{
	unsigned int size = 0;
	std::vector<ComponentType> data;
};

class BaseComponentManager
{
public:
	BaseComponentManager() = default;
	virtual ~BaseComponentManager() = default;
};

template <typename ComponentType>
class ComponentManager : public BaseComponentManager
{
public:
	// Create a new Component Manager with a specific Component Type
	ComponentManager()
	{
		// Reserve memory
		component_data.data.reserve(MAX_COMPONENTS_PER_TYPE);
	}

	// Add
	template <typename ComponentType, typename... Args>
	ComponentInstance add_component(Entity entity, Args&&... args)
	{
		// create new instance
		// TODO check recycled instances
		ComponentInstance new_instance = component_data.size;
		// set instance index 
		const auto it = component_data.data.begin() + new_instance;
		// create object in place at index
		component_data.data.emplace(it, args...);
		// update internal references
		entity_map.add(entity, new_instance);
		// increment number of component instances
		component_data.size++;
		// return new instance
		return new_instance;
	}

	void destroy_component(Entity entity)
	{
		// TODO destructor call?
		ComponentInstance instance = entity_map.get_instance(entity);
		entity_map.remove(entity);
	}

	ComponentType* get_component(Entity entity)
	{
		ComponentInstance instance = entity_map.get_instance(entity);
		return &component_data.data.at(instance);
	}

private:
	ComponentData<ComponentType> component_data;
	EntityMap entity_map;
};