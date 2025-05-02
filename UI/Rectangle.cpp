#include "Rectangle.h"

RectangleBox::RectangleBox(int x, int y, int width, int height)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
};

bool RectangleBox::PointInRectangle(int x, int y)
{
	return x >= X && y >= Y && x < X + Width && y < Y + Height;
};

RectangleBox RectangleBox::Intersection(RectangleBox rectangle)
{
    int startX = X < rectangle.X ? rectangle.X : X;
    int startY = Y < rectangle.Y ? rectangle.Y : Y;
    int endX = (X + Width) < (rectangle.X + rectangle.Width) ? (X + Width) : (rectangle.X + rectangle.Width);
    int endY = (Y + Height) < (rectangle.Y + rectangle.Height) ? (Y + Height) : (rectangle.Y + rectangle.Height);
    
    if (endX <= startX || endY <= startY)
        return RectangleBox(0, 0, 0, 0);
    
    return RectangleBox(startX, startY, endX - startX, endY - startY);
}

bool RectangleBox::Contains(RectangleBox rectangle)
{
    return rectangle.X >= X && 
           rectangle.Y >= Y && 
           rectangle.X + rectangle.Width <= X + Width && 
           rectangle.Y + rectangle.Height <= Y + Height;
}