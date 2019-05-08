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

void Sprite::initialise(SDL_Renderer* renderer, const char *pathToImage)
{
	SDL_Surface* image = IMG_Load("assets/Player-1.png (1).png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Rect	sourceRectangle;

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	SDL_QueryTexture(texture, 0, 0, &(sourceRectangle.w), &(sourceRectangle.h));

	SDL_Rect		targetRectangle;

	targetRectangle.x = 100;
	targetRectangle.y = 100;
	targetRectangle.w = 64;
	targetRectangle.h = 64;

	SDL_FreeSurface(image);
}

void Sprite::draw(SDL_Renderer* renderer, SDL_Rect* targetRectangle, float renderOrientation)
{	
	SDL_RenderCopyEx(renderer,
		texture,
		&sourceRectangle, 
		targetRectangle,
		renderOrientation,
		0,
		SDL_FLIP_NONE);
}


