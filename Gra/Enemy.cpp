#include "Enemy.h"

Enemy::Enemy()
{
	int pos_x = rand() % 78 + 1;
	int pos_y = rand() % 23 + 1;
	sprite.position = { pos_x, pos_y };
	sprite.content = 'X';
}

Enemy::Direction Enemy::getMove(Vector2 position)
{
	if (position[0] < sprite.position[0])
	{
		return Direction::left;
	}
	if (position[0] > sprite.position[0])
	{
		return Direction::right;
	}
	if (position[1] > sprite.position[1])
	{
		return Direction::up;
	}
	if (position[1] < sprite.position[1])
	{
		return Direction::down;
	}
	return Direction::none;
}