#include "Box.hpp"

Box::Box(RectangleBox rectangle, bool fill, Color color, Graphics* graphics) : Control(rectangle, color, graphics)
{
	Fill = fill;
}

void Box::Draw(RectangleBox rectangle)
{
	_graphics->DrawBox(Rectangle, rectangle, BackgroundColor, Fill);
}

Control* Box::HandleMouseEvent(MouseEventArgs args)
{
	return nullptr;
}