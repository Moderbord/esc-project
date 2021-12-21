#include "entity_mgr.h"

namespace ECS
{
// Creates a new Entity with new or recycled id.
Entity EntityManager::create()
{
    // New id
    if (free_ids.empty())
    {
        return { ++next_id };
    }
    // Recycle
    Entity recycled{ free_ids.front() };
    free_ids.pop_front();
    return recycled;
}

// Allows the id of the Entity to be recycled.
void EntityManager::recycle(Entity entity)
{
    free_ids.push_back(entity.id);
}
} // end namespace