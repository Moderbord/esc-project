#pragma once
#include <queue>

#include "entity.h"

class EntityManager
{
    public:
        EntityManager() = default;
        
        Entity create();
        void recycle(Entity entity);
        
    private:
        std::deque<unsigned int> free_ids;
        unsigned int next_id = 0;
};