#pragma once
#include "../Elements/NavbarMenu.h"
#include "../Elements/Box.h"
typedef COORD Point;

class TextEditor
{
    private: vector<Control*> _controls;

    private: HANDLE _outputConsole;

    private: HANDLE _inputConsole;

    private: DWORD _oldConsoleMode;

    private: Point _inputPoint;

    public: TextEditor(HANDLE outputConsole, HANDLE inputConsole);

    ~TextEditor();

    public: void Run();

    private: void HandleMouseEvent(MOUSE_EVENT_RECORD args);

    private: void HandleKeyEvent(KEY_EVENT_RECORD args);
};

