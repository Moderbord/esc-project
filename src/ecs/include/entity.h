#pragma once
//typedef unsigned int entity;

struct Entity
{
    unsigned int id;

    inline bool operator<(const Entity& rhs) const { return this->id < rhs.id; }
};