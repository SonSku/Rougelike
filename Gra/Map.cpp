#include "Map.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

Map::Map()
{
	visible = new bool* [80];
	prev_visible = new bool* [80];
	for (int i = 0; i < 80; i++)
	{
		visible[i] = new bool[25];
		prev_visible[i] = new bool[25];
		for (int z = 0; z < 25; z++)
		{
			//if (z == 0 || z == 24 || i == 0 || i == 79)
			{
				tiles[i][z].setType(Tile::TileType::Wall);
				tiles[i][z].sprite.position[0] = i;
				tiles[i][z].sprite.position[1] = z;
			}
		}
	}
}

void Map::generate(int level)
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			{
				tiles[i][z].setType(Tile::TileType::Wall);
				tiles[i][z].sprite.position[0] = i;
				tiles[i][z].sprite.position[1] = z;
				prev_visible[i][z] = false;
			}
		}
	}
	items.clear();

	int miner_x = rand() % 78 + 1;
	int miner_y = rand() % 23 + 1;
	for (int i = 0; i < num_of_miners; i++)
	{
		int step_count = rand() % 10 + 1000;
		for (int z = 0; z < step_count; z++)
		{
			int direction = rand() % 4;
			switch (direction)
			{
			case 0:
				miner_x += 1;
				break;
			case 1:
				miner_x -= 1;
				break;
			case 2:
				miner_y += 1;
				break;
			case 3:
				miner_y -= 1;
				break;
			}
			if (miner_x < 1)
			{
				miner_x = 1;
			}
			if (miner_x > 78)
			{
				miner_x = 78;
			}
			if (miner_y < 1)
			{
				miner_y = 1;
			}
			if (miner_y > 23)
			{
				miner_y = 23;
			}
			tiles[miner_x][miner_y].setType(Tile::TileType::Floor);
			//if (z + 1 == step_count)
			{
				//tiles[miner_x][miner_y] = 'X';
				//miner = { miner_x, miner_y };
				//miners_coordinates.push_back(miner);
				//miner.clear();
			}
		}
	}

	int river_length = rand() % 30 + 10;
	int river_num = rand() % 4 + 1;

	for (int i = 0; i < river_num; i++)
	{
		int river_x = rand() % 78 + 1;
		int river_y = rand() % 23 + 1;
		for (int z = 0; z < river_length; z++)
		{
			int direction = rand() % 3 - 1;
			river_y++;
			river_x += direction;

			if (river_x < 1)
			{
				river_x = 1;
			}
			if (river_x > 78)
			{
				river_x = 78;
			}
			if (river_y < 1)
			{
				river_y = 1;
			}
			if (river_y > 23)
			{
				river_y = 23;
			}
			if (tiles[river_x][river_y].tile_type == Tile::TileType::Wall)
			{
				break;
			}
			else
			{
				tiles[river_x][river_y].setType(Tile::TileType::River);
			}
		}
	}

	first_point = { 0, 0 };
	second_point = { 0, 0 };
	current_first_point = { 0, 0 };
	current_second_point = { 0, 0 };
	//max_current_distance = 0;
	for (int i = 0; i < 100000; i++)
	{
		first_point = { rand() % 78 + 1, rand() % 23 + 1 };
		second_point = { rand() % 78 + 1, rand() % 23 + 1 };

		while (tiles[first_point[0]][first_point[1]].tile_type != Tile::TileType::Floor)
		{
			first_point = { rand() % 78 + 1, rand() % 23 + 1 };
		}
		while (tiles[second_point[0]][second_point[1]].tile_type != Tile::TileType::Floor)
		{
			second_point = { rand() % 78 + 1, rand() % 23 + 1 };
		}
		int distance = abs(first_point[0] - second_point[0]) + abs(first_point[1] - second_point[1]);

		if (distance > max_current_distance)
		{
			//if (rand() % 50 == 0)
			{
				items.emplace_back(new Item());
				//items[items.size() - 1]->sprite.position = { current_first_point[0], current_first_point[1] };
				items[items.size() - 1]->sprite.position = { current_first_point[0], current_first_point[1] };
				items[items.size() - 1]->sprite.content = '!';
				items[items.size() - 1]->name = "item";
				int random_stats = rand();
				if (random_stats % 4 == 0)
				{
					items[items.size() - 1]->strength_gain = rand() % 3 + 1;
					items[items.size() - 1]->name = "strength";
				}
				if (random_stats % 4 == 1)
				{
					items[items.size() - 1]->hp_gain = rand() % 3 + 1;
					items[items.size() - 1]->name = "hp";
				}
				if (random_stats % 4 == 2)
				{
					items[items.size() - 1]->agility_gain = rand() % 3 + 1;
					items[items.size() - 1]->name = "agitily";
				}
				if (random_stats % 4 == 3)
				{
					items[items.size() - 1]->max_hp_gain = rand() % 3 + 1;
					items[items.size() - 1]->name = "max_hp";
				}

			}
			max_current_distance = distance;
			current_first_point = first_point;
			current_second_point = second_point;
		}
	}
	tiles[current_first_point[0]][current_first_point[1]].setType(Tile::TileType::Stairs_up);
	tiles[current_second_point[0]][current_second_point[1]].setType(Tile::TileType::Stairs_down);
	

	
	/*
	for (int i = 0; i < miners_coordinates.size(); i++)
	{
		for (int z = 0; z < miners_coordinates.size(); z++)
		{
			if (i != z)
			{
				int distance = abs(miners_coordinates[i][0] - miners_coordinates[z][0]) + abs(miners_coordinates[i][1] - miners_coordinates[z][1]);
				if (distance > max_distance)
				{
					first_point.clear();
					second_point.clear();
					max_distance = distance;
					first_point = miners_coordinates[i];
					second_point = miners_coordinates[z];
				}
			}
			
		}
	}
	tiles[first_point[0]][first_point[1]] = '1';
	tiles[second_point[0]][second_point[1]] = '2';
	*/
}

void Map::draw(char buffor[80][25], Color color[80][25]) const
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			//tiles[i][z].changeColorToSeen();
			//if (visible[i][z])
			{
				tiles[i][z].sprite.draw(buffor, color);
			}
		}
	}
	for (auto x : items)
	{
		if (visible[x->sprite.position.x][x->sprite.position.y])
		{
			x->sprite.draw(buffor, color);
		}
	}
}

void Map::updateVisibility(Player& player)
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			visible[i][z] = false;
		}
	}
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			int a = i - player.sprite.position[0];
			int b = z - player.sprite.position[1];
			if (a * a + b * b < player.lightRadius * player.lightRadius)
			{
				visible[i][z] = true;
				prev_visible[i][z] = true;
				//tiles[i][z].setVisibility(Tile::Visibility::Visible);
			}
			else
			{
				visible[i][z] = false;
			}
		}
	}
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			if (visible[i][z] == true)
			{
				tiles[i][z].setVisibility(Tile::Visibility::Visible);
			}
			if (prev_visible[i][z] == true && visible[i][z] == false)
			{
				tiles[i][z].setVisibility(Tile::Visibility::Seen);
			}
			if (prev_visible[i][z] == false && visible[i][z] == false)
			{
				tiles[i][z].setVisibility(Tile::Visibility::Never_seen);
			}
		}
	}
}
