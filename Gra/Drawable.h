#pragma once
#include "Color.h"
class Drawable
{
public:
	virtual void draw(char buffor[80][25], Color color[80][25]) const = 0;
};
