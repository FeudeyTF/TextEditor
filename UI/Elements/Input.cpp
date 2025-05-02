#include "Input.h"

Input::Input(RectangleBox rectangle, Color color) : Control(rectangle, color)
{
	InputPoint = { (short)Rectangle.X, (short)Rectangle.Y };
}

Control* Input::HandleMouseEvent(MouseEventArgs args)
{
	return nullptr;
}

Control* Input::HandleKeyEvent(KeyEventArgs args)
{
	if (args.Status == KeyStatus::Pressed)
	{
		SetConsoleTextAttribute(args.OutputConsole, BackgroundColor);
		if (args.Char > 31)
		{
			if (InputPoint.Y < Rectangle.Height)
			{
				if (InputPoint.X == Rectangle.Width)
				{
					InputPoint.Y++;
					InputPoint.X = Rectangle.X;
				}
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				cout << args.Char;
				InputPoint.X++;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				return this;
			}
		}
		else if (args.Char == '\r')
		{
			if (InputPoint.Y < Rectangle.Height)
			{
				InputPoint.Y++;
				InputPoint.X = Rectangle.X;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				return this;
			}
		}
		else if (args.Char == '\b')
		{
			if (InputPoint.X == 1)
			{
				if (InputPoint.Y != 1)
				{
					InputPoint.Y--;
					InputPoint.X = 128;
					cout << " ";
					SetConsoleCursorPosition(args.OutputConsole, InputPoint);
					return this;
				}
			}
			else
			{
				InputPoint.X--;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				cout << " ";
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				return this;
			}
		}
	}
	return nullptr;
}