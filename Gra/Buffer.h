#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Color.h"

class Buffer
{
public:
	char contents[80][25];
	char previous_contents[80][25];
	Color colors[80][25];
	Color previous_colors[80][25];
	void display();
	void clear();
	void draw(Drawable*);
	void setCursorVisibility(bool);
	Buffer();
};

