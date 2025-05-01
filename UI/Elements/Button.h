#pragma once
#include "../Control.h"

class Button : public Control
{
    public: string Text;

    public: Button(string text, int x, int y, int width, int height, Color backgroundColor);

    public: virtual void Draw(HANDLE console) override;
};

