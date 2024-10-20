#include "Text.h"

void Text::setColorOfText(int new_background_c, int new_foreground_c)
{
	color.foreground_color = new_foreground_c;
	color.background_color = new_background_c;
}

void Text::setColorOfText(Color::Type new_background_c, Color::Type new_foreground_c)
{
	setColorOfText(int(new_background_c), int(new_foreground_c));
}

void Text::draw(char buffor[80][25], Color color[80][25]) const
{
	for(int i = 0; i < text.size(); i++)
	{
		char content;
		content = text[i];
		buffor[x+i][y] = content;
		color[x+i][y].foreground_color = this->color.foreground_color;
		color[x+i][y].background_color = this->color.background_color;
	}
}