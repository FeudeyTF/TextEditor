#pragma once
#include "../Modal.h"
#include "../Elements/Button.h"
#include "../Elements/Input.h"

class InputModal : public Modal
{
	public: Input* TextInput;

	public: Button* CloseButton;

	public: Button* SubmitButton;

	public: InputModal(string text, RectangleBox rectangle, Color modalColor, Color inputColor);

	public: ~InputModal();

	public: void HandleCloseButtonClick(Control* sender, MouseEventArgs args);

	public: void HandleSubmitButtonClick(Control* sender, MouseEventArgs args);

	public: virtual void Draw(RectangleBox rectangle, HANDLE console);

	public: virtual Control* HandleKeyEvent(KeyEventArgs args);
};

