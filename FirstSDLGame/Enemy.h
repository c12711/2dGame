#pragma once

#include "FloatA.h"
#include "CD.h"
#include "Sprite.h"


class Enemy
{
private:

	// Position
	float		x;
	float		y;

	Sprite*			sprite;

	float		speed; // Speed

	// Bounding box
	float			w;
	float			h;
	CD				boundingBox;

	int				health; // Enemy health

	int				points; // Points for enemy

public:
	Enemy();
	~Enemy();

	void initialise(Sprite* playerSprite, float initX, float initY, int initHealth, float speed, int points);
	void update();
	void draw(SDL_Renderer* renderer);

	void move(float xMovement, float yMovement);

	CD getBoundingBox();

	void addHealth(int amountToAdd);

	void addPoints(int amountToAdd);

};

