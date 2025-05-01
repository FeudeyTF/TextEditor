#include "Button.h";

Button::Button(string text, RectangleBox rectangle, Color color) : Control(rectangle, color)
{
	Text = text;
}

void Button::Draw(RectangleBox rectangle, HANDLE console)
{
	auto inter = Rectangle.Intersection(rectangle);
	DrawRectangle(inter, BackgroundColor, console);
	if (Text != "")
		CreateText(Rectangle.X + (Rectangle.Width - Text.size()) / 2, Rectangle.Y + Rectangle.Height / 2, Text, BackgroundColor, console);
}