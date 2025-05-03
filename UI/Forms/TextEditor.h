#pragma once
#include "../Elements/NavbarMenu.h"
#include "../Elements/Box.h"
#include "../Elements/Input.h"


class TextEditor
{
    private: Input* _textInput;

    private: vector<Control*> _controls;

    private: HANDLE _outputConsole;

    private: HANDLE _inputConsole;

    private: DWORD _oldConsoleMode;

    public: TextEditor(HANDLE outputConsole, HANDLE inputConsole);

    ~TextEditor();

    public: void Run();

    private: void HandleMouseEvent(MOUSE_EVENT_RECORD args);

    private: void HandleKeyEvent(KEY_EVENT_RECORD args);

    public: void Invalidate(RectangleBox rectangle);
};

