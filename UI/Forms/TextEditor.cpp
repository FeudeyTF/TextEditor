#include "TextEditor.h"
#include <fstream> 
#include <codecvt>

#define NAVBAR_COLOR BACKGROUND_CYAN
#define EDITOR_COLOR BACKGROUND_BLUE

void SaveFileWithText(String path, String text);

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

	_graphics = new Graphics(ConsoleBox, outputConsole, inputConsole);

	vector<Button*> navbarButtons{};
	Button* fileButton = new Button(L"File", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	Button* saveButton = new Button(L"Save", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	Button* exitButton = new Button(L"Exit", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	saveButton->OnClick += bind(&TextEditor::HandleSaveButtonClick, this, placeholders::_1, placeholders::_2);
	exitButton->OnClick += OnExitButtonClick;

	Button* findButton = new Button(L"Find", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	findButton->OnMouseEnter += OnButtonEnter;
	findButton->OnMouseLeave += OnButtonLeave;
	findButton->OnClick += bind(&TextEditor::HandleFindButtonClick, this, placeholders::_1, placeholders::_2);

	navbarButtons.push_back(fileButton);
	navbarButtons.push_back(saveButton);
	navbarButtons.push_back(exitButton);
	navbarButtons.push_back(findButton);

	for (Button* button : navbarButtons)
	{
		button->OnMouseEnter += OnButtonEnter;
		button->OnMouseLeave += OnButtonLeave;
	}

	Button* fileMenuSaveButton = new Button(L"Save", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	fileMenuSaveButton->OnMouseEnter += OnButtonEnter;
	fileMenuSaveButton->OnMouseLeave += OnButtonLeave;
	fileMenuSaveButton->OnClick += bind(&TextEditor::HandleSaveButtonClick, this, placeholders::_1, placeholders::_2);

	Button* fileMenuNewButton = new Button(L"New", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	fileMenuNewButton->OnMouseEnter += OnButtonEnter;
	fileMenuNewButton->OnMouseLeave += OnButtonLeave;
	fileMenuNewButton->OnClick += bind(&TextEditor::HandleNewButtonClick, this, placeholders::_1, placeholders::_2);


	Button* fileMenuOpenButton = new Button(L"Open", RectangleBox{ 0, 0, 0, 0 }, NAVBAR_COLOR, _graphics);
	fileMenuOpenButton->OnMouseEnter += OnButtonEnter;
	fileMenuOpenButton->OnMouseLeave += OnButtonLeave;

	DropdownMenu* fileMenu = new DropdownMenu({ 0, 0, 20, 10 }, NAVBAR_COLOR | FOREGROUND_WHITE, { fileMenuNewButton, fileMenuOpenButton, fileMenuSaveButton }, _graphics);

	NavbarMenu* menu = new NavbarMenu({ 0, 0, 120, 1 }, NAVBAR_COLOR, navbarButtons, { fileMenu }, _graphics);

	Box* box = new Box({ 0, 1, 120, 29 }, true, EDITOR_COLOR, _graphics);
	TextInput = new SearchInput({ 1, 2, 118, 27 }, EDITOR_COLOR, _graphics);

	_controls.push_back(box);
	_controls.push_back(TextInput);
	_controls.push_back(menu);

	FileNameInputModal = new InputModal(L"Enter file name", ConsoleBox.GetCenteredRectangle(80, 6), BACKGROUND_WHITE, BACKGROUND_CYAN, _graphics);
	FileNameInputModal->OnClose += bind(&TextEditor::HandleFileNameModalClose, this, placeholders::_1, placeholders::_2);
	FileNameInputModal->OnSubmit += bind(&TextEditor::HandleFileNameModalSubmit, this, placeholders::_1, placeholders::_2);
	

	SearchInpuModal = new InputModal(L"Enter string to find", ConsoleBox.GetCenteredRectangle(80, 6), BACKGROUND_WHITE, BACKGROUND_CYAN, _graphics);
	SearchInpuModal->OnClose += bind(&TextEditor::HandleSearchModalClose, this, placeholders::_1, placeholders::_2);
	SearchInpuModal->OnSubmit += bind(&TextEditor::HandleSearchModalSubmit, this, placeholders::_1, placeholders::_2);
	
	_modals.push_back(FileNameInputModal);
	_modals.push_back(SearchInpuModal);
}

TextEditor::~TextEditor()
{
	for (int i = 0; i < _controls.size(); i++)
		delete _controls[i];
	for (int i = 0; i < _modals.size(); i++)
		delete _modals[i];
	delete _graphics;
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
			updatedControl->Draw(ConsoleBox);
			Invalidate(updatedControl->GetInvalidationRectangle());
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
			updatedControl->Draw(ConsoleBox);
			Invalidate(updatedControl->GetInvalidationRectangle());
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
			Invalidate(updatedControl->GetInvalidationRectangle());
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
			Invalidate(updatedControl->GetInvalidationRectangle());
			return;
		}
	}
}

void TextEditor::Invalidate(RectangleBox rectangle)
{
	for (Control* control : _controls)
	{
		if (control->Active)
			control->Draw(rectangle);
	}

	for (Modal* modal : _modals)
	{
		if (modal->Active)
			modal->Draw(rectangle);
	}
	_graphics->Invalidate();
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
		FileNameInputModal->Draw(ConsoleBox);
	}
	else
		SaveFileWithText(FilePath, TextInput->Text);
}


void TextEditor::HandleSearchModalClose(Modal* modal, int arg)
{
	SearchInpuModal->Active = false;
	RectangleBox modalBox = SearchInpuModal->Rectangle;
	Invalidate({ modalBox.X, modalBox.Y, modalBox.Width + 2, modalBox.Height + 1 });
}

void TextEditor::HandleSearchModalSubmit(Modal* modal, int arg)
{
	TextInput->SearchPattern = SearchInpuModal->TextInput->Text;
	SearchInpuModal->Active = false;
	RectangleBox modalBox = SearchInpuModal->Rectangle;
	modalBox.Width += 2;
	modalBox.Height++;
	Invalidate(modalBox.Union(SearchInpuModal->GetInvalidationRectangle()));
}

void TextEditor::HandleFindButtonClick(Control* sender, MouseEventArgs args)
{
	SearchInpuModal->Active = true;
	SearchInpuModal->Draw(ConsoleBox);
}

void SaveFileWithText(String filePath, String text)
{
	wofstream file;
	file.open(filePath);
	file.imbue(locale(file.getloc(), new codecvt_utf8_utf16<wchar_t, 0x10ffff, codecvt_mode(consume_header | generate_header)>));
	file << text;
	file.close();
}

void TextEditor::HandleNewButtonClick(Control* sender, MouseEventArgs args)
{
	TextInput->Text.clear();
	FilePath = L"";
	Invalidate(ConsoleBox);
}