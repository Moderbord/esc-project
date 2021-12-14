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

struct Transform : Component<Transform>
{
	int x;
	int y;

	Transform(int x=0, int y=0) : x(x), y(y)
	{
		printf("Transform constructor\n");
	}

	~Transform()
	{
		printf("Transform deconstructor\n");
	}
};

struct Texture : Component<Texture>
{
	int width;
	int height;
	int bpp;
};

