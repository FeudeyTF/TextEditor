#include "Box.h"

Box::Box(RectangleBox rectangle, bool fill, bool createBorders, Color color) : Control(rectangle, color)
{
	Fill = fill;
	CreateBorders = createBorders;
}

void Box::Draw(RectangleBox rectangle, HANDLE console)
{
	RectangleBox inter = rectangle.Intersection(Rectangle);
	DrawBox(inter, BackgroundColor, Fill, console);
}

Control* Box::HandleMouseEvent(MouseEventArgs args)
{
	return nullptr;
}