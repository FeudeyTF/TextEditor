#pragma once
#include "Button.h"

class DropdownMenu : public Control
{
	public: bool Active;

	private: vector<Button*> _buttons;

	public: DropdownMenu(RectangleBox rectangle, Color backgroundColor, vector<Button*> buttons);

	public: virtual void Draw(RectangleBox rectangle, HANDLE console) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args);
};

