#include "Button.h";

Button::Button(string text, int x, int y, int width, int height, Color backgroundColor)
{
	Text = text;
	X = x;
	Y = y;
	Width = width;
	Height = height;
	BackgroundColor = backgroundColor;
}

void Button::Draw(HANDLE console)
{
	DrawRectangle(X, Y, Width, Height, BackgroundColor, console);
	if (Text != "")
		CreateText(X + (Width - Text.size()) / 2, Y + Height / 2, Text, BackgroundColor, console);
}