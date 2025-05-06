#pragma once
#include "Point.h"

class RectangleBox  
{
	public: int X;  

	public: int Y;  

	public: int Width;  

	public: int Height;

	public: RectangleBox() : X(0), Y(0), Width(0), Height(0) {}

	public: RectangleBox(int x, int y, int width, int height);  

	public: bool Contains(int x, int y);  

	public: RectangleBox Intersection(RectangleBox rectangle);

	public: RectangleBox Union(RectangleBox rectangle);
	  
	public: bool Contains(RectangleBox rectangle);

	public: RectangleBox WithOffset(int offset);

	public: RectangleBox GetCenteredRectangle(int width, int height);

	public: RectangleBox GetShadow();

	public: Point Center();

	public: operator SMALL_RECT();
};