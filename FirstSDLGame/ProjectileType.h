#pragma once

#include "Sprite.h"
#include "CD.h"
#include "Enemy.h"


class ProjectileType
{
	// Projectile sprite
	Sprite*			sprite;

	float			damage; // Damage
	
	float			range; // Range

	// Projectile dimensions in game world
	float			w, h;

	float			speed; // Speed

	int				lifetime; // Lifetime

public:
	ProjectileType();
	virtual ~ProjectileType();

	void initialise(Sprite* playerSprite, float projectileDamage, float projectileRange, float width, float height, float projectileSpeed, int projectileLifetime);

	float getDamage();
	float getRange();
	float getWidth();
	float getHeight();
	float getSpeed();
	int	  getLifetime();

	void draw(SDL_Renderer* renderer, FloatA pos, float orientation);
};



