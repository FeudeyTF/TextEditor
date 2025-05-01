#include "TextEditor.h"

#define NAVBAR_COLOR BACKGROUND_CYAN
#define EDITOR_COLOR BACKGROUND_BLUE

void OnButtonEnter(Control* sender, MouseEventArgs args)
{
	sender->BackgroundColor = BACKGROUND_BLACK | FOREGROUND_WHITE;
}

void OnButtonLeave(Control* sender, MouseEventArgs args)
{
	sender->BackgroundColor = NAVBAR_COLOR;
}

void OnSaveButtonClick(Control* sender, MouseEventArgs args)
{
	cout << "Saved";
}

void OnExitButtonClick(Control* sender, MouseEventArgs args)
{
	ExitProcess(0);
}

TextEditor::TextEditor(HANDLE outputConsole, HANDLE inputConsole)
{
	_inputConsole = inputConsole;
	_outputConsole = outputConsole;
	_oldConsoleMode = 0;
	_inputPoint = { 1, 2 };

	vector<Button*> navbarButtons{};
	Button* fileButton = new Button("File", 0, 0, 0, 0, NAVBAR_COLOR);
	Button* saveButton = new Button("Save", 0, 0, 0, 0, NAVBAR_COLOR);
	Button* exitButton = new Button("Exit", 0, 0, 0, 0, NAVBAR_COLOR);
	saveButton->OnClick += OnSaveButtonClick;
	exitButton->OnClick += OnExitButtonClick;
	navbarButtons.push_back(fileButton);
	navbarButtons.push_back(saveButton);
	navbarButtons.push_back(exitButton);
	for (Button* button : navbarButtons)
	{
		button->OnMouseEnter += OnButtonEnter;
		button->OnMouseLeave += OnButtonLeave;
	}
	NavbarMenu* menu = new NavbarMenu(0, 0, 120, 1, NAVBAR_COLOR, navbarButtons);

	Box* box = new Box(0, 1, 120, 29, true, true, EDITOR_COLOR);

	_controls.push_back(menu);
	_controls.push_back(box);
}

TextEditor::~TextEditor()
{
	for (int i = 0; i < _controls.size(); i++)
		delete _controls[i];
}

void TextEditor::Run()
{
	DWORD recordsCount;
	INPUT_RECORD inputBuffer[128];

	if (_inputConsole == INVALID_HANDLE_VALUE)
		return;

	if (!GetConsoleMode(_inputConsole, &_oldConsoleMode))
		return;

	DWORD newConsoleMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(_inputConsole, newConsoleMode))
		return;

	for (Control* control : _controls)
		control->Draw(_outputConsole);

	while (true)
	{
		SetConsoleCursorPosition(_outputConsole, _inputPoint );
		if (!ReadConsoleInput(_inputConsole, inputBuffer, 128, &recordsCount))
			return;

		for (DWORD i = 0; i < recordsCount; i++)
		{
			switch (inputBuffer[i].EventType)
			{
			case KEY_EVENT:
				HandleKeyEvent(inputBuffer[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT:
				HandleMouseEvent(inputBuffer[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT:
			case FOCUS_EVENT:
			case MENU_EVENT:
			default:
				break;
			}
		}
	}
}

void TextEditor::HandleMouseEvent(MOUSE_EVENT_RECORD args)
{
	for (Control* control : _controls)
	{
		Control* updatedControl = control->HandleMouseEvent(MouseEventArgs(args, _outputConsole));
		if (updatedControl != nullptr)
		{
			updatedControl->Draw(_outputConsole);
			return;
		}
	}
}

void TextEditor::HandleKeyEvent(KEY_EVENT_RECORD args)
{
	if (args.bKeyDown)
	{
		SetConsoleTextAttribute(_outputConsole, EDITOR_COLOR);
		if (args.uChar.AsciiChar > 31)
		{
			cout << args.uChar.AsciiChar;
			_inputPoint.X++;
		}
		else if (args.uChar.AsciiChar == '\r')
		{
			_inputPoint.Y++;
			_inputPoint.X = 1;
		}
		else if (args.uChar.AsciiChar == '\b')
		{
			if (_inputPoint.X == 1)
			{
				if (_inputPoint.Y != 1)
				{
					_inputPoint.Y--;
					_inputPoint.X = 128;
					cout << " ";
				}
			}
			else
			{
				_inputPoint.X--;
				cout << " ";
			}
		}
		SetConsoleTextAttribute(_outputConsole, DEFAULT_COLOR);
	}
}