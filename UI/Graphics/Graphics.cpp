#include "Graphics.h"

Graphics::Graphics(RectangleBox rectangle, HANDLE outputConsole, HANDLE inputConsole)
{
	_outputConsole = outputConsole;
	_inputConsole = inputConsole;

	_screenBuffer = new CHAR_INFO[rectangle.Width * rectangle.Height];

	_bufferCoords.X = 0;
	_bufferCoords.Y = 0;

	_bufferSize.X = rectangle.Width;
	_bufferSize.Y = rectangle.Height;

	_rectangle = rectangle;

	_writeRegion = rectangle;

	for (int i = 0; i < rectangle.Width * rectangle.Height; i++)
	{
		_screenBuffer[i].Char.UnicodeChar = L' ';
		_screenBuffer[i].Attributes = DEFAULT_COLOR;
	}
}

void Graphics::Invalidate()
{
	WriteConsoleOutput(
		_outputConsole,
		_screenBuffer,
		_bufferSize,
		_bufferCoords,
		&_writeRegion
	);
}

void Graphics::DrawRectangle(RectangleBox rectangle, Color color)
{
	for (int i = rectangle.Y; i < rectangle.Y + rectangle.Height; i++)
		DrawLine(rectangle.X, i, rectangle.Width, L' ', L' ', L' ', color);
}

void Graphics::DrawShadow(RectangleBox rectangle)
{
	DrawRectangle(rectangle.GetShadow(), BACKGROUND_BLACK);
}

void Graphics::DrawBox(RectangleBox rectangle, RectangleBox maxRectangle, Color color, bool fill)
{
	int x = rectangle.X;
	int y = rectangle.Y;
	int width = rectangle.Width;
	int height = rectangle.Height;

	RectangleBox intersection = maxRectangle.Intersection(rectangle);

	for (int i = intersection.Y; i < intersection.Y + intersection.Height; i++)
	{
		if (i == y)
		{
			DrawLine(intersection.X, i, intersection.Width,
				intersection.X <= x ? L'╔' : -1,
				intersection.X + intersection.Width >= x + width ? L'╗' : -1,
				L'═',
				color);
		}
		else if (i == y + height - 1)
		{
			DrawLine(intersection.X, i, intersection.Width,
				intersection.X <= x ? L'╚' : -1,
				intersection.X + intersection.Width >= x + width ? L'╝' : -1,
				L'═',
				color);
		}
		else
		{
			DrawLine(intersection.X, i, intersection.Width,
				intersection.X <= x ? L'║' : -1,
				intersection.X + intersection.Width >= x + width ? L'║' : -1,
				fill ? L' ' : -1,
				color);
		}
	}
}

void Graphics::DrawLine(int x, int y, int width, Char start, Char end, Char mid, Color color)
{
	for (int i = x; i < x + width; i++)
	{
		Char c = mid;
		if (i == x && start != -1)
			c = start;
		if (i == x + width - 1 && end != -1)
			c = end;
		SetChar(i, y, c, color);
	}
}

void Graphics::CreateText(int x, int y, RectangleBox rectangle, String text, Color color)
{
	if (!rectangle.Contains(x, y))
		return;

	Point coords = { x,  y};
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == L'\n')
		{
			coords.Y++;
			coords.X = x;
			continue;
		}

		if (rectangle.Contains(coords.X, coords.Y))
			SetChar(coords.X, coords.Y, text[i], color);
		coords.X++;
	}
}

void Graphics::SetChar(int x, int y, Char c, Color color)
{
	if (!_rectangle.Contains(x, y))
		return;
	int index = x + _bufferSize.X * y;
	_screenBuffer[index].Char.UnicodeChar = c;
	_screenBuffer[index].Attributes = color;
}

int Graphics::Clamp(int value, int min, int max)
{
	return max(min, min(value, max));
}