#pragma once

#include "SDL.h"
#include "Game.h"
#include "SDL_image.h"
#include "stdio.h"
#include "KeyFlags.h"
#include "windows.h"

Game::Game() {
}


Game::~Game() {
}

void Game::initialise()
{
	const int SDL_OKAY = 0;

	int sdlStatus = SDL_Init(SDL_INIT_EVERYTHING);

	if (sdlStatus != SDL_OKAY)
		throw "SDL init error";

	// Game window creation
	gameWindow = SDL_CreateWindow(
		"Space Carnage",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		600,
		SDL_WINDOW_SHOWN);

	// Enumerate render drivers
	int n = SDL_GetNumRenderDrivers();

	printf("Number of renderers = %d\n", n);

	for (int i = 0; i < n; ++i) {

		SDL_RendererInfo renderInfo;

		if (SDL_GetRenderDriverInfo(i, &renderInfo) == 0) { // 0 means success

			printf("Renderer %d : %s\n", i, renderInfo.name);
		}
	}

	// Create game renderer
	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);


	// Player sprite
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "assets\\Player-1.png (1).png");

	mainPlayer = new Player();
	mainPlayer->initialise(sprite, 100, 100, 10, 5.5);	

	// Enemy sprite
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "assets\\Enemy-1.png.png");
	
	theOtherOne = new Enemy();
	theOtherOne->initialise(sprite, 600, 400, 10, 4, 10);

	// Primary bullet sprite (laser)
	bulletSprite = new Sprite();
	bulletSprite->initialise(gameRenderer, "assets\\Laser-1.png.png");

	bulletType = new ProjectileType();
	bulletType->initialise(bulletSprite, 5, 600, 32, 32, 9, 3);
	
	// Meteor laser pickup sprite
	bulletSprite = new Sprite();
	bulletSprite->initialise(gameRenderer, "assets\\Meteor Laser-1.png.png");

	bulletType = new ProjectileType();
	bulletType->initialise(bulletSprite, 10, 600, 32, 32, 9, 3);


	for (int i = 0; i < MAX_BULLETS; i++) {

		bullets[i] = nullptr;
	}


	// Shield pickup sprite
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "assets\\Shield-1.png.png");
}

void Game::runGameLoop() {

	gameRunning = true;

	while (gameRunning) {

		// Calculate time elapsed
		currentTimeIndex = SDL_GetTicks();
		timeDelta = currentTimeIndex - prevTimeIndex;
		timeDeltaInSeconds = float(timeDelta) / 1000.0f;

		// Stores current time into previous time index for the next frame
		prevTimeIndex = currentTimeIndex;

		handleEvents();
		update();
		draw();
	}
}

void Game::handleEvents() {

	SDL_Event event;

	// Next event check
	while (SDL_PollEvent(&event)) {

		switch (event.type) {

		// Check if window is closed
		case SDL_QUIT:
			gameRunning = false;
			break;

		// When a key is pressed
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {

			case SDLK_UP:
				keyState |= Keys::Up;
				break;

			case SDLK_DOWN:
				keyState |= Keys::Down;
				break;

			case SDLK_LEFT:
				keyState |= Keys::Left;
				break;

			case SDLK_RIGHT:
				keyState |= Keys::Right;
				break;

			case SDLK_SPACE:
				keyState |= Keys::Fire;
				break;

			case SDLK_ESCAPE:
				gameRunning = false;
				break;
			}
			break;

			// When a key is released
		case SDL_KEYUP:

			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				keyState &= (~Keys::Up);
				break;

			case SDLK_DOWN:
				keyState &= (~Keys::Down);
				break;

			case SDLK_LEFT:
				keyState &= (~Keys::Left);
				break;

			case SDLK_RIGHT:
				keyState &= (~Keys::Right);
				break;

			case SDLK_SPACE:
				keyState &= (~Keys::Fire);

				// Find the first bullet
				if (1) {

					int i = 0;
					while (bullets[i] != nullptr && i < MAX_BULLETS) {
						i++;
					}

					if (i < MAX_BULLETS) {

						bullets[i] = new BulletInstance();
						bullets[i]->initialise(bulletType, mainPlayer->getPosition(), FloatA(200.0f, 0.0f));
					}
				}

				break;
			}

			break;
		}
	}
}


void Game::update() {

	// Player movement through keys
	float		xMovement = 0.0f;
	float		yMovement = 0.0f;
	float		rotation = 0.0f;

	// Player movement when keys are pressed
	if (keyState & Keys::Left) {
		xMovement = -100.0f;
	}
	else {
		if (keyState & Keys::Right)
			xMovement = 100.0f;
		else if (keyState & Keys::Up)
			yMovement = -100.0f;
		else if (keyState & Keys::Down)
			yMovement = 100.0f;


		// Ensure length of direction vector is consistent for movement
		float dx = float(xMovement);
		float dy = float(yMovement);

		float dLength = sqrtf(dx * dx + dy * dy);

		if (dLength > 0.0f) {

			dx = dx / dLength;
			dy = dy / dLength;

			dx *= 100.0f;
			dy *= 100.0f;

			xMovement = dx;
			yMovement = dy;
		}
	}



	mainPlayer->move(xMovement * timeDeltaInSeconds, yMovement * timeDeltaInSeconds);
	mainPlayer->rotate(rotation * timeDeltaInSeconds);

	// Update bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			bullets[i]->update(timeDeltaInSeconds);
		}
	}

	// Player and enemy collision detection
	if (CD::intersectAABB(mainPlayer->getBoundingBox(), theOtherOne->getBoundingBox())) {

		// A hit
		mainPlayer->addHealth(-0.5f);

		if (mainPlayer->getHealth() <= 0.0f) {

			printf("GAME OVER\n");
			gameRunning = false;
		}
	}

	// Check for laser collision with enemy
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {

			if (CD::intersectAABB(bullets[i]->getBoundingBox(), theOtherOne->getBoundingBox())) {

				printf("Hit!\n");
				bullets[i]->hit(theOtherOne);
			}
		}
	}

	// Laser bullets disappear when out of range
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i] && bullets[i]->exceededRange()) {

			printf("eol!\n");
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}
}

void Game::draw() {

	// Clear screen
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255); // Colour provided as red, green, blue and alpha (transparency) values (ie. RGBA)
	SDL_RenderClear(gameRenderer);

	// Draw player
	mainPlayer->draw(gameRenderer);

	// Instantiate something to collide against
	theOtherOne->draw(gameRenderer);

	// Draw lasers
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			bullets[i]->draw(gameRenderer);
		}
	}


	// Render frame to screen
	SDL_RenderPresent(gameRenderer);
}
