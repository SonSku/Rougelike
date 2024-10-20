#pragma once
#include "Sprite.h"
#include <string>

class Item
{
public:
	Sprite sprite;
	std::string name;
	int hp_gain;
	int max_hp_gain;
	int strength_gain;
	int agility_gain;
};

