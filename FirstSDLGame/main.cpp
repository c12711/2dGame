#include "SDL.h"
#include "Game.h"




int main(int argc, char* args[])
{
	//initialisation.
	Game* mainGame = new Game();

	mainGame->initialise();
	mainGame->runGameLoop();
			
	return 0;
}
