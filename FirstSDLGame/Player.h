#pragma once
class Player
{
private:

	//position
	int		x;
	int		y;

	Sprite* playerSprite;

public:
	Player();
	~Player();

	void initialise(Sprite* playerSprite, int initx, int initY);
	void draw(SDL_Renderer* renderer);
};

