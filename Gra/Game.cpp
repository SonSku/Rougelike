#include "Game.h"

Game::Game()
{
	buffer.setCursorVisibility(false);
}

void Game::play()
{
	Engine* engine = new Engine(&buffer);
	engine->loop();
}



void Game::menu()
{

}

void Game::loop()
{
	while (state != State::Exit)
	{
		switch (state) 
		{
			case State::Menu:
			{
				menu();
				break;
			}
			case State::Playing:
			{
				play();
				break;
			}
		}
	}
}