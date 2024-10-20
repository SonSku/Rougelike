#pragma once
#include "Buffer.h"
#include "Engine.h"

class Game
{
public:
	enum  class State
	{
		Playing,
		Menu,
		Inventory,
		Exit
	} state = State::Playing;

	void loop();

	void play();

	void menu();

	//void inventory();

	Game();

	Buffer buffer;
};

