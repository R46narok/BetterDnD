#pragma once

#include "../math/vec3.h"
#include "../application.h"
#include "../ECS/EntityComponentSystem.h"
#include "../ECS/SpriteComponent.h"
#include "../ECS/TransformComponent.h"
#include <string>

struct TextureManager
{
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
	static SDL_Texture* LoadFont(const char* path, const char* text, vec3 color)
	{
		TTF_Font * font = TTF_OpenFont(path, 25);
		SDL_Color textColor = { color.x, color.y, color.z };
		SDL_Surface * surface = TTF_RenderText_Solid(font, text, textColor);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(Application::renderer, surface);
		
		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
		return texture;
	}
	static SDL_Texture* LoadFont(const char* path, std::string text, vec3 color)
	{
		TTF_Font * font = TTF_OpenFont(path, 25);
		SDL_Color textColor = { color.x, color.y, color.z };
		SDL_Surface * surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, 175);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(Application::renderer, surface);

		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
		return texture;
	}
	static SDL_Texture* LoadFont(const char* text, vec3 color)
	{
		TTF_Font * font = TTF_OpenFont("database/Fonts/papyrus.ttf", 25);
		SDL_Color textColor = { color.x, color.y, color.z };
		SDL_Surface * surface = TTF_RenderText_Solid(font, text, textColor);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(Application::renderer, surface);

		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
		return texture;
	}
};
