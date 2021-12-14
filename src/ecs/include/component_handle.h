#pragma once

#include "component_mgr.h"
#include "entity.h"

template <typename ComponentType>
struct ComponentHandle
{
public:
	Entity owner;
	ComponentType* component;
	ComponentManager<ComponentType>* mgr;

	ComponentHandle(Entity owner, ComponentType* component, ComponentManager<ComponentType>* manager)
		: owner(owner), component(component), mgr(manager) {}
	
	ComponentType* operator->() const { return component; }
	
	void destroy() { mgr->destroy_component(owner); }

};