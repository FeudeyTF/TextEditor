#include "DropdownMenu.h"

DropdownMenu::DropdownMenu(RectangleBox rectangle, Color color, vector<Button*> buttons) : Control(rectangle, color)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Rectangle.Width = Rectangle.Width - 4;
		buttons[i]->Rectangle.Height = 1;
		buttons[i]->Rectangle.X = Rectangle.X + (Rectangle.Width - buttons[i]->Rectangle.Width) / 2;
		buttons[i]->Rectangle.Y = Rectangle.Y + i + 1;
	}
	_buttons = buttons;
}

void DropdownMenu::Draw(RectangleBox rectangle, HANDLE console)
{
	if (!Active)
		return;
	DrawBox(Rectangle, rectangle, BackgroundColor, true, console);
	for (Button* button : _buttons)
		button->Draw(rectangle, console);
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