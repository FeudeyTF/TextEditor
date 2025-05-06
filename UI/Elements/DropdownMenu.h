#pragma once
#include "Button.h"

class DropdownMenu : public Control
{
	private: vector<Button*> _buttons;

	public: DropdownMenu(RectangleBox rectangle, Color backgroundColor, vector<Button*> buttons, Graphics* graphics);

	public: virtual void Draw(RectangleBox rectangle) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;

	public: virtual RectangleBox GetInvalidationRectangle() override;
};

