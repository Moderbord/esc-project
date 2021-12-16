#pragma once
#include <memory>
#include <vector>

#include "component_mgr.h"
#include "component_handle.h"
#include "component.h"
#include "entity.h"
#include "entity_mgr.h"
#include "system.h"

struct EntityHandle;

class World
{
public:
	World(EntityManager* entity_manager);
	void init();
	void update(float dt);
	void render();

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

	// Unpacks multiple component's data into specified component handles. Recursive case.
	template <typename ComponentType, typename... Args>
	void unpack_component(Entity entity, ComponentHandle<ComponentType>& handle, ComponentHandle<Args>&... args)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		handle = ComponentHandle<ComponentType>(entity, manager->get_component(entity), manager);
		// Recursive call
		unpack_component(entity, args...);
	}
	
	// Unpacks component data into specified component handle. Base case.
	template <typename ComponentType>
	void unpack_component(Entity entity, ComponentHandle<ComponentType>& handle)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		handle = ComponentHandle<ComponentType>(entity, manager->get_component(entity), manager);
	}

	// Add a Component Manager to the World object
	template<class ComponentType>
	void add_component_manager()
	{
		const int component_family = get_component_family<ComponentType>();
		const auto it = component_managers.begin() + component_family;
		auto ptr = std::make_unique<ComponentManager<ComponentType>>();
		component_managers.insert(it, std::move(ptr));
	}

	template<class SystemType>
	void add_system()
	{
		auto ptr = std::make_unique<SystemType>();
		systems.push_back(std::move(ptr));
	}

private:
	std::vector<std::unique_ptr<BaseComponentManager>> component_managers;
	std::vector<std::unique_ptr<System>> systems;
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