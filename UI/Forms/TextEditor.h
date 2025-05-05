#pragma once
#include "../Elements/NavbarMenu.h"
#include "../Elements/Box.h"
#include "../Elements/Input.h"
#include "../Modals/InputModal.h"

class TextEditor
{
    public: InputModal* FileNameInputModal;

    public: Input* TextInput;

    public: string FilePath;

    private: vector<Control*> _controls;

    private: vector<Modal*> _modals;

    private: HANDLE _outputConsole;

    private: HANDLE _inputConsole;

    private: DWORD _oldConsoleMode;

    public: TextEditor(HANDLE outputConsole, HANDLE inputConsole);

    ~TextEditor();

    public: void Run();

    public: void Invalidate(RectangleBox rectangle);

    private: void HandleMouseEvent(MOUSE_EVENT_RECORD args);

    private: void HandleKeyEvent(KEY_EVENT_RECORD args);

    private: void HandleSaveButtonClick(Control* sender, MouseEventArgs args);

    private: void HandleFileNameModalClose(Modal* sender, int arg);

    private: void HandleFileNameModalSubmit(Modal* sender, int arg);
}; 

