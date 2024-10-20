#pragma once
#include "Map.h"
#include "Buffer.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h" 
#include "Inventory.h"
#include "PathFinder.h"
#include <conio.h>


class Engine
{
public:

	Engine(Buffer*);

	enum class State
	{
		Playing,
		Exit,
		Pause,
		Inventory
	} state = State::Playing;

	void draw();
	void loop();
	void play();
	void pause();
	void inventoryScreen();
	bool collision(int, int);
	bool isOnStairs();
	bool isOnRiver(int, int);
	void isOnItem();
	void setPlayerPosition();
	void deleteEnemy(Character*);
	void setEnemyPosition();
	Character* characterAtPosition(int, int);
	int level = 0;
	std::vector<Enemy> enemies;
	void processAI();
	Map **visible[80][25];
	Map **prev_visible[80][25];

	Map map;
	Player player;
	Buffer* buffer;
	Inventory inventory;
	PathFinder path;
};

