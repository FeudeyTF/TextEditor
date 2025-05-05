#include "InputModal.h"

InputModal::InputModal(string text, RectangleBox rectangle, Color modalColor, Color inputColor) : Modal(text, rectangle, modalColor)
{
	CloseButton = new Button("X", {rectangle.X + rectangle.Width - 3, rectangle.Y, 3, 1}, BACKGROUND_RED | FOREGROUND_BRIGHT_WHITE);
	CloseButton->OnClick += bind(&InputModal::HandleCloseButtonClick, this, placeholders::_1, placeholders::_2);
	
	RectangleBox submitButtonBox = rectangle.GetCenteredRectangle(8, 1);
	submitButtonBox.Y++;
	SubmitButton = new Button("Submit", submitButtonBox, modalColor);
	SubmitButton->OnClick += bind(&InputModal::HandleSubmitButtonClick, this, placeholders::_1, placeholders::_2);

	Title = " " + Title + " ";
	RectangleBox inputBox = rectangle.GetCenteredRectangle(rectangle.WithOffset(1).Width - 4, 1);
	TextInput = new Input(inputBox, inputColor);
	_controls.push_back(CloseButton);
	_controls.push_back(SubmitButton);
	_controls.push_back(TextInput);
}

InputModal::~InputModal()
{
	delete TextInput;
	delete CloseButton;
}

void InputModal::HandleCloseButtonClick(Control* sender, MouseEventArgs args)
{
	OnClose.Invoke(this, 0);
}

void InputModal::HandleSubmitButtonClick(Control* sender, MouseEventArgs args)
{
	OnSubmit.Invoke(this, 0);
}

void InputModal::Draw(RectangleBox rectangle, HANDLE console)
{
	DrawShadow(Rectangle.Intersection(rectangle), console);
	DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor, console);
	DrawBox(Rectangle.WithOffset(1), rectangle, BackgroundColor, true, console);
	CreateText(Rectangle.X + (Rectangle.Width - Title.size()) / 2, Rectangle.Y + 1, rectangle, Title, BackgroundColor, console);
	for(Control* control : _controls)
		control->Draw(rectangle, console);
}

Control* InputModal::HandleKeyEvent(KeyEventArgs args)
{
	TextInput->HandleKeyEvent(args);
	return this;
}