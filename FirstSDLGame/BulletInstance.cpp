#include "BulletInstance.h"
#include "windows.h"
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"

BulletInstance::BulletInstance()
{
}


BulletInstance::~BulletInstance()
{
}

void BulletInstance::initialise(ProjectileType* type, FloatA initPos, FloatA initVel) {

	this->type = type;

	this->pos = initPos;
	this->vel = initVel;

	// Calculate centre point of sprite
	float cx = pos.x + (type->getWidth() / 2.0f);
	float cy = pos.y + (type->getHeight() / 2.0f);

	boundingBox = CD(cx, cy, type->getWidth() / 2.0f, type->getHeight() / 2.0f); // Store half w, h in the bounding box!
}

void BulletInstance::update(float tDelta) {

	float dx = vel.x * tDelta;
	float dy = vel.y * tDelta;

	float offset = sqrtf(dx * dx + dy * dy);

	pos.x += dx;
	pos.y += dy;

	boundingBox.move(dx, dy);

	distanceTravelled += offset;
}

void BulletInstance::hit(Enemy* target) {

	// Change health when hit
	int damageImpact = int(type->getDamage());
	target->addHealth(-damageImpact);
	distanceTravelled = type->getRange();
}

bool BulletInstance::exceededRange() {

	// Disappears when range exceeded
	return distanceTravelled >= type->getRange();
}

CD BulletInstance::getBoundingBox() {

	return boundingBox;
}

void BulletInstance::draw(SDL_Renderer* renderer) {

	type->draw(renderer, pos, 0.0f);
}