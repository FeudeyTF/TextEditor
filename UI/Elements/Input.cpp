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
		int index = 0;
		Point startPoint = { Rectangle.X, Rectangle.Y };
		for (int i = 0; i < Text.size(); i++)
		{
			index++;
			startPoint.X++;
			if (Text[i] == '\n')
			{
				startPoint.Y++;
				startPoint.X++;
			}
			if (startPoint.X == InputPoint.X && startPoint.Y == InputPoint.Y)
				break;
		}

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
			//Text += args.Char;
			Text.insert(index, 1, args.Char);
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
				Text.insert(index, 1, '\n');
			}
			return this;
		}
		else if (args.Char == '\b')
		{
			if (index > 0)
			{
				Text.replace(index - 1, 1, L"");
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
		else if (args.Char == '\0')
		{
			if (args.VirtualKeyCode == LEFT_ARROW_KEY)
			{
				if (InputPoint.X > Rectangle.X)
					InputPoint.X--;
			}
			else if (args.VirtualKeyCode == RIGHT_ARROW_KEY)
			{
				if (InputPoint.X < Rectangle.X + Rectangle.Width - 1)
					InputPoint.X++;
			}
			else if (args.VirtualKeyCode == UP_ARROW_KEY)
			{
				if (InputPoint.Y > Rectangle.Y)
					InputPoint.Y--;
			}
			else if (args.VirtualKeyCode == DOWN_ARROW_KEY)
			{
				if (InputPoint.Y < Rectangle.Y + Rectangle.Height - 1)
					InputPoint.Y++;
			}
			SetConsoleCursorPosition(args.OutputConsole, InputPoint);

		}

	}
	return nullptr;
}