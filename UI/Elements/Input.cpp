#include "Input.h"

Input::Input(RectangleBox rectangle, Color color) : Control(rectangle, color)
{
	_inputPoint = { (short)Rectangle.X, (short)Rectangle.Y };
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
			if (_inputPoint.Y < Rectangle.Height)
			{
				if (_inputPoint.X == Rectangle.Width)
				{
					_inputPoint.Y++;
					_inputPoint.X = Rectangle.X;
				}
				SetConsoleCursorPosition(args.OutputConsole, _inputPoint);
				cout << args.Char;
				_inputPoint.X++;
				SetConsoleCursorPosition(args.OutputConsole, _inputPoint);
				return this;
			}
		}
		else if (args.Char == '\r')
		{
			if (_inputPoint.Y < Rectangle.Height)
			{
				_inputPoint.Y++;
				_inputPoint.X = Rectangle.X;
				SetConsoleCursorPosition(args.OutputConsole, _inputPoint);
				return this;
			}
		}
		else if (args.Char == '\b')
		{
			if (_inputPoint.X == 1)
			{
				if (_inputPoint.Y != 1)
				{
					_inputPoint.Y--;
					_inputPoint.X = 128;
					cout << " ";
					SetConsoleCursorPosition(args.OutputConsole, _inputPoint);
					return this;
				}
			}
			else
			{
				_inputPoint.X--;
				SetConsoleCursorPosition(args.OutputConsole, _inputPoint);
				cout << " ";
				SetConsoleCursorPosition(args.OutputConsole, _inputPoint);
				return this;
			}
		}
	}
	return nullptr;
}