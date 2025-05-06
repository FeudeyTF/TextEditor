#include "Input.h"

Input::Input(RectangleBox rectangle, Color color, Graphics* graphics) : Control(rectangle, color, graphics)
{
	InputPoint = { (short)Rectangle.X, (short)Rectangle.Y };
}

void Input::Draw(RectangleBox rectangle)
{
	_graphics->DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor);
	_graphics->CreateText(Rectangle.X, Rectangle.Y, rectangle, Text, BackgroundColor);
}

Control* Input::HandleMouseEvent(MouseEventArgs args)
{
	return nullptr;
}

Control* Input::HandleKeyEvent(KeyEventArgs args)
{
	if (args.Status == KeyStatus::Pressed)
	{
		if (args.Char > 31)
		{
			if (InputPoint.X == Rectangle.X + Rectangle.Width)
			{
				if (InputPoint.Y < Rectangle.Height - 1)
				{
					InputPoint.Y++;
					InputPoint.X = Rectangle.X;
					Text += L'\n';
				}
				else
					return nullptr;
			}
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);
			Text += args.Char;
			InputPoint.X++;
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);
			return this;
		}
		else if (args.Char == '\r')
		{
			if (InputPoint.Y < Rectangle.Y + Rectangle.Height - 1)
			{
				InputPoint.Y++;
				InputPoint.X = Rectangle.X;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				Text += L'\n';
			}
			return this;
		}
		else if (args.Char == '\b')
		{
			if (Text.size() > 0)
			{
				Text.pop_back();
				if (InputPoint.X == Rectangle.X)
				{
					InputPoint.Y--;
					for (int i = (int)Text.size() - 1; i >= 0 && Text[i] != '\n'; i--)
						InputPoint.X++;
				}
				else
					InputPoint.X--;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				return this;
			}
		}
	}
	return nullptr;
}