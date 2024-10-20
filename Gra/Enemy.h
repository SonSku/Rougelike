#pragma once
#include "Sprite.h"
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	enum class Direction { none, up, down, left, right };

	Direction getMove(Vector2 position);
		
};

