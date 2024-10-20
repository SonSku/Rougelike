#include "Engine.h"
#include "Map.h"
#include <sstream>

Engine::Engine(Buffer* buffer)
{
	this->buffer = buffer;
	map.generate(level);
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			map.visible[i][z] = *visible;
			map.prev_visible[i][z] = *prev_visible;
			map.prev_visible[i][z] = false;
		}
	}
	setPlayerPosition();
	Enemy();
	enemies.emplace_back(Enemy());
	for (auto& x : enemies)
	{
		setEnemyPosition();
	}
}

void Engine::draw()
{
	buffer->draw(&map);
	buffer->draw(&player.sprite);
	for (auto& x : enemies)
	{
		if (state == State::Playing)
		{
			if (map.visible[x.sprite.position[0]][x.sprite.position[1]] == true)
			{
				buffer->draw(&x.sprite);
			}
		}
		else
		{
			buffer->draw(&x.sprite);
		}
	}
	Text hp;
	std::stringstream ss;
	ss << player.current_hp << "/" << player.max_hp;
	hp.text = "hp: " + ss.str();
	hp.x = 70;
	hp.y = 24;
	hp.setColorOfText(Color::Type::Black, Color::Type::Red);
	buffer->draw(&hp);
	buffer->display();
	buffer->clear();
}

void Engine::processAI()
{
	for (auto& x : enemies)
	{
		/*int a = (x.sprite.position[0] - player.sprite.position[0]);
		int b = (x.sprite.position[1] - player.sprite.position[1]);
		if (a * a + b + b > 36)
		{
			continue;
		}
		switch (x.getMove(player.sprite.position))
		{
		case Enemy::Direction::up:
			if (!collision(x.sprite.position[0], x.sprite.position[1] + 1))
			{
				x.sprite.position[1] += 1;
			}
			else
			{
				if (!collision(x.sprite.position[0] - 1, x.sprite.position[1]))
				{
					x.sprite.position[0] -= 1;
					break;
				}
				if (!collision(x.sprite.position[0] + 1, x.sprite.position[1]))
				{
					x.sprite.position[0] += 1;
					break;
				}
			}
			break;
		case Enemy::Direction::down:
			if (!collision(x.sprite.position[0], x.sprite.position[1] - 1))
			{
				x.sprite.position[1] -= 1;
			}
			else
			{
				if (!collision(x.sprite.position[0] - 1, x.sprite.position[1]))
				{
					x.sprite.position[0] -= 1;
					break;
				}
				if (!collision(x.sprite.position[0] + 1, x.sprite.position[1]))
				{
					x.sprite.position[0] += 1;
					break;
				}
			}
			break;
		case Enemy::Direction::left:
			if (!collision(x.sprite.position[0] - 1, x.sprite.position[1]))
			{
				x.sprite.position[0] -= 1;
			}
			else
			{
				if (!collision(x.sprite.position[0], x.sprite.position[1] + 1))
				{
					x.sprite.position[1] += 1;
					break;
				}
				if (!collision(x.sprite.position[0], x.sprite.position[1] - 1))
				{
					x.sprite.position[1] -= 1;
					break;
				}
			}
			break;
		case Enemy::Direction::right:
			if (!collision(x.sprite.position[0] + 1, x.sprite.position[1]))
			{
				x.sprite.position[0] += 1;
			}
			else
			{
				if (!collision(x.sprite.position[0], x.sprite.position[1] + 1))
				{
					x.sprite.position[1] += 1;
					break;
				}
				if (!collision(x.sprite.position[0], x.sprite.position[1] - 1))
				{
					x.sprite.position[1] -= 1;
					break;
				}
			}
			break;
		}
		*/
		int i = (x.sprite.position[0] - player.sprite.position[0]);
		int z = (x.sprite.position[1] - player.sprite.position[1]);
		if (i * i + z * z > 36)
		{
			continue;
		}

		i = x.sprite.position[0];
		z = x.sprite.position[1];

		int weight = path.dmap[i][z];

		if (!collision(i, z + 1) && path.dmap[i][z + 1] < weight)
		{
			x.sprite.position[1] += 1;
		}
		else if (!collision(i, z - 1) && path.dmap[i][z - 1] < weight)
		{
			x.sprite.position[1] -= 1;
		}
		else if (!collision(i + 1, z) && path.dmap[i + 1][z] < weight)
		{
			x.sprite.position[0] += 1;
		}
		else if (!collision(i - 1, z) && path.dmap[i - 1][z] < weight)
		{
			x.sprite.position[0] -= 1;
		}
	}
}

bool Engine::collision(int x, int y)
{
	return map.tiles[x][y].collision;
}

void Engine::setPlayerPosition()
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			if (map.tiles[i][z].tile_type == Tile::TileType::Stairs_down)
			{
				player.sprite.setPosition(i, z);
			}
		}
	}
}

void Engine::setEnemyPosition()
{
	for (auto& x : enemies)
	{
		if (map.tiles[x.sprite.position.x][x.sprite.position.y].tile_type == Tile::TileType::Wall)
		{
			while (map.tiles[x.sprite.position.x][x.sprite.position.y].tile_type == Tile::TileType::Wall)
			{
				int pos_x = rand() % 78 + 1;
				int pos_y = rand() % 23 + 1;
				x.sprite.position = { pos_x, pos_y };
			}
		}
	}
}

bool Engine::isOnStairs()
{
	return map.tiles[player.sprite.position[0]][player.sprite.position[1]].tile_type == Tile::TileType::Stairs_up;
}

bool Engine::isOnRiver(int x, int y)
{
	return map.tiles[x][y].tile_type == Tile::TileType::River;
}


void Engine::isOnItem()
{
	int idx = 0;
	for (auto x : map.items)
	{
		if (player.sprite.position.x == x->sprite.position.x && player.sprite.position.y == x->sprite.position.y)
		{
			//if (inventory.items.size() <= inventory.max_items)
			{
				inventory.items.push_back(x);
				map.items.erase(map.items.begin() + idx);


				player.agility += inventory.items[inventory.items.size() - 1]->agility_gain;
				player.max_hp += inventory.items[inventory.items.size() - 1]->max_hp_gain;
				if (player.current_hp + inventory.items[inventory.items.size() - 1]->hp_gain <= player.max_hp)
				{
					player.current_hp += inventory.items[inventory.items.size() - 1]->hp_gain;
				}
				else
				{
					player.current_hp = player.max_hp;
				}
				player.strength += inventory.items[inventory.items.size() - 1]->strength_gain;
				idx--;
			}
		}
		idx += 1;
	}
}

Character* Engine::characterAtPosition(int pos_x, int pos_y)
{
	for (auto& x : enemies)
	{
		//if (x.sprite.position == player.sprite.position)
		if (x.sprite.position.x == pos_x && x.sprite.position.y == pos_y)
		{
			return &x;
		}
	}
	return nullptr;
}

void Engine::deleteEnemy(Character* e)
{
	int l = 0;
	for (auto& x : enemies)
	{
		if (e == &x)
		{
			delete e;
			enemies.erase(enemies.begin() + l);
			break;
		}
		l += 1;
	}
}

void Engine::play()
{
	while (state == State::Playing)
	{
		if (_kbhit() != 0)
		{
			char znak;
			znak = _getch();

			Character* e;
			switch (znak)
			{
			case 'W':
			case 'w':
				e = characterAtPosition(player.sprite.position[0], player.sprite.position[1] - 1);
				if (e != nullptr)
				{
					deleteEnemy(e);
				}
				else if (!collision(player.sprite.position[0], player.sprite.position[1] - 1))
				{
					player.sprite.position[1] -= 1;
				}
				break;
			case 'S':
			case 's':
				e = characterAtPosition(player.sprite.position[0], player.sprite.position[1] + 1);
				if (e != nullptr)
				{
					player.sprite.setColorOfSprite(Color::Type::Blue, Color::Type::Green);
					deleteEnemy(e);
				}
				else if (!collision(player.sprite.position[0], player.sprite.position[1] + 1))
				{
					player.sprite.position[1] += 1;
				}
				break;
			case 'A':
			case 'a':
				e = characterAtPosition(player.sprite.position[0] - 1, player.sprite.position[1]);
				if (e != nullptr)
				{
					player.sprite.setColorOfSprite(Color::Type::Blue, Color::Type::Green);
					deleteEnemy(e);
				}
				else if (!collision(player.sprite.position[0] - 1, player.sprite.position[1]))
				{
					player.sprite.position[0] -= 1;
				}
				break;
			case 'D':
			case 'd':
				e = characterAtPosition(player.sprite.position[0] + 1, player.sprite.position[1]);
				if (e != nullptr)
				{
					deleteEnemy(e);
				}
				else if (!collision(player.sprite.position[0] + 1, player.sprite.position[1]))
				{
					player.sprite.position[0] += 1;
				}
				break;
			case 'I':
			case 'i':
				state = State::Inventory;
				break;
			}
			processAI();
			if (isOnRiver(player.sprite.position[0], player.sprite.position[1]))
			{
				player.sprite.setColorOfSprite(Color::Type::Blue, Color::Type::Red);
			}
			else
			{
				player.sprite.setColorOfSprite(Color::Type::Black, Color::Type::Red);
			}
			for (auto& x : enemies)
			{
				if (isOnRiver(x.sprite.position[0], x.sprite.position[1]))
				{
					x.sprite.setColorOfSprite(Color::Type::Blue, Color::Type::White);
				}
				else
				{
					x.sprite.setColorOfSprite(Color::Type::Black, Color::Type::White);
				}
			}
		}
		map.updateVisibility(player);
		
		/*
		for (int i = 0; i < 80; i++)
		{
			for (int z = 0; z < 25; z++)
			{
				char content;
				std::stringstream num;
				num << path.dmap[i][z];
				num >> content;
				map.tiles[i][z].sprite.content = content;
				map.tiles[i][z].sprite.setColorOfSprite(Color::Type::Black, Color::Type::Bright_White);
			}
		}*/
		draw();
		if (isOnStairs())
		{
			level += 1;
			map.generate(level);
			setPlayerPosition();
			enemies.clear();
			for (int i = 0; i < level + 1; i++)
			{
				enemies.push_back(Enemy());

			}
			setEnemyPosition();
		}
		path.update(map, player);
		isOnItem();
	}
}

void Engine::pause()
{
	while (state == State::Pause)
	{

	}
}

void Engine::loop()
{
	while (state != State::Exit)
		switch (state)
		{
			case State::Playing:
			{
				play();
				break;
			}
			case State::Pause:
			{
				pause();
				break;
			}
			case State::Inventory:
			{
				inventoryScreen();
				break;
			}
		}
}

void Engine::inventoryScreen()
{
	buffer->clear();

	while (state == State::Inventory)
	{
		//buffer->clear();

		Text text;
		text.setColorOfText(Color::Type::Red, Color::Type::White);
		text.x = 0;
		text.y = 0;
		if (inventory.items.size() == 0)
		{
			text.text = "empty";
			buffer->draw(&text);
			buffer->display();
		}
		for (auto& x : inventory.items)
		{
			std::string content;
			std::stringstream ss;
			ss << x->sprite.content;
			ss >> content;
			text.text = ("Item " + content + ": " + x->name);
			buffer->draw(&text);
			buffer->display();
			text.y++;
		}
		if (_kbhit() != 0)
		{
			char znak;
			znak = _getch();

			switch (znak)
			{
			case 'P':
			case 'p':
				state = State::Playing;
				break;
			}
		}
	}
}