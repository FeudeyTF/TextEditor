#pragma once
#include <windows.h>
#include "Rectangle.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include <string>

using namespace std;

typedef wchar_t Char;
typedef wstring String;

class Graphics
{
	private: HANDLE _outputConsole;

	private: HANDLE _inputConsole;

	private: CHAR_INFO* _screenBuffer;

	private: RectangleBox _rectangle;

	private: COORD _bufferSize;

	private: COORD _bufferCoords;

	private: SMALL_RECT _writeRegion;

	public: Graphics(RectangleBox rectangle, HANDLE outputConsole, HANDLE inputConsole);

	public: void Invalidate();

	public: void DrawRectangle(RectangleBox rectangle, Color color);

	public: void DrawShadow(RectangleBox rectangle);

	public: void DrawBox(RectangleBox rectangle, RectangleBox maxRectangle, Color color, bool fill);

	public: void DrawLine(int x, int y, int width, Char start, Char end, Char mid, Color color);

	public: void CreateText(int x, int y, RectangleBox rectangle, String text, Color color);

	public: void SetChar(int x, int y, Char c, Color color);

	private: int Clamp(int value, int min, int max);
};

