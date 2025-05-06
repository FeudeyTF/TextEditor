#pragma once
#include "../Control.h"

class Input : public Control
{
	public: wstring  Text;

	public: Point InputPoint;

	public: Input(RectangleBox rectangle, Color color, Graphics* graphics);

	public: virtual void Draw(RectangleBox rectangle);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;

	public: virtual Control* HandleKeyEvent(KeyEventArgs args) override;
};

