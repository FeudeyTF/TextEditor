#pragma once
#include "Button.h";

class NavbarMenu : public Control
{
    private: vector<Button*> _buttons;

    public: NavbarMenu(int x, int y, int width, int height, Color color, vector<Button*> buttons);

    ~NavbarMenu();

    public: void Draw(HANDLE console) override;

    public: Control* HandleMouseEvent(MouseEventArgs args) override;
};

