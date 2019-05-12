#include "Player.h"
#include "windows.h"
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"


Player::Player()
{
}


Player::~Player()
{
}


void Player::initialise(Sprite* sprite, float initX, float initY, float initHealth, float initSpeed) {

	x = initX;
	y = initY;

	this->sprite = sprite;

	// Size of sprite in game world
	w = 128.0f;
	h = 128.0f;

	// Calculate centre point of sprite
	float cx = x + (w / 2.0f);
	float cy = y + (h / 2.0f);

	boundingBox = CD(cx, cy, w / 2.0f, h / 2.0f); // Store half w, h in the bounding box

	// Player health
	health = initHealth;

	// Player speed
	speed = initSpeed;
}


void Player::update() {
}


void Player::draw(SDL_Renderer* renderer) {

	SDL_Rect	targetRect;

	// Get player size
	targetRect.x = int(x);
	targetRect.y = int(y);
	targetRect.w = int(w); 
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, orientation);

	// Draw bounding box to show collision boundary
	boundingBox.draw(renderer);
}


FloatA Player::getPosition() {

	return FloatA(x, y);
}


void Player::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	// Also move bounding box along with enemy
	boundingBox.move(xMovement, yMovement);
}


// Player rotation (doesn't affect bouding box)
void Player::rotate(float dTheta) {

	orientation += dTheta;

	
}


// Test for collisions in game object
CD Player::getBoundingBox() {

	return boundingBox;
}


// Update player health (up or down depending on amountToAdd value)
void Player::addHealth(float amountToAdd) {

	health += amountToAdd;
	printf("health = %f\n", health);
}

float Player::getHealth() {

	return health;
}
