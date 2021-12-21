#pragma once

namespace ECS
{
struct Entity
{
    unsigned int id;

    inline bool operator<(const Entity& rhs) const { return this->id < rhs.id; }
    inline bool operator==(const Entity& rhs) const { return this->id == rhs.id; }
};
} // end namespace