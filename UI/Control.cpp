#include "Control.hpp"

Control::Control(RectangleBox rectangle, Color color, Graphics* graphics)
{
	Rectangle = rectangle;
	BackgroundColor = color;
	Active = true;
	_mouseInControl = false;
	_graphics = graphics;
}

void Control::Draw(RectangleBox rectangle)
{
}

RectangleBox Control::GetInvalidationRectangle()
{
	return Rectangle;
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