#include "SDL.h"
#include <iostream>
#include "SDL_image.h"

class Game
{
public:
	Game();
	~Game();

	void initialise();
	void runGameLoop();

	
	

	



private:
	
	bool gameRunning;

	SDL_Window*		gameWindow = nullptr;
	SDL_Renderer*	gameRenderer = nullptr;


	void handleEvents();
	void update();
	void draw();

};

