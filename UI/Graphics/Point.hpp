#pragma once
#include <windows.h>

struct Point
{
    int X;
    int Y;
    operator COORD();
};
