#include "Enemy.h"
#include "windows.h"
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::initialise(Sprite* sprite, float initX, float initY, int initHealth, float speed, int points) {

	x = initX;
	y = initY;

	this->sprite = sprite;

	// Size of sprite in game world
	w = 128.0f;
	h = 128.0f;

	// Calculate centre point of sprite
	float cx = x + (w / 2.0f);
	float cy = y + (h / 2.0f);

	boundingBox = CD(cx, cy, w / 2.0f, h / 2.0f); // Store half w, h in the bounding box!

	health = initHealth;
}

void Enemy::update() {
}

void Enemy::draw(SDL_Renderer* renderer) {

	SDL_Rect targetRect;

	// Get enemy size
	targetRect.x = int(x);
	targetRect.y = int(y);
	targetRect.w = int(w);
	targetRect.h = int(h);

	// Draw enemy
	sprite->draw(renderer, &targetRect, 0.0f);

	// Draw bounding box to show collision boundary
	boundingBox.draw(renderer);
}


void Enemy::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	// Also move bounding box along with enemy
	boundingBox.move(xMovement, yMovement);
}

// Test for collisions in game object
CD Enemy::getBoundingBox() {

	return boundingBox;
}

// Code for health loss when lasers hit
void Enemy::addHealth(int amountToAdd) {

	health += amountToAdd;	
}

// Points 
void Enemy::addPoints(int amountToAdd) {

	points += amountToAdd;
}