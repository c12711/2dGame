#include "SDL.h"
#include "Game.h"
#include "SDL_image.h"

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
	mainPlayer->initialise(sprite, 100, 100, 100.0f);

	// Recipe 5 & 9 - instantiate something to collide with and shoot
	theOtherOne = new Enemy();
	theOtherOne->initialise(sprite, 600, 400);

	// Recipe 9 - Bullets
	bulletSprite = new Sprite();
	bulletSprite->initialise(gameRenderer, "Assets\\Images\\projectile01.png");

	bulletType = new ProjectileType();
	bulletType->initialise(bulletSprite, 5, 600, 32, 32);

	for (int i = 0; i < MAX_BULLETS; i++) {

		bullets[i] = nullptr;
	}
}

void Game::draw()
{

}













	//decide if want fullscreen or not when playing game.
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;

	}

	//make sure to initialise SDL properly.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	cnt++;
	std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

