#pragma once
#include "../Control.h"

typedef COORD Point;

class Input : public Control
{
	public: string Text;

	public: Point InputPoint;

	public: Input(RectangleBox rectangle, Color color);

	public: virtual void Draw(RectangleBox rectangle, HANDLE console);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;

	public: virtual Control* HandleKeyEvent(KeyEventArgs args) override;
};

