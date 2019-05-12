#include "windows.h"
#include "stdio.h"
#include "Sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include"Game.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void Sprite::initialise(SDL_Renderer* renderer, const char *pathToImage) {
	
	// Image load
	SDL_Surface* image = IMG_Load(pathToImage);
	
	// Create texture object from this image
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	
	// Region of texture that is to be drawn
	SDL_Rect		sourceRectangle;

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	SDL_QueryTexture(texture, 0, 0, &(sourceRectangle.w), &(sourceRectangle.h));
	
	// Delete image once texture is set up
	SDL_FreeSurface(image);

}

void Sprite::draw(SDL_Renderer* renderer, SDL_Rect* targetRect, float renderOrientation)
{	
	// Draw sprite
	SDL_RenderCopyEx(renderer, texture, &sourceRectangle, targetRect, renderOrientation, 0, SDL_FLIP_NONE);
}


