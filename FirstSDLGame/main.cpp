#include "SDL.h"
#include "Game.h"




int main(int argc, char* argv[])
{
	
	SDLGame* mainGame = new SDLGame();

	mainGame->initialise();
	mainGame->runGameLoop();

	//initialisation.
	game->init("GameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);

	//game loop.
	while (game->running()) {
		
		game->handleEvents();
		game->update();
		game->render();

	}

	game->clean();
	
	return 0;
}
