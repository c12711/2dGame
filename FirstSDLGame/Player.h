#pragma once

#include "FloatA.h"
#include "Sprite.h"
#include "SDL_render.h"
#include "CD.h"



class Player
{
private:

	// position
	float			x;
	float			y;
	// player rotation
	float			orientation;

	float			speed;

	Sprite*			sprite = nullptr;

	// collision detection bounding volume
	float			w;
	float			h;
	CD				boundingBox;

	float			health;
	

public:
	Player();
	~Player();

	void initialise(Sprite* sprite, float initx, float initY, float initHealth, float speed);
	void update();
	void draw(SDL_Renderer* renderer);

	FloatA getPosition();
	void move(float xMovement, float yMovement);

	// player rotation
	void rotate(float dTheta);

	// Bounding box collision detection
	CD getBoundingBox();

	// Recipe 8 - Update health by amountToAdd (if amountToAdd is negative the player's health goes down!)
	void addHealth(float amountToAdd);
	float getHealth();
};

