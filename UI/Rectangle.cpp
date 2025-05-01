#include "Rectangle.h"

RectangleBox::RectangleBox(int x, int y, int width, int height)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
};

RectangleBox RectangleBox::Intersection(RectangleBox rectangle)
{
	return RectangleBox(
		X < rectangle.X ? rectangle.X : X,
		Y < rectangle.Y ? rectangle.Y : Y,
		Width > rectangle.Width ? rectangle.Width : Width,
		Height > rectangle.Height ? rectangle.Height : Height
	);
}

bool RectangleBox::PointInRectangle(int x, int y)
{
	return x >= X && y >= Y && x < X + Width && y < Y + Height;
};