#include "Button.h"

Button::Button(string text, RectangleBox rectangle, Color color) : Control(rectangle, color)
{
	Text = text;
}

void Button::Draw(RectangleBox rectangle, HANDLE console)
{
	DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor, console);
	if (Text != "")
	{
		CreateText(Rectangle.X + (Rectangle.Width - (int)Text.size()) / 2, Rectangle.Y + Rectangle.Height / 2, rectangle, Text, BackgroundColor, console);
	}
}