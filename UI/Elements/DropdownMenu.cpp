#include "DropdownMenu.hpp"

DropdownMenu::DropdownMenu(RectangleBox rectangle, Color color, vector<Button*> buttons, Graphics* graphics) : Control(rectangle, color, graphics)
{
	_buttons = buttons;
}

void DropdownMenu::Draw(RectangleBox rectangle)
{
	_graphics->DrawShadow(Rectangle);
	_graphics->DrawBox(Rectangle, Rectangle, BackgroundColor, true);

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->Rectangle.Width = Rectangle.Width - 4;
		_buttons[i]->Rectangle.Height = 1;
		_buttons[i]->Rectangle.X = Rectangle.X + (Rectangle.Width - _buttons[i]->Rectangle.Width) / 2;
		_buttons[i]->Rectangle.Y = Rectangle.Y + i + 1;
		_buttons[i]->Draw(Rectangle);
	}
}

RectangleBox DropdownMenu::GetInvalidationRectangle()
{
	return { Rectangle.X, Rectangle.Y, Rectangle.Width + 2, Rectangle.Height + 1 };
}

Control* DropdownMenu::HandleMouseEvent(MouseEventArgs args)
{
	for (Button* button : _buttons)
	{
		if (button->Active)
		{
			if (button->HandleMouseEvent(args))
				return button;
		}
	}
	
	return Control::HandleMouseEvent(args);
}