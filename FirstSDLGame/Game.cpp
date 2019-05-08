#include "SDL.h"
#include "Game.h"
#include "SDL_image.h"
#include "stdio.h"
#include "KeyFlags.h"


Game::Game()
{


}


Game::~Game()
{


}

void Game::initialise()
{
	const int SDL_OKAY = 0;

	int sdlStatus = SDL_Init(SDL_INIT_EVERYTHING);

	if (sdlStatus != SDL_OKAY)
		throw "SDL init error";

	gameWindow = SDL_CreateWindow(
		"game name",
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

	// Use first (Default) renderer - this is usually Direct3D based
	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);


	// Use first (Default) renderer - this is usually Direct3D based
	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);

	
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "assets/Player-1.png (1).png");

	mainPlayer = new Player();
	mainPlayer->initialise(sprite, 100, 100);	

	//
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "assets/Enemy-1.png");
	
	theOtherOne = new Enemy();
	theOtherOne->initialise(sprite, 600, 400);
}

void Game::runGameLoop() {

	gameRunning = true;

	while (gameRunning) {

		// Recipe 3 - Update timing / clock

		// Calculate time elapsed
		//currentTimeIndex = SDL_GetTicks();
		//timeDelta = currentTimeIndex - prevTimeIndex;
		//timeDeltaInSeconds = float(timeDelta) / 1000.0f;

		// Store current time index into prevTimeIndex for next frame
		//prevTimeIndex = currentTimeIndex;

		// --------------------

		handleEvents();
		update();
		draw();
	}
}

	//decide if want fullscreen or not when playing game.
	//int flags = 0;
	//if (fullscreen)
	//{
		//flags = SDL_WINDOW_FULLSCREEN;

	//}


void Game::handleEvents() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

			// Check if window closed
		case SDL_QUIT:
			gameRunning = false;
			break;

			// Key pressed event
		case SDL_KEYDOWN:

			// Toggle key states based on key pressed
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

			// Key released event
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

				// Find first "free" bullet
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
	int		xMovement = 0.0f;
	int		yMovement = 0.0f;
	float	rotation = 0.0f;


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
	

	// Ensure length of direction vector is consistent for axis-aligned and diagonal movement
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

	// Recipe 9 - Update bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			bullets[i]->update(timeDeltaInSeconds);
		}
	}


	if (CD::intersectAABB(mainPlayer->getBoundingBox(), theOtherOne->getBoundingBox())) {

		// A hit!
		mainPlayer->addHealth(-0.1f);

		if (mainPlayer->getHealth() <= 0.0f) {

			printf("GAME OVER\n");
			gameRunning = false;
		}
	}

	// Recipe 9 - Check for bullet collisions with 'theOtherOne' Enemy object
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {

			if (CD::intersectAABB(bullets[i]->getBoundingBox(), theOtherOne->getBoundingBox())) {

				printf("Hit!\n");
				bullets[i]->hit(theOtherOne);
			}
		}
	}

	// Recipe 9 - Check for bullets out of range - delete when found
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i] && bullets[i]->exceededRange()) {

			printf("eol!\n");
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

void Game::draw() {

	// 1. Clear the screen
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255); // Colour provided as red, green, blue and alpha (transparency) values (ie. RGBA)
	SDL_RenderClear(gameRenderer);


	// 2. Draw the scene...

	// Draw the main player
	mainPlayer->draw(gameRenderer);

	// Recipe 5 - instantiate something to collide against
	theOtherOne->draw(gameRenderer);

	// Recipe 9 - Draw bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			bullets[i]->draw(gameRenderer);
		}
	}


	// 3. Present the current frame to the screen
	SDL_RenderPresent(gameRenderer);
}
