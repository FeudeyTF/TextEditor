#include "SearchInput.hpp"

SearchInput::SearchInput(RectangleBox rectangle, Color color, Graphics* graphics) : Input(rectangle, color, graphics)
{
}

void SearchInput::Draw(RectangleBox rectangle)
{
    String text = GetString();
	_graphics->DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor);
	_graphics->CreateText(Rectangle.X, Rectangle.Y, rectangle, text, BackgroundColor);
    if (!SearchPattern.empty())
    {
        for (int i = 0; i < _text.size(); i++)
        {
            String text = _text[i];
            size_t index = 0;
            while ((index = text.find(SearchPattern, index)) != string::npos)
            {
                _graphics->CreateText(Rectangle.X + index, Rectangle.Y + i, rectangle, SearchPattern, BACKGROUND_YELLOW);
                index += SearchPattern.length();
            }
        }
    }
}