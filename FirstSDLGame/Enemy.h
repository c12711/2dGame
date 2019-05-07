#pragma once
#include "FloatA.h"
#include "CD.h"
#include "Sprite.h"


class Enemy
{
private:

	// Position
	int		x;
	int		y;

	Sprite*			sprite;

	// Bounding box
	float			w;
	float			h;
	CD				boundingBox;

	// Enemy health
	int				health = 100;

public:
	Enemy();
	~Enemy();

	void initialise(Sprite* playerSprite, int initX, int initY);
	void update();
	void draw(SDL_Renderer* renderer);

	void move(int xMovement, int yMovement);

	void addHealth(int amountToAdd);

	CD getBoundingBox();

};

