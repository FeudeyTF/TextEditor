#include "NavbarMenu.h"

NavbarMenu::NavbarMenu(RectangleBox rectangle, Color color, vector<Button*> buttons, vector<DropdownMenu*> menus, Graphics* graphics) : Control(rectangle, color, graphics)
{
	_menus = menus;

	int maxTextSize = 0;
	for (Button* button : buttons)
		if (button->Text.size() > maxTextSize)
			maxTextSize = (int)button->Text.size();
	maxTextSize += 2;

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Rectangle.Width = maxTextSize;
		buttons[i]->Rectangle.Height = 1;
		buttons[i]->Rectangle.X = Rectangle.X + i * maxTextSize + i + 1;
		buttons[i]->Rectangle.Y = Rectangle.Y;

		buttons[i]->OnMouseEnter += [this, i](Control* sender, MouseEventArgs args)
		{
			if (i < _menus.size())
			{
				_menus[i]->Active = true;
			}
		};

		buttons[i]->OnMouseLeave += [this, i](Control* sender, MouseEventArgs args)
		{
			if (i < _menus.size() && !_menus[i]->Rectangle.Contains(args.X, args.Y))
			{
				_menus[i]->Active = false;
			}
		};

		_buttons.push_back(buttons[i]);
	}

	for (int i = 0; i < _menus.size(); i++)
	{
		DropdownMenu* menu = _menus[i];
		menu->Active = false;
		menu->Rectangle.X = Rectangle.X +  i * (menu->Rectangle.Width - _buttons[i]->Rectangle.Width)/ 2 + 1;
		menu->Rectangle.Y = Rectangle.Y + 1;

		_menus[i]->OnMouseLeave += [this, i](Control* sender, MouseEventArgs args)
		{
			if (!_buttons[i]->Rectangle.Contains(args.X, args.Y))
			{
				_menus[i]->Active = false;
			}
		};
	}
}

NavbarMenu::~NavbarMenu()
{
	for (int i = 0; i < _buttons.size(); i++)
		delete _buttons[i];
}

void NavbarMenu::Draw(RectangleBox rectangle)
{
	_graphics->DrawRectangle(rectangle.Intersection(Rectangle), BackgroundColor);
	for (Button* button: _buttons)
		if (button->Active)
		button->Draw(rectangle);

	for (DropdownMenu* menu : _menus)
		if (menu->Active)
			menu->Draw(rectangle);
}

Control* NavbarMenu::HandleMouseEvent(MouseEventArgs args)
{
	for (DropdownMenu* menu : _menus)
	{
		if (menu->Active)
		{
			Control* control = menu->HandleMouseEvent(args);
			if (control)
				return control;
		}
	}
	for (Button* button : _buttons)
	{
		if (button->Active)
		{
			Control* control = button->HandleMouseEvent(args);
			if (control)
				return control;
		}
	}
	return nullptr;
}