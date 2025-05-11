#include "Rectangle.hpp"

RectangleBox::RectangleBox(int x, int y, int width, int height)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
};

bool RectangleBox::Contains(int x, int y)
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

RectangleBox RectangleBox::Union(RectangleBox rectangle)
{
    int startX = X < rectangle.X ? X : rectangle.X;
    int startY = Y < rectangle.Y ? Y : rectangle.Y;
    int endX = (X + Width) > (rectangle.X + rectangle.Width) ? (X + Width) : (rectangle.X + rectangle.Width);
    int endY = (Y + Height) > (rectangle.Y + rectangle.Height) ? (Y + Height) : (rectangle.Y + rectangle.Height);
    
    return RectangleBox(startX, startY, endX - startX, endY - startY);
}

bool RectangleBox::Contains(RectangleBox rectangle)
{
    return rectangle.X >= X && 
           rectangle.Y >= Y && 
           rectangle.X + rectangle.Width <= X + Width && 
           rectangle.Y + rectangle.Height <= Y + Height;
}

RectangleBox RectangleBox::WithOffset(int offset)
{
    return RectangleBox(X + 2 * offset + 1, Y + 1 * offset, Width - 4 * offset - 2, Height - 2 * offset);
}

RectangleBox RectangleBox::GetCenteredRectangle(int width, int height)
{
    return RectangleBox(X + (Width - width) / 2, Y + (Height - height) / 2, width, height);
}

RectangleBox RectangleBox::GetShadow()
{
    return RectangleBox(X + 2, Y + 1, Width, Height);
}

Point RectangleBox::Center()
{
    return { X + Width / 2, Y + Height / 2 };
}

RectangleBox::operator SMALL_RECT()
{
    SMALL_RECT result{};
    result.Left = X;
    result.Top = Y;
    result.Right = X + Width - 1;
    result.Bottom = Y + Height - 1;
    return result;
}