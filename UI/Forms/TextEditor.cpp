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

	vector<Button*> navbarButtons{};
	Button* fileButton = new Button("File", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	Button* saveButton = new Button("Save", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	Button* exitButton = new Button("Exit", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
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

	Button* fileMenuSaveButton = new Button("Save", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	fileMenuSaveButton->OnMouseEnter += OnButtonEnter;
	fileMenuSaveButton->OnMouseLeave += OnButtonLeave;

	Button* fileMenuNewButton = new Button("New", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	fileMenuNewButton->OnMouseEnter += OnButtonEnter;
	fileMenuNewButton->OnMouseLeave += OnButtonLeave;

	Button* fileMenuOpenButton = new Button("Open", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	fileMenuOpenButton->OnMouseEnter += OnButtonEnter;
	fileMenuOpenButton->OnMouseLeave += OnButtonLeave;

	DropdownMenu* fileMenu = new DropdownMenu(RectangleBox{ 0, 1, 20, 10 }, NAVBAR_COLOR | FOREGROUND_WHITE, { fileMenuNewButton, fileMenuOpenButton, fileMenuSaveButton });
	DropdownMenu* saveMenu = new DropdownMenu(RectangleBox{ 10, 1, 20, 10 }, NAVBAR_COLOR | FOREGROUND_WHITE, { });

	NavbarMenu* menu = new NavbarMenu(RectangleBox{ 0, 0, 120, 1 }, NAVBAR_COLOR, navbarButtons, { fileMenu, saveMenu }, this);

	Box* box = new Box(RectangleBox{ 0, 1, 120, 29 }, true, true, EDITOR_COLOR);
	Input* input = new Input(RectangleBox{ 1, 2, 119, 29 }, EDITOR_COLOR);
	_textInput = input;

	_controls.push_back(menu);
	_controls.push_back(box);
	_controls.push_back(input);
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

	Invalidate({ 0, 0, 120, 30 });
	CONSOLE_CURSOR_INFO cursor = { 1, false };
	SetConsoleCursorInfo(_outputConsole, &cursor);

	while (true)
	{
		if (!ReadConsoleInput(_inputConsole, inputBuffer, 128, &recordsCount))
			return;
		SetConsoleCursorPosition(_outputConsole, _textInput->InputPoint);
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
		if (!control->Active)
			continue;
		Control* updatedControl = control->HandleMouseEvent(MouseEventArgs(args, _outputConsole));
		if (updatedControl != nullptr)
		{
			updatedControl->Draw({ 0, 0, 120, 30 }, _outputConsole);
			return;
		}
	}
}

void TextEditor::HandleKeyEvent(KEY_EVENT_RECORD args)
{
	for (Control* control : _controls)
	{
		if (!control->Active)
			continue;
		Control* updatedControl = control->HandleKeyEvent(KeyEventArgs(args, _outputConsole));
		if (updatedControl != nullptr)
			return;
	}
}

void TextEditor::Invalidate(RectangleBox rectangle)
{
	for (Control* control : _controls)
	{
		if (!control->Active)
			continue;
		control->Draw(rectangle, _outputConsole);
	}
}