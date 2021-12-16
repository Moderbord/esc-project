#include "system.h"

void System::init()
{
}

void System::update(float dt)
{
}

void System::render()
{
}

void System::register_world(World* world)
{
	parent_world = world;
}

void System::register_entity(Entity entity)
{
	registered_entities.push_back(entity);
}

void System::unregister_entity(Entity entity)
{
	for (auto it = registered_entities.begin(); it != registered_entities.end(); ++it)
	{
		if (*it == entity)
		{
			registered_entities.erase(it);
			return;
		}
	}
}
