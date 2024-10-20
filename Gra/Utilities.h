#pragma once
#include <windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>

struct Vector2 
{
    int x;
    int y;
    int &operator[](int pos)
    {
        if (pos == 0)
        {
            return x;
        }
        else
        {
            return y;
        }
    }
    int operator[](int pos) const
    {
        if (pos == 0)
        {
            return x;
        }
        else
        {
            return y;
        }
    }
    Vector2 operator+(Vector2 vector) const
    {
        return { x + vector.x, y + vector.y };
    }
    Vector2 operator-(Vector2 vector) const
    {
        return { x - vector.x, y - vector.y };
    }
    bool operator==(Vector2 vector) const
    {
        return x == vector.x && y == vector.y;
    }
    bool operator!=(Vector2 vector) const
    {
        return x != vector.x || y != vector.y;
    }
};

inline void gotoxy(int x, int y)
{
	COORD cord;
	cord.X = x;
	cord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

inline void resizeConsole(int xs, int ys)
{
    std::ostringstream ss;
    ss << "mode con: COLS=" << xs << " LINES=" << ys;
    system(ss.str().c_str());
    HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    COORD NewSBSize;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hOut, &SBInfo);
    NewSBSize.X = xs;
    NewSBSize.Y = ys;
    SetConsoleScreenBufferSize(hOut, NewSBSize);
}

inline std::vector<Vector2> bresenham_line(int x1, int y1, int x2, int y2)
{
    std::vector<Vector2> points;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int di = 2 * dy - dx;
    int x = x1;
    int y = y1;
    while (x <= x2)
    {
        if (di < 0)
        {
            x = x + 1;
            y = y;
            di = di + 2 * (dy);
        }
        else
        {
            x = x + 1;
            y = y + 1;
            di = di + 2 * (dy - dx);
        }
        Vector2 point;
        point[0] = x;
        point[1] = y;
        points.push_back(point);
    }
    return points;
}
