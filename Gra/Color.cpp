#include "Color.h"

void Color::changeColor()
{
    int value = background_color * 16 + foreground_color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void Color::changeToDefaultColor()
{
    int value = 15;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

bool Color::operator==(Color rhs)
{
    return background_color == rhs.background_color && foreground_color == rhs.foreground_color;
}

bool Color::operator!=(Color rhs)
{
    return !((*this) == rhs);
}