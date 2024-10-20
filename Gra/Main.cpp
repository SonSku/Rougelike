#include "Game.h"
#include "Engine.h" 
#include "Buffer.h"
#include "Utilities.h"
#include "Color.h"
#include "Map.h"

int main()
{
	resizeConsole(80, 26);

	srand(time(NULL));

	Game* game = new Game();
	game->loop();
	delete game;


	return 0;
}