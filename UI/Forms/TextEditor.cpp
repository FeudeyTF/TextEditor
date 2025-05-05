#include "TextEditor.h"
#include <fstream> 

#define NAVBAR_COLOR BACKGROUND_CYAN
#define EDITOR_COLOR BACKGROUND_BLUE

void SaveFileWithText(string path, string text);

RectangleBox ConsoleBox = RectangleBox(0, 0, 120, 30);

void OnButtonEnter(Control* sender, MouseEventArgs args)
{
	sender->BackgroundColor = BACKGROUND_BLACK | FOREGROUND_WHITE;
}

void OnButtonLeave(Control* sender, MouseEventArgs args)
{
	sender->BackgroundColor = NAVBAR_COLOR;
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
	FilePath = "";

	vector<Button*> navbarButtons{};
	Button* fileButton = new Button("File", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	Button* saveButton = new Button("Save", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	Button* exitButton = new Button("Exit", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	saveButton->OnClick += bind(&TextEditor::HandleSaveButtonClick, this, placeholders::_1, placeholders::_2);
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
	fileMenuSaveButton->OnClick += bind(&TextEditor::HandleSaveButtonClick, this, placeholders::_1, placeholders::_2);

	Button* fileMenuNewButton = new Button("New", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	fileMenuNewButton->OnMouseEnter += OnButtonEnter;
	fileMenuNewButton->OnMouseLeave += OnButtonLeave;

	Button* fileMenuOpenButton = new Button("Open", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR);
	fileMenuOpenButton->OnMouseEnter += OnButtonEnter;
	fileMenuOpenButton->OnMouseLeave += OnButtonLeave;

	DropdownMenu* fileMenu = new DropdownMenu(RectangleBox{ 0, 0, 20, 10 }, NAVBAR_COLOR | FOREGROUND_WHITE, { fileMenuNewButton, fileMenuOpenButton, fileMenuSaveButton });

	NavbarMenu* menu = new NavbarMenu(RectangleBox{ 0, 0, 120, 1 }, NAVBAR_COLOR, navbarButtons, { fileMenu }, this);

	Box* box = new Box(RectangleBox{ 0, 1, 120, 29 }, true, true, EDITOR_COLOR);
	TextInput = new Input(RectangleBox{ 1, 2, 118, 27 }, EDITOR_COLOR);

	_controls.push_back(menu);
	_controls.push_back(box);
	_controls.push_back(TextInput);

	FileNameInputModal = new InputModal("Enter new file name", ConsoleBox.GetCenteredRectangle(80, 6), BACKGROUND_WHITE, BACKGROUND_CYAN);
	FileNameInputModal->OnClose += bind(&TextEditor::HandleFileNameModalClose, this, placeholders::_1, placeholders::_2);
	FileNameInputModal->OnSubmit += bind(&TextEditor::HandleFileNameModalSubmit, this, placeholders::_1, placeholders::_2);
	_modals.push_back(FileNameInputModal);
}

TextEditor::~TextEditor()
{
	for (int i = 0; i < _controls.size(); i++)
		delete _controls[i];
	for (int i = 0; i < _modals.size(); i++)
		delete _modals[i];
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

	Invalidate(ConsoleBox);

	while (true)
	{
		if (!ReadConsoleInput(_inputConsole, inputBuffer, 128, &recordsCount))
			return;
		//SetConsoleCursorPosition(_outputConsole, _textInput->InputPoint);
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
	for (Modal* modal : _modals)
	{
		if (!modal->Active)
			continue;
		Control* updatedControl = modal->HandleMouseEvent(MouseEventArgs(args, _outputConsole));
		if (updatedControl != nullptr)
		{
			CONSOLE_CURSOR_INFO cursor = { 1, false };
			SetConsoleCursorInfo(_outputConsole, &cursor);
			updatedControl->Draw(ConsoleBox, _outputConsole);
			return;
		}
	}

	for (Control* control : _controls)
	{
		if (!control->Active)
			continue;
		Control* updatedControl = control->HandleMouseEvent(MouseEventArgs(args, _outputConsole));
		if (updatedControl != nullptr)
		{
			CONSOLE_CURSOR_INFO cursor = { 1, false };
			SetConsoleCursorInfo(_outputConsole, &cursor);
			updatedControl->Draw(ConsoleBox, _outputConsole);
			return;
		}
	}
}

void TextEditor::HandleKeyEvent(KEY_EVENT_RECORD args)
{
	KeyEventArgs keyEventArgs = KeyEventArgs(args, _outputConsole);

	for (Modal* modal : _modals)
	{
		if (!modal->Active)
			continue;
		Control* updatedControl = modal->HandleKeyEvent(keyEventArgs);
		if (updatedControl != nullptr)
		{
			CONSOLE_CURSOR_INFO cursor = { 1, true };
			SetConsoleCursorInfo(_outputConsole, &cursor);
			return;
		}
	}

	for (Control* control : _controls)
	{
		if (!control->Active)
			continue;
		Control* updatedControl = control->HandleKeyEvent(keyEventArgs);
		if (updatedControl != nullptr)
		{
			CONSOLE_CURSOR_INFO cursor = { 1, true };
			SetConsoleCursorInfo(_outputConsole, &cursor);
			return;
		}
	}
}

void TextEditor::Invalidate(RectangleBox rectangle)
{
	for (Control* control : _controls)
	{
		if (control->Active)
			control->Draw(rectangle, _outputConsole);
	}

	for (Modal* modal : _modals)
	{
		if (modal->Active)
			modal->Draw(rectangle, _outputConsole);
	}
}

void TextEditor::HandleFileNameModalClose(Modal* modal, int arg)
{
	FileNameInputModal->Active = false;
	RectangleBox modalBox = FileNameInputModal->Rectangle;
	Invalidate({ modalBox.X, modalBox.Y, modalBox.Width + 2, modalBox.Height + 1 });
}

void TextEditor::HandleFileNameModalSubmit(Modal* modal, int arg)
{
	FilePath = FileNameInputModal->TextInput->Text;
	SaveFileWithText(FilePath, TextInput->Text);
	FileNameInputModal->Active = false;
	RectangleBox modalBox = FileNameInputModal->Rectangle;
	Invalidate({ modalBox.X, modalBox.Y, modalBox.Width + 2, modalBox.Height + 1 });
}

void TextEditor::HandleSaveButtonClick(Control* sender, MouseEventArgs args)
{
	if (FilePath.empty())
	{
		FileNameInputModal->Active = true;
		FileNameInputModal->Draw(ConsoleBox, args.OutputConsole);
	}
	else
		SaveFileWithText(FilePath, TextInput->Text);
}

void SaveFileWithText(string filePath, string text)
{
	if (!text.empty())
	{
		string buffer;
		ofstream file;
		file.open(filePath);
		file << text;
		file.close();
	}
}