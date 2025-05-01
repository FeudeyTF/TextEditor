#pragma once
#include "../Control.h"

typedef COORD Point;

class Input : public Control
{
	public: string Text;

	private: Point _inputPoint;

	public: Input(RectangleBox rectangle, Color color);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;

	public: virtual Control* HandleKeyEvent(KeyEventArgs args) override;
};

