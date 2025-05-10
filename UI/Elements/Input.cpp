#include "Input.h"

Input::Input(RectangleBox rectangle, Color color, Graphics* graphics) : Control(rectangle, color, graphics)
{
	_text = vector<String>(1);
	InputPoint = { (short)Rectangle.X, (short)Rectangle.Y };
}

void Input::Draw(RectangleBox rectangle)
{
	_graphics->DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor);
	_graphics->CreateText(Rectangle.X, Rectangle.Y, rectangle, GetString(), BackgroundColor);
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
					_text.push_back(L"");
					InputPoint.X = Rectangle.X;
				}
				else
					return nullptr;
			}

			_text[InputPoint.Y - Rectangle.Y].insert(InputPoint.X - Rectangle.X, 1, args.Char);
			InputPoint.X++;
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);
			return this;
		}
		else if (args.Char == '\r')
		{
			if (InputPoint.Y < Rectangle.Y + Rectangle.Height - 1)
			{
				InputPoint.Y++;
				_text.push_back(L"");
				InputPoint.X = Rectangle.X;
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
			}
			return this;
		}
		else if (args.Char == '\b')
		{
			if (InputPoint.Y >= Rectangle.Y && InputPoint.X >= Rectangle.X)
			{
				if (InputPoint.X == Rectangle.X)
				{
					if (InputPoint.Y > Rectangle.Y)
					{
						InputPoint.Y--;
						_text.pop_back();
						InputPoint.X = _text[InputPoint.Y - Rectangle.Y].size() + Rectangle.X;
					}
				}
				else
				{
					_text[InputPoint.Y - Rectangle.Y].replace(InputPoint.X - Rectangle.X - 1, 1, L"");
					InputPoint.X--;
				}
				SetConsoleCursorPosition(args.OutputConsole, InputPoint);
				return this;
			}
		}
		else if (args.Char == '\0')
		{
			if (args.VirtualKeyCode == LEFT_ARROW_KEY)
			{
				if (InputPoint.X > Rectangle.X)
					InputPoint.X--;
			}
			else if (args.VirtualKeyCode == RIGHT_ARROW_KEY)
			{
				if (InputPoint.X - Rectangle.X < _text[InputPoint.Y - Rectangle.Y].size())
					InputPoint.X++;
			}
			else if (args.VirtualKeyCode == UP_ARROW_KEY)
			{
				if (InputPoint.Y > Rectangle.Y)
				{
					InputPoint.Y--;
					InputPoint.X = _text[InputPoint.Y - Rectangle.Y].size() + Rectangle.X;
				}
			}
			else if (args.VirtualKeyCode == DOWN_ARROW_KEY)
			{
				if (InputPoint.Y - Rectangle.Y < _text.size())
				{
					if (InputPoint.Y - Rectangle.Y == _text.size() - 1)
						_text.push_back(L"");
					InputPoint.Y++;
					InputPoint.X = _text[InputPoint.Y - Rectangle.Y].size() + Rectangle.X;
				}
			}
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);

		}

	}
	return nullptr;
}

String Input::GetString()
{
	String result = L"";
	for (int i = 0; i < _text.size() - 1; i++)
		result += _text[i] + L'\n';
	result += _text[_text.size() - 1];
	return result;
}

void Input::Clear()
{
	InputPoint = { (short)Rectangle.X, (short)Rectangle.Y };
	for (int i = 0; i < _text.size(); i++)
		_text[i].clear();
}