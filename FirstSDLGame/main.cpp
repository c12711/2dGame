#include "SDL.h"
#include "Game.h"




int main(int argc, char* argv[])
{
	//initialisation.
	Game* mainGame = new Game();
	mainGame->initialise();
	mainGame->runGameLoop();

	
	//game->init("GameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);

	//game loop.
	//while (game->running()) {
		
		//game->handleEvents();
		//game->update();
		//game->render();

	//}

	//game->clean();
	
	return 0;
}
