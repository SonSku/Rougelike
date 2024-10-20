#pragma once
#include "Sprite.h"
class Character
{
public:
	Sprite sprite;
	int max_hp;
	int real_max_hp;
	int current_hp;
	int real_strength;
	int strength;
	int real_agility;
	int agility;

	void updateStats();
};

