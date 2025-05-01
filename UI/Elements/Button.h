#pragma once
#include "../Control.h"

class Button : public Control
{
    public: string Text;

    public: Button(string text, RectangleBox rectangle, Color backgroundColor);

    public: virtual void Draw(RectangleBox rectangle, HANDLE console) override;
};

