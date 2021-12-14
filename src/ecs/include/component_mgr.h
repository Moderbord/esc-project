#pragma once
#include <array>

#include "entity.h"
#include "entity_map.h"


template <typename ComponentType>
struct ComponentData
{
	// 0 used as invalid value
	unsigned int size = 1;
	std::array<ComponentType, MAX_COMPONENTS_PER_TYPE>* data;
};

class BaseComponentManager
{
public:
	BaseComponentManager() = default;
	virtual ~BaseComponentManager() = default;
	/*BaseComponentManager(BaseComponentManager&) = default;
	BaseComponentManager &operator=(BaseComponentManager&) = default;*/
	/*BaseComponentManager(const BaseComponentManager&) = default;
	BaseComponentManager &operator=(const BaseComponentManager&) = default;*/
};

template <typename ComponentType>
class ComponentManager : public BaseComponentManager
{
public:
	// Create a new Component Manager with a specific Component Type
	ComponentManager()
	{
		// Manually allocate a block of data
		component_data.data = static_cast<std::array<ComponentType, 1024> *>(malloc(sizeof(ComponentType) * 1024));
	}

	// Add
	ComponentInstance add_component(Entity entity, ComponentType& component)
	{
		// create new instance
		// TODO check recycled instances
		ComponentInstance new_instance = component_data.size;
		// assign new instance into data container
		component_data.data->at(new_instance) = component;
		// update internal references
		entity_map.add(entity, new_instance);
		// increment number of component instances
		component_data.size++;
		// return new instance
		return new_instance;
	}

	void destroy_component(Entity entity)
	{
		ComponentInstance instance = entity_map.get_instance(entity);
		entity_map.remove(entity);
	}

	ComponentType* get_component(Entity entity)
	{
		ComponentInstance instance = entity_map.get_instance(entity);
		return &component_data.data->at(instance);
	}

private:
	ComponentData<ComponentType> component_data;
	EntityMap entity_map;
};