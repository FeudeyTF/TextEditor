#include "Button.hpp"

Button::Button(String text, RectangleBox rectangle, Color color, Graphics* graphics) : Control(rectangle, color, graphics)
{
	Text = text;
}

void Button::Draw(RectangleBox rectangle)
{
	_graphics->DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor);
	if (!Text.empty())
		_graphics->CreateText(Rectangle.X + (Rectangle.Width - (int)Text.size()) / 2, Rectangle.Y + Rectangle.Height / 2, rectangle, Text, BackgroundColor);
}