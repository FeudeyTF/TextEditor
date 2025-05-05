#include "Control.h";

Control::Control(RectangleBox rectangle, Color color)
{
	Rectangle = rectangle;
	BackgroundColor = color;
	Active = true;
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
	return Rectangle.Contains(x, y);
}

void Control::DrawRectangle(RectangleBox rectangle, Color color, HANDLE console)
{
	SetConsoleTextAttribute(console, color);
	for (int i = rectangle.Y; i < rectangle.Y + rectangle.Height; i++)
	{
		DrawLine(rectangle.X, i, rectangle.Width, ' ', ' ', ' ', color, console);
	}
	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}

void Control::DrawShadow(RectangleBox rectangle, HANDLE console)
{
	DrawRectangle(RectangleBox(rectangle.X + 2, rectangle.Y + 1, rectangle.Width, rectangle.Height), BACKGROUND_BLACK, console);
}

void Control::DrawBox(RectangleBox rectangle, RectangleBox maxRectangle,  Color color, bool fill, HANDLE console)
{
	int x = rectangle.X;
	int y = rectangle.Y;
	int width = rectangle.Width;
	int height = rectangle.Height;

	RectangleBox intersection = maxRectangle.Intersection(rectangle);

	SetConsoleTextAttribute(console, color);

	for (int i = intersection.Y; i < intersection.Y + intersection.Height; i++)
	{
		if (i == y)
		{
			DrawLine(intersection.X, i, intersection.Width,
				intersection.X <= x ? 0xC9 : -1,
				intersection.X + intersection.Width >= x + width ? 0xBB : -1,
				0xCD,
			color, console);
		}
		else if (i == y + height - 1)
		{
			DrawLine(intersection.X, i, intersection.Width, 
				intersection.X <= x ? 0xC8 : -1,
				intersection.X + intersection.Width >= x + width ? 0xBC : -1,
				0xCD, 
			color, console);
		}
		else
		{
			DrawLine(intersection.X, i, intersection.Width, 
				intersection.X <= x ? 0xBA : -1, 
				intersection.X + intersection.Width >= x + width ? 0xBA : -1,
				fill ? ' ' : -1,
			color, console);
		}
	}

	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}

void Control::DrawLine(int x, int y, int width, char start, char end, char mid, Color color, HANDLE console)
{
	if (start != -1)
		width--;
	if (end != -1)
		width--;
	SetConsoleCursorPosition(console, { (short)x, (short)y, });
	string line = "";
	if (start != -1)
		line += start;
	if (width > 0)
		line += string(width, mid);
	if (end != -1)
		line += end;
	cout << line;
}

void Control::CreateText(int x, int y, RectangleBox rectangle, string text, Color color, HANDLE console)
{
	if (!rectangle.Contains(x, y))
		return;

	SetConsoleTextAttribute(console, BackgroundColor);
	string s = "";
	for (int i = 0; i < min(rectangle.Width, text.size()); i++)
		s += text[i];

	COORD coords = { x, y };
	SetConsoleCursorPosition(console, coords);
	cout << s;

	SetConsoleTextAttribute(console, DEFAULT_COLOR);
}