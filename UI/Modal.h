#pragma once
#include "Control.h";

class Modal : public Control
{
	public: string Title;

	public: Event<Modal*, int> OnClose;

	public: Event<Modal*, int> OnSubmit;

	protected: vector<Control*> _controls;

	public: Modal(string title, RectangleBox rectangle, Color color);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args);
};

