#pragma once

#include "CD.h"
#include "FloatA.h"
#include "ProjectileType.h"

class BulletInstance
{
	ProjectileType*	type; // Provide access to sprite and damage

	FloatA			pos; // Position
	FloatA			vel; // Direction of travel (serves as velocity)

	float			distanceTravelled; // How far the bullet has travelled

	// Bounding volume for collisions
	CD			boundingBox;


public:
	BulletInstance();
	~BulletInstance();

	// ProjectileInstance interface
	void initialise(ProjectileType* type, FloatA initPos, FloatA initVel);

	void update(float tDelta);
	void hit(Enemy* target);
	bool exceededRange();

	CD getBoundingBox();

	void draw(SDL_Renderer* renderer);
};



