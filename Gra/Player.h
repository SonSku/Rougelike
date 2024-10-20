#pragma once
#include "Sprite.h"
#include "Drawable.h"
#include "Character.h"


class Player : public Character
{
public:
	Player();
	int lightRadius = 80;
};

