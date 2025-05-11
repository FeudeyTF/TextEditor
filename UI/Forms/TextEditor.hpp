#pragma once
#include "../Elements/NavbarMenu.hpp"
#include "../Elements/Box.hpp"
#include "../Elements/SearchInput.hpp"
#include "../Modals/InputModal.hpp"

class TextEditor
{
    public: InputModal* FileNameInputModal;

    public: InputModal* SearchInpuModal;

    public: SearchInput* TextInput;

    public: String FilePath;

    private: vector<Control*> _controls;

    private: vector<Modal*> _modals;

    private: HANDLE _outputConsole;

    private: HANDLE _inputConsole;

    private: DWORD _oldConsoleMode;

    private: Graphics* _graphics;

    public: TextEditor(HANDLE outputConsole, HANDLE inputConsole);

    ~TextEditor();

    public: void Run();

    public: void Invalidate(RectangleBox rectangle);

    private: void HandleMouseEvent(MOUSE_EVENT_RECORD args);

    private: void HandleKeyEvent(KEY_EVENT_RECORD args);

    private: void HandleSaveButtonClick(Control* sender, MouseEventArgs args);

    private: void HandleFileNameModalClose(Modal* sender, int arg);

    private: void HandleFileNameModalSubmit(Modal* sender, int arg);

    private: void HandleFindButtonClick(Control* sender, MouseEventArgs args);

    private: void HandleSearchModalClose(Modal* sender, int arg);

    private: void HandleSearchModalSubmit(Modal* sender, int arg);

    private: void HandleNewButtonClick(Control* sender, MouseEventArgs args);
}; 

