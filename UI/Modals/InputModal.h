#pragma once
#include "../Modal.h"
#include "../Elements/Button.h"
#include "../Elements/Input.h"

class InputModal : public Modal
{
	public: Input* TextInput;

	public: Button* CloseButton;

	public: Button* SubmitButton;

	private: Point _oldPosition;

	private: RectangleBox _invalidationBox;

	public: InputModal(String text, RectangleBox rectangle, Color modalColor, Color inputColor, Graphics* graphics);

	public: ~InputModal();

	public: void HandleCloseButtonClick(Control* sender, MouseEventArgs args);

	public: void HandleSubmitButtonClick(Control* sender, MouseEventArgs args);

	public: virtual void Draw(RectangleBox rectangle) override;

	public: virtual RectangleBox GetInvalidationRectangle() override;

	public: virtual Control* HandleKeyEvent(KeyEventArgs args) override;

	public: virtual Control* HandleMouseEvent(MouseEventArgs args) override;
};