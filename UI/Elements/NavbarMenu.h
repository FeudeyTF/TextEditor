#pragma once
#include "Button.h"
#include "DropdownMenu.h"

class NavbarMenu : public Control
{
    private: vector<Button*> _buttons;

    private: vector<DropdownMenu*> _menus;

    public: NavbarMenu(RectangleBox rectangle, Color color, vector<Button*> buttons, vector<DropdownMenu*> menus);

    ~NavbarMenu();

    public: void Draw(RectangleBox rectangle, HANDLE console) override;

    public: Control* HandleMouseEvent(MouseEventArgs args) override;
};

