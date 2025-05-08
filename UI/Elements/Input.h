#pragma once
#include "../Control.h"

#define LEFT_ARROW_KEY 37
#define UP_ARROW_KEY 38
#define RIGHT_ARROW_KEY 39
#define DOWN_ARROW_KEY 40

class Input : public Control
{
	public: String Text;

	public: Point InputPoint;

	public: Input(RectangleBox rectangle, Color color, Graphics* graphics);

	public: virtual void Draw(RectangleBox rectangle) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;

	public: virtual Control* HandleKeyEvent(KeyEventArgs args) override;
};

