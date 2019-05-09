#pragma once

#include "Sprite.h"
#include "CD.h"
#include "Enemy.h"


class ProjectileType
{
	// Projectile sprite - what it looks like
	Sprite*			sprite;

	// Damage
	float			damage;

	// Range
	float			range;

	// Dimensions of projectile in game world
	float			w, h;

	float			speed;

	int				lifetime;

public:
	ProjectileType();
	virtual ~ProjectileType();

	void initialise(Sprite* playerSprite, float projectileDamage, float projectileRange, float width, float height, float projectileSpeed, int projectileLifetime);

	// Read-only accessors
	float getDamage();
	float getRange();
	float getWidth();
	float getHeight();
	float getSpeed();
	int	  getLifetime();

	void draw(SDL_Renderer* renderer, FloatA pos, float orientation);
};



