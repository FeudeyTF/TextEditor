#include "InputModal.h"

InputModal::InputModal(String text, RectangleBox rectangle, Color modalColor, Color inputColor, Graphics* graphics) : Modal(text, rectangle, modalColor, graphics)
{
	CloseButton = new Button(L"X", {rectangle.X + rectangle.Width - 3, rectangle.Y, 3, 1}, BACKGROUND_RED | FOREGROUND_BRIGHT_WHITE, graphics);
	CloseButton->OnClick += bind(&InputModal::HandleCloseButtonClick, this, placeholders::_1, placeholders::_2);
	
	RectangleBox submitButtonBox = rectangle.GetCenteredRectangle(8, 1);
	submitButtonBox.Y++;
	SubmitButton = new Button(L"Submit", submitButtonBox, modalColor, graphics);
	SubmitButton->OnClick += bind(&InputModal::HandleSubmitButtonClick, this, placeholders::_1, placeholders::_2);

	Title = L" " + Title + L" ";
	RectangleBox inputBox = rectangle.GetCenteredRectangle(rectangle.WithOffset(1).Width - 4, 1);
	TextInput = new Input(inputBox, inputColor, graphics);
	_controls.push_back(CloseButton);
	_controls.push_back(SubmitButton);
	_controls.push_back(TextInput);

	_oldPosition = { -1, -1 };
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

void InputModal::Draw(RectangleBox rectangle)
{
	_graphics->DrawShadow(Rectangle.Intersection(rectangle));
	_graphics->DrawRectangle(Rectangle.Intersection(rectangle), BackgroundColor);
	_graphics->DrawBox(Rectangle.WithOffset(1), rectangle, BackgroundColor, true);
	_graphics->CreateText(Rectangle.X + (Rectangle.Width - (int)Title.size()) / 2, Rectangle.Y + 1, rectangle, Title, BackgroundColor);
	for(Control* control : _controls)
		control->Draw(rectangle);
}

RectangleBox InputModal::GetInvalidationRectangle()
{
	return _invalidationBox;
}

Control* InputModal::HandleKeyEvent(KeyEventArgs args)
{
	TextInput->HandleKeyEvent(args);
	return this;
}

Control* InputModal::HandleMouseEvent(MouseEventArgs args)
{
	Control* result = Modal::HandleMouseEvent(args);
	if (result != nullptr)
		return result;

	if (args.Record.dwEventFlags != MOUSE_MOVED)
	{
		if (args.Record.dwButtonState)
			_oldPosition = { args.X, args.Y };
		else
			_oldPosition = { -1, -1 };
	}

	if (!Rectangle.Contains(_oldPosition.X, _oldPosition.Y))
		return nullptr;

	if (args.EventType == MouseEventType::MouseMoved && _oldPosition.X != -1 && _oldPosition.Y != -1)
	{
		int deltaX = args.X - _oldPosition.X;
		int deltaY = args.Y - _oldPosition.Y;
		if (deltaX != 0 || deltaY != 0)
		{
			RectangleBox oldRectangle = Rectangle;
			oldRectangle.Width += 2;
			oldRectangle.Height++;

			Rectangle.X += deltaX;
			Rectangle.Y += deltaY;


			RectangleBox newRectangle = Rectangle;
			newRectangle.Width += 2;
			newRectangle.Height++;

			for (Control* control : _controls)
			{
				control->Rectangle.X += deltaX;
				control->Rectangle.Y += deltaY;
			}

			TextInput->InputPoint.X += deltaX;
			TextInput->InputPoint.Y += deltaY;

			_oldPosition = { args.X, args.Y };

			_invalidationBox = newRectangle.Union(oldRectangle);
			return this;
		}
	}
	return nullptr;
}