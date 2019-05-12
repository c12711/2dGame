#pragma once

#include "CD.h"
#include "FloatA.h"
#include "ProjectileType.h"

class BulletInstance
{
	ProjectileType*	type; // Provide access to sprite and damage

	FloatA			pos; // Position
	FloatA			vel; // Velocity (direction)

	float			distanceTravelled; // Distance travelled
	float			speed;			// Speed
	float			lifetime;			// Lifetime

	// Bounding box for collisions
	CD			boundingBox;


public:
	BulletInstance();
	~BulletInstance();

	void initialise(ProjectileType* type, FloatA initPos, FloatA initVel);

	void update(float tDelta);
	void hit(Enemy* target);
	bool exceededRange();

	CD getBoundingBox();

	void draw(SDL_Renderer* renderer);
};



