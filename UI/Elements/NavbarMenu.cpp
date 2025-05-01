#include "NavbarMenu.h";

NavbarMenu::NavbarMenu(int x, int y, int width, int height, Color color, vector<Button*> buttons)
{
	int maxTextSize = 0;
	for (Button* button : buttons)
		if (button->Text.size() > maxTextSize)
			maxTextSize = button->Text.size();
	maxTextSize += 2;

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Width = maxTextSize;
		buttons[i]->Height = 1;
		buttons[i]->X = X + i * maxTextSize + i + 1;
		buttons[i]->Y = Y;
		_buttons.push_back(buttons[i]);
	}

	X = x;
	Y = y;
	Width = width;
	Height = height;
	BackgroundColor = color;
}

NavbarMenu::~NavbarMenu()
{
	for (int i = 0; i < _buttons.size(); i++)
		delete _buttons[i];
}

void NavbarMenu::Draw(HANDLE console)
{
	DrawRectangle(X, Y, Width, Height, BackgroundColor, console);
	for (int i = 0; i < _buttons.size(); i++)
		_buttons[i]->Draw(console);
}

Control* NavbarMenu::HandleMouseEvent(MouseEventArgs args)
{
	for (Button* button : _buttons)
		if (button->HandleMouseEvent(args))
			return button;
	return nullptr;
}