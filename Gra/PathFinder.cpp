#include "PathFinder.h"

void PathFinder::update(Map& map, Player& player)
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			dmap[i][z] = -1;
		}
	}

	dmap[player.sprite.position.x][player.sprite.position.y] = 0;
	int weight = 0;

	while (checkIfAll(map) == false)
	{
		getForUpdate(weight, map);
		weight += 1;
	}
}

std::vector<Vector2> PathFinder::getForUpdate(int weight, Map& map)
{
	std::vector<Vector2> positions;
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			if (dmap[i][z] == weight)
			{
				Vector2 pos = { i, z };
				Vector2 hpos;
				for (int x = 0; x < 4; x++)
				{
					switch (x)
					{
					case 0:
						hpos = pos + Vector2{ 0, 1 };
						break;
					case 1:
						hpos = pos + Vector2{ 1, 0 };
						break;
					case 2:
						hpos = pos + Vector2{ 0, -1 };
						break;
					case 3:
						hpos = pos + Vector2{ -1, 0 };
						break;
					}
					if (bounds(hpos))
					{
						if (map.tiles[hpos.x][hpos.y].tile_type != Tile::TileType::Wall && dmap[hpos.x][hpos.y] == -1)
						{
							dmap[hpos.x][hpos.y] = weight + 1;
							positions.push_back(hpos);
						}
					}
				}
			}
		}
	}
	return positions;
}

bool PathFinder::bounds(Vector2 pos)
{
	return pos.x >= 0 && pos.x < 79 && pos.y >= 0 && pos.y < 24;
}

bool PathFinder::checkIfAll(Map& map)
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			if (map.tiles[i][z].tile_type != Tile::TileType::Wall && dmap[i][z] == -1)
			{
				return false;
			}
		}
	}
	return true;
}