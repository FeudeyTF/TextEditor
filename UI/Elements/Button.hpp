#pragma once
#include "../Control.hpp"

class Button : public Control
{
    public: String Text;

    public: Button(String text, RectangleBox rectangle, Color backgroundColor, Graphics* graphics);

    public: virtual void Draw(RectangleBox rectangle) override;
};

