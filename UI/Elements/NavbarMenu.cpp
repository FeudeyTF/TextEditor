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
				_menus[i]->Active = true;
				_menus[i]->Draw(_menus[i]->Rectangle, args.OutputConsole);
			}
		};

		buttons[i]->OnMouseLeave += [this, i, editor](Control* sender, MouseEventArgs args)
		{
			if (i < _menus.size())
			{
				_menus[i]->Active = false;
				editor->Invalidate(_menus[i]->Rectangle);
			}
		};

		_buttons.push_back(buttons[i]);
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
	for (Button* button : _buttons)
		if (button->HandleMouseEvent(args))
			return button;
	for (DropdownMenu* menu : _menus)
		if (menu->HandleMouseEvent(args))
			return menu;
	return nullptr;
}