#pragma once
#include <memory>
#include <vector>
#include <map>

#include "component_mgr.h"
#include "component_handle.h"
#include "component.h"
#include "component_mask.h"
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
	void update_entity_mask(Entity entity, ComponentMask new_mask, ComponentMask old_mask);

	// Add component to target Entity
	template<typename ComponentType, typename... Args>
	void add_component(Entity entity, Args&&... args)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		manager->add_component<ComponentType>(entity, args...);

		const ComponentMask old_mask = entity_masks[entity];
		const ComponentMask new_mask = entity_masks[entity].add_component<ComponentType>();
		update_entity_mask(entity, new_mask, old_mask);
	}

	// Remove component from target Entity
	template <typename ComponentType>
	void remove_component(Entity entity)
	{
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		manager->destroy_component(entity);

		const ComponentMask old_mask = entity_masks[entity];
		const ComponentMask new_mask = entity_masks[entity].remove_component<ComponentType>();
		update_entity_mask(entity, new_mask, old_mask);
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
		ptr->register_world(this);
		systems.push_back(std::move(ptr));
	}

private:
	std::vector<std::unique_ptr<BaseComponentManager>> component_managers;
	std::vector<std::unique_ptr<System>> systems;
	std::map<Entity, ComponentMask> entity_masks;
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