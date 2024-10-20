#pragma once
#include <windows.h>
#include <typeinfo>

class Color
{
public:
    enum class Type : int
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Aqua = 3,
        Red = 4,
        Purple = 5,
        Yellow = 6,
        White = 7,
        Gray = 8,
        Light_Blue = 9,
        Light_Green = 10,
        Light_Aqua = 11,
        Light_Red = 12,
        Light_Purple = 13,
        Light_Yellow = 14,
        Bright_White = 15
    };

	void changeColor();
    void changeToDefaultColor();

	int background_color = 0;
	int foreground_color = 7;
    bool operator == (Color);
    bool operator != (Color);
};

