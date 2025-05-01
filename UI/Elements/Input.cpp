#include "Input.h"

Input::Input(int x, int y, int width, int height, Color color)
{
	_inputPoint = { (short)x, (short)y };
	X = x;
	Y = y;
	Width = width;
	Height = height;
	BackgroundColor = color;
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
			if (_inputPoint.Y < Height)
			{
				if (_inputPoint.X == Width)
				{
					_inputPoint.Y++;
					_inputPoint.X = X;
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
			if (_inputPoint.Y < Height)
			{
				_inputPoint.Y++;
				_inputPoint.X = X;
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