#pragma once
#include "component.h"

struct ComponentMask
{
	unsigned int mask = 0;

	bool matches(ComponentMask cmp_mask);

	template<typename ComponentType>
	ComponentMask add_component()
	{
		mask |= (1 << Component<ComponentType>::family());
		return { mask };
	}

	template<typename ComponentType>
	ComponentMask remove_component()
	{
		mask &= ~(1 << Component<ComponentType>::family());
		return { mask };
	}
};