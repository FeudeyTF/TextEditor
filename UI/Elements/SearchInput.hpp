#pragma once
#include "Input.hpp"

class SearchInput : public Input
{
	public: String SearchPattern;

	public: SearchInput(RectangleBox rectangle, Color color, Graphics* graphics);

	public: virtual void Draw(RectangleBox rectangle) override;
};

