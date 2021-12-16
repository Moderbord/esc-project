#pragma once
#include <bitset>
#include <vector>
#include "entity.h"

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

protected:
	std::bitset<32> system_signature;
	std::vector<Entity> registered_entities;
	World* parent_world;
};