#pragma once
#include "..\Control.hpp"

class Box : public Control
{
	public: bool Fill;

	public: Box(RectangleBox rectangle, bool fill, Color color, Graphics* graphics);

	public: virtual void Draw(RectangleBox rectangle) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;
};

