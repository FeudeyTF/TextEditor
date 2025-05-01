#include "Control.h";

void Control::Draw(HANDLE console)
{
}


Control* Control::HandleKeyEvent(KeyEventArgs args)
{
	return nullptr;
}

Control* Control::HandleMouseEvent(MouseEventArgs args)
{
	switch (args.EventType)
	{
		case MouseEventType::MouseMoved:
		{
			if (IsPointInControl(args.X, args.Y))
			{
				if (!_mouseInControl)
				{
					_mouseInControl = true;
					OnMouseEnter.Invoke(this, args);
					return this;
				}
			}
			else
			{
				if (_mouseInControl)
				{
					OnMouseLeave.Invoke(this, args);
					_mouseInControl = false;
					return this;
				}
			}
		}
		break;
		case MouseEventType::LeftMouseButton:
		{
			if (IsPointInControl(args.X, args.Y))
			{
				OnClick.Invoke(this, args);
				return this;
			}
		}
		break;
	}
	return nullptr;
}

bool Control::IsPointInControl(int x, int y)
{
	return x >= X && y >= Y && x < X + Width && y < Y + Height;
}

void Control::DrawRectangle(int x, int y, int width, int height, Color color, HANDLE console)
{
	SetConsoleTextAttribute(console, color);
	for (int i = X; i < X + Width; i++)
	{
		for (int j = Y; j < Y + Height; j++)
		{
			SetConsoleCursorPosition(console, { (short)i , (short)j });
			cout << " ";
		}
	}
	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}

void Control::DrawBox(int x, int y, int width, int height, Color color, bool fill, HANDLE console)
{
	SetConsoleTextAttribute(console, color);
	for (short i = x; i < x + width; i++)
	{
		for (short j = y; j < y + height; j++)
		{
			char c = 0;
			if (i == x && j == y)
				c = 0xC9;
			else if (i == x && j == y + height - 1)
				c = 0xC8;
			else if (i == x + width - 1 && j == y)
				c = 0xBB;
			else if (i == x + width - 1 && j == y + height - 1)
				c = 0xBC;
			else if (i == x || i == x + width - 1)
				c = 0xBA;
			else if (j == y || j == y + height - 1)
				c = 0xCD;
			else if (fill)
				c = ' ';

			if (c != 0)
			{
				SetConsoleCursorPosition(console, { i, j });
				cout << c;
			}
		}
	}

	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}

void Control::CreateText(int x, int y, string text, Color color, HANDLE console)
{
	SetConsoleTextAttribute(console, BackgroundColor);
	COORD coords = { x, y };
	SetConsoleCursorPosition(console, coords);
	cout << text;
	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}