#include "Box.h"

Box::Box(RectangleBox rectangle, bool fill, bool createBorders, Color color, Graphics* graphics) : Control(rectangle, color, graphics)
{
	Fill = fill;
	CreateBorders = createBorders;
}

void Box::Draw(RectangleBox rectangle)
{
	_graphics->DrawBox(Rectangle, rectangle, BackgroundColor, Fill);
}

Control* Box::HandleMouseEvent(MouseEventArgs args)
{
	return nullptr;
}