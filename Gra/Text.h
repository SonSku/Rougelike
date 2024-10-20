#pragma once
#include <string>
#include <windows.h>
#include "Drawable.h"
#include "Color.h"

class Text:public Drawable
{
public:
	std::string text;
	int x;
	int y;
	void setColorOfText(int new_background_c, int new_foreground_c);
	void setColorOfText(Color::Type, Color::Type);
	Color color;

	virtual void draw(char buffor[80][25], Color color[80][25]) const;
};

