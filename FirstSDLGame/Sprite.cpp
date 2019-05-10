#include "windows.h"
#include "stdio.h"
#include "Sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include"Game.h"
#include"Game.cpp"


Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void Sprite::initialise(SDL_Renderer* renderer, const char *pathToImage) {
	
	SDL_Surface* image = IMG_Load(pathToImage);
	texture = SDL_CreateTextureFromSurface(renderer, image);

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	SDL_QueryTexture(texture, 0, 0, &(sourceRectangle.w), &(sourceRectangle.h));

	SDL_FreeSurface(image);
}

void Sprite::draw(SDL_Renderer* renderer, SDL_Rect* targetRect, float renderOrientation)
{	
	SDL_RenderCopyEx(renderer,
		texture,
		&sourceRectangle,
		targetRect,
		renderOrientation,
		0,
		SDL_FLIP_NONE);
}


