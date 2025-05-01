#include "Box.h"

Box::Box(int x, int y, int width, int height, bool fill, bool createBorders, Color color)
{
	Fill = fill;
	CreateBorders = createBorders;
	X = x;
	Y = y;
	Width = width;
	Height = height;
	BackgroundColor = color;
}

void Box::Draw(HANDLE console)
{
	DrawBox(X, Y, Width, Height, BackgroundColor, Fill, console);
}

Control* Box::HandleMouseEvent(MouseEventArgs args)
{
	return nullptr;
}