#include "Control.h";

Control::Control(RectangleBox rectangle, Color color)
{
	Rectangle = rectangle;
	BackgroundColor = color;
	_mouseInControl = false;
}

void Control::Draw(RectangleBox rectangle, HANDLE console)
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
	return Rectangle.PointInRectangle(x, y);
}

void Control::DrawRectangle(RectangleBox rectangle, Color color, HANDLE console)
{
	SetConsoleTextAttribute(console, color);
	for (int i = rectangle.X; i < rectangle.X + rectangle.Width; i++)
	{
		for (int j = rectangle.Y; j < rectangle.Y + rectangle.Height; j++)
		{
			SetConsoleCursorPosition(console, { (short)i , (short)j });
			cout << " ";
		}
	}
	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}

void Control::DrawBox(RectangleBox rectangle, RectangleBox maxRectangle,  Color color, bool fill, HANDLE console)
{
	int x = rectangle.X;
	int y = rectangle.Y;
	int width = rectangle.Width;
	int height = rectangle.Height;

	SetConsoleTextAttribute(console, color);
	for (short i = x; i < x + width; i++)
	{
		for (short j = y; j < y + height; j++)
		{
			if (!maxRectangle.PointInRectangle(i, j))
				continue;

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

void Control::CreateText(int x, int y, RectangleBox rectangle, string text, Color color, HANDLE console)
{
	RectangleBox textRectangle = RectangleBox(x, y, text.size(), 1);
	textRectangle = textRectangle.Intersection(rectangle);
	if (textRectangle.Width == 0 || textRectangle.Height == 0)
		return;

	SetConsoleTextAttribute(console, BackgroundColor);
	COORD coords = { x, y };
	SetConsoleCursorPosition(console, coords);
	for (int i = 0; i < text.size(); i++)
	{
		if (i >= rectangle.Width)
			break;
		SetConsoleCursorPosition(console, { (short)(coords.X + i), (short)coords.Y });
		cout << text[i];
	}
	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}