#pragma once
#include "Drawable.h"
#include "Color.h"
#include <vector>
#include "Utilities.h"

class Sprite:public Drawable 
{
public:
	char content;
	Vector2 position = { 0,0 };
	Vector2 getPosition();
	void setPosition(int, int);
	void setColorOfSprite(int new_background_color, int new_foreground_color);
	void setColorOfSprite(Color::Type, Color::Type);
	Color color;

	virtual void draw(char buffor[80][25], Color color[80][25]) const;
};

