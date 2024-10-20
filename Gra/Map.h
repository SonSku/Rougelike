#pragma once
#include "Buffer.h"
#include "Drawable.h"
#include "Tile.h"
#include "Color.h"
#include "Sprite.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

class Map:public Drawable
{
public:
	Tile tiles[80][25];

	bool** visible;
	bool** prev_visible;
	Map();
	void generate(int level);
	void updateVisibility(Player&);
	int num_of_miners = 3 + rand() % 4;
	int max_distance = 0;
	int max_current_distance = 0;
	std::vector<int> first_point = {};
	std::vector<int> second_point = {};
	std::vector<int> current_first_point = {0,0};
	std::vector<int> current_second_point = {0,0};
	std::vector<int> miner = {};
	std::vector<std::vector<int>> miners_coordinates = {};
	std::vector<Item*> items;
	

	virtual void draw(char buffor[80][25], Color color[80][25]) const;
};

