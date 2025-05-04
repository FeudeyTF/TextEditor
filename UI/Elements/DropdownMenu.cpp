#include "DropdownMenu.h"

DropdownMenu::DropdownMenu(RectangleBox rectangle, Color color, vector<Button*> buttons) : Control(rectangle, color)
{
	_buttons = buttons;
}

void DropdownMenu::Draw(RectangleBox rectangle, HANDLE console)
{
	if (!Active)
		return;

	RectangleBox shadowRight = RectangleBox(Rectangle.X + Rectangle.Width, Rectangle.Y + 1, 2, Rectangle.Height);
	RectangleBox shadowBottom = RectangleBox(Rectangle.X + 1, Rectangle.Y + Rectangle.Height, Rectangle.Width, 1);
	DrawRectangle(shadowRight, BACKGROUND_BLACK, console);
	DrawRectangle(shadowBottom, BACKGROUND_BLACK, console);

	DrawBox(Rectangle, rectangle, BackgroundColor, true, console);

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->Rectangle.Width = Rectangle.Width - 4;
		_buttons[i]->Rectangle.Height = 1;
		_buttons[i]->Rectangle.X = Rectangle.X + (Rectangle.Width - _buttons[i]->Rectangle.Width) / 2;
		_buttons[i]->Rectangle.Y = Rectangle.Y + i + 1;
		_buttons[i]->Draw(rectangle, console);
	}
}

Control* DropdownMenu::HandleMouseEvent(MouseEventArgs args)
{
	if (!Active)
		return nullptr;
	for (Button* button : _buttons)
	{
		if(button->HandleMouseEvent(args))
			return button;
	}

	Control::HandleMouseEvent(args);

	return nullptr;
}