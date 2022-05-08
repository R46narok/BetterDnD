#pragma once 

#include "EntityComponentSystem.h"
#include "../math/vec2.h"

class TransformComponent : public Component
{
public:
	vec2 position;
	vec2 velocity;
	static bool onGround;
	int speed = 3;
	float height = 32;
	float width = 32;
	float scale = 1;

	TransformComponent()
	{
		position.Zero();
	}
	TransformComponent(int sc)
	{
		position.x = 0;
		position.y = 0;
		scale = sc;
	}
	TransformComponent(float x, float y)
	{
		position.Zero();
	}
	TransformComponent(float x, float y, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{
		/*position.x += velocity.x * speed;
		position.y += velocity.y * speed;*/
	}
};
