#include "Tile.h"

Tile::Tile()
{
	setType(TileType::Empty);
	setVisibility(Visibility::Never_seen);
}

void Tile::setVisibility(Visibility n_visibility)
{
	visibility = n_visibility;

	if (visibility == Visibility::Visible)
	{
		switch (tile_type)
		{
		case TileType::Empty:
		case TileType::Wall:
		case TileType::Floor:
		case TileType::Stairs_up:
			sprite.setColorOfSprite(Color::Type::Black, Color::Type::White);
			break;
		case TileType::Stairs_down:
			sprite.setColorOfSprite(Color::Type::Black, Color::Type::Yellow);
			break;
		case TileType::River:
			sprite.setColorOfSprite(Color::Type::Blue, Color::Type::Light_Blue);
			break;
		}
	}

	if(visibility == Visibility::Seen)
	{
		sprite.setColorOfSprite(Color::Type::Black, Color::Type::Gray);
	}

	if (visibility == Visibility::Never_seen)
	{
		sprite.setColorOfSprite(Color::Type::Black, Color::Type::Black);
	}
}

void Tile::setType(TileType type)
{
	tile_type = type;

	switch (tile_type)
	{
	case TileType::Empty:
		sprite.content = ' ';
		collision = true;
		break;
	case TileType::Wall:
		sprite.content = '#';
		collision = true;
		break;
	case TileType::Floor:
		sprite.content = '.';
		collision = false;
		break;
	case TileType::Stairs_up:
		sprite.content = '1';
		collision = false;
		break;
	case TileType::Stairs_down:
		sprite.content = '2';
		collision = false;
		break;
	case TileType::River:
		sprite.content = '~';
		collision = false;
		break;
	}
}
