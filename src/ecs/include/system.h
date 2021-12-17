#pragma once
#include <bitset>
#include <vector>
#include "entity.h"
#include "component_mask.h"

class World;

class System
{
public:
	System() : parent_world(nullptr) {};
	~System() = default;
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	void register_world(World* world);
	void register_entity(Entity entity);
	void unregister_entity(Entity entity);
	ComponentMask get_signature();

protected:
	ComponentMask system_signature;
	std::vector<Entity> registered_entities;
	World* parent_world;
};