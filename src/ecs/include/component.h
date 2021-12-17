#pragma once
#include <type_traits>
#include <iostream>

struct ComponentCounter
{
	static int counter;
};

template <typename ComponentType>
struct Component
{
	static inline int family()
	{
		static int family = ComponentCounter::counter++;
		return family;
	}
};

template <typename component>
static int get_component_family()
{
	return Component<typename std::remove_const<component>::type>::family();
}


/*-------------COMPONENTS------------*/
struct Vec2
{
	float x;
	float y;

	inline Vec2& operator+=(const Vec2& vec) { this->x += vec.x, this->y += vec.y; return *this; }
	inline Vec2 operator*(float val) const { return { x * val, y * val }; }
};

struct Transform : Component<Transform>
{
	Vec2 position;

	Transform(float x=0, float y=0) : position({x, y})
	{
		printf("Transform constructor\n");
	}

	~Transform()
	{
		printf("Transform deconstructor\n");
	}
};

struct Physics : Component<Physics>
{
	Vec2 linear_velocity;
	Vec2 acceleration;

	Physics(const Vec2& vel = { 1,0 }, const Vec2& acc = { 0,0 }) : linear_velocity(vel), acceleration(acc)
	{
		printf("Physics constructor\n");
	}

	~Physics()
	{
		printf("Physics deconstructor\n");
	}
};

struct Texture : Component<Texture>
{
	int width;
	int height;
	int bpp;

	Texture(int width=0, int height=0, int bpp=0) : width(width), height(height), bpp(bpp)
	{
		printf("Texture constructor\n");
	}

	~Texture()
	{
		printf("Texture deconstructor\n");
	}
};

