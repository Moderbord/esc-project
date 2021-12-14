#pragma once
#include <memory>
#include <vector>

#include "component_mgr.h"
#include "component_handle.h"
#include "component.h"
#include "entity.h"
#include "entity_mgr.h"

struct EntityHandle;

class World
{
public:
	World(EntityManager* entity_manager);
	void init();
	EntityHandle create_entity();
	void destroy_entity(Entity entity);

	// Add component to target Entity
	template<typename ComponentType, typename... Args>
	void add_component(Entity entity, Args&&... args)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		manager->add_component<ComponentType>(entity, args...);
	}

	// Remove component from target Entity
	template <typename ComponentType>
	void remove_component(Entity entity)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		manager->destroy_component(entity);
	}
	
	// Create a handle to manipulate an Entity with
	template <typename ComponentType>
	ComponentHandle<ComponentType> component_handle(Entity entity)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		return ComponentHandle<ComponentType>(entity, manager->get_component(entity), manager);
	}

	// Add a Component Manager to the World object
	template<typename ComponentType>
	void add_component_manager()
	{
		const int component_family = get_component_family<ComponentType>();
		const auto it = component_managers.begin() + component_family;
		component_managers.emplace(it, std::make_unique<ComponentManager<ComponentType>>(ComponentManager<ComponentType>()));
	}

private:
	std::vector<std::unique_ptr<BaseComponentManager>> component_managers;
	EntityManager* entity_manager;

	// Retrieves the Component Manager from the equivalent Component Type
	template<typename ComponentType>
	ComponentManager<ComponentType>* get_component_manager()
	{
		// retrieve component family ID
		const int component_family = get_component_family<ComponentType>();
		// return unique pointer to manager of corresponding component type
		return static_cast<ComponentManager<ComponentType> *>(component_managers[component_family].get());
	}

};