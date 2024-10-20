#include "Sprite.h"

Vector2 Sprite::getPosition()
{
	return position;
}

void Sprite::setPosition(int x, int y)
{
	position = { x, y };
}

void Sprite::setColorOfSprite(int new_background_c, int new_foreground_c)
{
	color.foreground_color = new_foreground_c;
	color.background_color = new_background_c;
}

void Sprite::setColorOfSprite(Color::Type new_background_c, Color::Type new_foreground_c)
{
	setColorOfSprite(int(new_background_c), int(new_foreground_c));
}


void Sprite::draw(char buffor[80][25], Color color[80][25]) const
{
	buffor[position[0]][position[1]] = content;
	color[position[0]][position[1]].foreground_color = this->color.foreground_color;
	color[position[0]][position[1]].background_color = this->color.background_color;
}