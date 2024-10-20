#include "Buffer.h"
#include "Utilities.h"


Buffer::Buffer()
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			contents[i][z] = ' ';
			previous_contents[i][z] = ' ';
			colors[i][z].changeToDefaultColor();
			previous_colors[i][z].changeToDefaultColor();
		}
	}
}

void Buffer::display()
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			if (previous_contents[i][z] != contents[i][z] || previous_colors[i][z] != colors[i][z])
			{
				previous_contents[i][z] = contents[i][z];
				previous_colors[i][z] = colors[i][z];
				colors[i][z].changeColor();
				gotoxy(i, z);
				printf("%c", contents[i][z]);
			}
		}
	}
}

void Buffer::clear()
{
	for (int i = 0; i < 80; i++)
	{
		for (int z = 0; z < 25; z++)
		{
			contents[i][z] = ' ';
			colors[i][z].background_color = 0;
			colors[i][z].foreground_color = 7;
		}
	}
}

void Buffer::draw(Drawable* drawable)
{
	drawable->draw(contents, colors);
}

void Buffer::setCursorVisibility(bool visible)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo); // Get current cursor size
	structCursorInfo.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
}