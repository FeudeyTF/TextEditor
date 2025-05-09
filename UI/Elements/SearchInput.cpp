#include "SearchInput.h"

SearchInput::SearchInput(RectangleBox rectangle, Color color, Graphics* graphics) : Input(rectangle, color, graphics)
{
}

void SearchInput::Draw(RectangleBox rectangle)
{
	_graphics->DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor);
	_graphics->CreateText(Rectangle.X, Rectangle.Y, rectangle, Text, BackgroundColor);
    if (!SearchPattern.empty())
    {
        size_t index = 0;
        while ((index = Text.find(SearchPattern, index)) != string::npos)
        {
            int yOffset = 0;
            int xOffset = 0;
            bool foundLastNewLine = false;
            for (size_t i = index - 1; i >= 0; i--)
            {
                if (!foundLastNewLine)
                    xOffset++;
                if (Text[i] == '\n')
                {
                    foundLastNewLine = true;
                    yOffset++;
                }
            }
            if (foundLastNewLine)
                xOffset--;
            _graphics->CreateText(Rectangle.X + xOffset, Rectangle.Y + yOffset, rectangle, SearchPattern, BACKGROUND_YELLOW);
            index += SearchPattern.length();
        }
    }
}