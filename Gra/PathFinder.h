#pragma once
#include "Map.h"
#include "Player.h"

class PathFinder
{
public:
	int dmap[80][25];
	void update(Map&, Player&);
	std::vector<Vector2> getForUpdate(int, Map&);
	bool bounds(Vector2);
	bool checkIfAll(Map&);
};

