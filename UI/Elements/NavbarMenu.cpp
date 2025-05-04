#include "NavbarMenu.h";

NavbarMenu::NavbarMenu(RectangleBox rectangle, Color color, vector<Button*> buttons, vector<DropdownMenu*> menus, TextEditor* editor) : Control(rectangle, color)
{
	_menus = menus;

	int maxTextSize = 0;
	for (Button* button : buttons)
		if (button->Text.size() > maxTextSize)
			maxTextSize = button->Text.size();
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
				DropdownMenu* menu = _menus[i];
				menu->Active = true;
				RectangleBox invalidationRectangle = RectangleBox(menu->Rectangle.X, menu->Rectangle.Y, menu->Rectangle.Width + 1, menu->Rectangle.Height + 1);
				menu->Draw(invalidationRectangle, args.OutputConsole);
			}
		};

		buttons[i]->OnMouseLeave += [this, i, editor](Control* sender, MouseEventArgs args)
		{
			if (i < _menus.size() && !_menus[i]->Rectangle.Contains(args.X, args.Y))
			{
				DropdownMenu* menu = _menus[i];
				menu->Active = false;
				RectangleBox invalidationRectangle = RectangleBox(menu->Rectangle.X, menu->Rectangle.Y, menu->Rectangle.Width + 2, menu->Rectangle.Height + 1);
				editor->Invalidate(invalidationRectangle);
			}
		};

		_buttons.push_back(buttons[i]);
	}

	for (int i = 0; i < _menus.size(); i++)
	{
		DropdownMenu* menu = _menus[i];
		menu->Rectangle.X = Rectangle.X +  i * (menu->Rectangle.Width - _buttons[i]->Rectangle.Width)/ 2 + 1;
		menu->Rectangle.Y = Rectangle.Y + 1;

		_menus[i]->OnMouseLeave += [this, i, editor](Control* sender, MouseEventArgs args)
		{
			if (!_buttons[i]->Rectangle.Contains(args.X, args.Y))
			{
				DropdownMenu* menu = _menus[i];
				menu->Active = false;
				RectangleBox invalidationRectangle = RectangleBox(menu->Rectangle.X, menu->Rectangle.Y, menu->Rectangle.Width + 2, menu->Rectangle.Height + 1);
				editor->Invalidate(invalidationRectangle);
			}
		};

	}
}

NavbarMenu::~NavbarMenu()
{
	for (int i = 0; i < _buttons.size(); i++)
		delete _buttons[i];
}

void NavbarMenu::Draw(RectangleBox rectangle, HANDLE console)
{
	DrawRectangle(rectangle.Intersection(Rectangle), BackgroundColor, console);
	for (int i = 0; i < _buttons.size(); i++)
		_buttons[i]->Draw(rectangle, console);
}

Control* NavbarMenu::HandleMouseEvent(MouseEventArgs args)
{
	for (DropdownMenu* menu : _menus)
	{
		Control* control = menu->HandleMouseEvent(args);
		if (control)
			return control;
	}
	for (Button* button : _buttons)
	{
		Control* control = button->HandleMouseEvent(args);
		if (control)
			return control;
	}
	return nullptr;
}