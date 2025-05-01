#pragma once
#include "..\Control.h"

class Box : public Control
{
	public: bool CreateBorders;

	public: bool Fill;

	public: Box(RectangleBox rectangle, bool fill, bool createBorders, Color color);

	public: virtual void Draw(RectangleBox rectangle, HANDLE console) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;
};

