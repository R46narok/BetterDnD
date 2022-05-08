#pragma once

#include <map>
#include "TransformComponent.h"
#include "Animation.h"
#include "../math/vec3.h"
#include "../application.h"

static SDL_Texture* LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Application::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}
static void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Application::renderer, tex, src, dest, NULL, NULL, flip);
}

class SpriteComponent : public Component
{
private:

	bool text = false;
	bool animated = false;
	int frames = 0;
	int speed = 100;
public:
	TransformComponent *transform;
	SDL_Rect srcRect, destRect;
	SDL_Texture *texture;   
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = LoadTexture(path);
	}
	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("idle", idle);
		animations.emplace("walk", walk);

		Play("idle");

		texture = LoadTexture(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void setTex(const char *path)
	{
		texture = LoadTexture(path);
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;

		
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override
	{
		Draw(texture, &srcRect, &destRect, spriteFlip);
	}
	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};
