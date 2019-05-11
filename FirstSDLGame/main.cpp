#include "SDL.h"
#include "Game.h"
#include "windows.h"
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"



int main(int argc, char* args[])
{
	//initialisation.
	Game* mainGame = new Game();

	mainGame->initialise();
	mainGame->runGameLoop();
			
	return 0;
}
