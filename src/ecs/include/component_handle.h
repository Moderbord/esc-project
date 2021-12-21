#pragma once
#include "component_mgr.h"
#include "entity.h"

namespace ECS
{
template <typename ComponentType>
struct ComponentHandle
{
public:
	Entity owner;
	ComponentType* component;
	ComponentManager<ComponentType>* mgr;

	ComponentHandle() : component(nullptr), mgr(nullptr) {};
	ComponentHandle(Entity owner, ComponentType* component, ComponentManager<ComponentType>* manager)
		: owner(owner), component(component), mgr(manager) {}
	
	ComponentType* operator->() const { return component; }
	
	void destroy() { mgr->destroy_component(owner); }

};
} // end namespace