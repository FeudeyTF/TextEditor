#pragma once
#include "Control.hpp"

class Modal : public Control
{
	public: String Title;

	public: Event<Modal*, int> OnClose;

	public: Event<Modal*, int> OnSubmit;

	protected: vector<Control*> _controls;

	public: Modal(String title, RectangleBox rectangle, Color color, Graphics* graphics);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args);
};

