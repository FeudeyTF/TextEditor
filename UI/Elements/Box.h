#pragma once
#include "..\Control.h"

class Box : public Control
{
	public: bool CreateBorders;

	public: bool Fill;

	public: Box(int x, int y, int width, int height, bool fill, bool createBorders, Color color);

	public: virtual void Draw(HANDLE console) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;
};

