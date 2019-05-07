
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "KeyFlags.h"


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

	//Adding player sprite
	Sprite*			sprite = nullptr;
	Player*			mainPlayer = nullptr;

	//Keyboard controls
	KeyFlags		keyState = 0;

	// Recipe 3 - Timing attributes
	uint32_t		currentTimeIndex, prevTimeIndex, timeDelta;
	float			timeDeltaInSeconds;

	// Enemy for shooting and collisions
	Enemy*			theOtherOne = nullptr;



	void handleEvents();
	void update();
	void draw();
	
};

