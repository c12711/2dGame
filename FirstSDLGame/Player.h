#pragma once

#include "FloatA.h"
#include "Sprite.h"
#include "SDL_render.h"
#include "CD.h"



class Player
{
private:

	// position
	int				x;
	int				y;
	// player rotation
	float			orientation;

	Sprite*			sprite;

	// collision detection bounding volume
	float			w;
	float			h;
	CD				boundingBox;

	float			health;

	int				points;


public:
	Player();
	~Player();

	void initialise(Sprite* sprite, int initx, int initY, float initHealth);
	void update();
	void draw(SDL_Renderer* renderer);

	FloatA getPosition();
	void move(int xMovement, int yMovement);

	// player rotation
	void rotate(float dTheta);

	// Bounding box collision detection
	CD getBoundingBox();

	// Recipe 8 - Update health by amountToAdd (if amountToAdd is negative the player's health goes down!)
	void addHealth(float amountToAdd);
	float getHealth();

	//
	void addPoints(int amountToAdd);
};

