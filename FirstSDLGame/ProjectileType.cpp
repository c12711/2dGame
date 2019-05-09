#include "ProjectileType.h"

ProjectileType::ProjectileType()
{
}


ProjectileType::~ProjectileType()
{
}

void ProjectileType::initialise(Sprite* projectileSprite, float projectileDamage, float projectileRange, float width, float height, float projectileSpeed, int projectileLifetime) {

	sprite = projectileSprite;
	damage = projectileDamage;
	range = projectileRange;
	w = width;
	h = height;
	speed = projectileSpeed;
	lifetime = projectileLifetime;
}

float ProjectileType::getDamage() {

	return damage;
}

float ProjectileType::getRange() {

	return range;
}

float ProjectileType::getWidth() {

	return w;
}

float ProjectileType::getHeight() {

	return h;
}

float ProjectileType::getSpeed() {

	return speed;
}

int ProjectileType::getLifetime() {

	return lifetime;
}


void ProjectileType::draw(SDL_Renderer* renderer, FloatA pos, float orientation) {

	SDL_Rect targetRect;

	targetRect.x = int(pos.x);
	targetRect.y = int(pos.y);
	targetRect.w = int(w);
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, orientation);
}

