#pragma once
#include "TextureManager.h"
#include "vec2.h"
#include "EntityComponentSystem.h"
#include <SDL.h>

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	vec2 position;
	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 64;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;
	}

	void update() override
	{
		/*destRect.x = position.x - Application::camera.x;
		destRect.y = position.y - Application::camera.y;*/
	}

	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect, SDL_FLIP_NONE);
	}
};