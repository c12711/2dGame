#pragma once

#include "FloatA.h"
#include "Sprite.h"
#include "CD.h"


class Player
{
private:

	// Position
	float			x;
	float			y;
	
	
	float			orientation; // Player rotation

	Sprite*			sprite = nullptr;

	// collision detection bounding volume
	float			w;
	float			h;
	CD				boundingBox;

	float			health; // Player health
	float			speed; // Player speed

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

	// Update health (amountToAdd neg or pos)
	void addHealth(float amountToAdd);
	float getHealth();
};

