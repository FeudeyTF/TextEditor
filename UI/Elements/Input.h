#pragma once
#include "../Control.h"

typedef COORD Point;

class Input : public Control
{
	private: Point _inputPoint;

	public: Input(int x, int y, int width, int height, Color color);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;

	public: virtual Control* HandleKeyEvent(KeyEventArgs args) override;
};

