#pragma once
#include "../Control.h"

class Input : public Control
{
	public: Input(int x, int y, int width, int height, Color color);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;
};

