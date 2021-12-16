#pragma once
#include "system.h"
#include "world.h"

class MotionSystem : public System
{
public:
	MotionSystem()
	{
		system_signature.set(1); // Transform
		system_signature.set(7); // Physics
	};

	void update(float dt) override
	{
		for (auto& entity : registered_entities)
		{
			ComponentHandle<Transform> transform;
			ComponentHandle<Physics> physics;

			parent_world->unpack_component(entity, transform, physics);

			transform->position += physics->linear_velocity * dt;
			physics->linear_velocity += physics->acceleration * dt;
		}
	}

private:
};