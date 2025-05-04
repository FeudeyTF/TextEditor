#include "Input.h"

Input::Input(RectangleBox rectangle, Color color) : Control(rectangle, color)
{
	InputPoint = { (short)Rectangle.X, (short)Rectangle.Y };
}

void Input::Draw(RectangleBox rectangle, HANDLE console)
{
	Point coords = { Rectangle.X,  Rectangle.Y };
	SetConsoleTextAttribute(console, BackgroundColor);
	for (int i = 0; i < Text.size(); i++)
	{
		if (Text[i] == '\n')
		{
			coords.Y++;
			coords.X = Rectangle.X;
			continue;
		}
		if (rectangle.Contains(coords.X, coords.Y))
		{
			SetConsoleCursorPosition(console, coords);
			cout << Text[i];
		}
		coords.X++;
	}
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
			if (InputPoint.X == Rectangle.Width)
			{
				if (InputPoint.Y >= Rectangle.Y + Rectangle.Height)
					return nullptr;
				InputPoint.Y++;
				InputPoint.X = Rectangle.X;
			}
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);
			cout << args.Char;
			Text += args.Char;
			InputPoint.X++;
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);
			return this;
		}
		else if (args.Char == '\r')
		{
			if (InputPoint.Y < Rectangle.Height)
			{
				InputPoint.Y++;
				InputPoint.X = Rectangle.X;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				Text += '\n';
			}
		}
		else if (args.Char == '\b')
		{
			if (Text.size() > 0)
			{
				Text.pop_back();
				if (InputPoint.X == Rectangle.X)
				{
					InputPoint.Y--;
					for (int i = Text.size() - 1; i >= 0 && Text[i] != '\n'; i--)
						InputPoint.X++;
				}
				else
					InputPoint.X--;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				cout << " ";
			}
		}
	}
	return nullptr;
}