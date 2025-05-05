#include "Modal.h"

Modal::Modal(string title, RectangleBox rectangle, Color color) : Control(rectangle, color)
{
	Active = false;
	Title = title;
}

Control* Modal::HandleMouseEvent(MouseEventArgs args)
{
	for (Control* control : _controls)
	{
		if (!control->Active)
			continue;
		Control* updatedControl = control->HandleMouseEvent(args);
		if (updatedControl != nullptr && Active)
			return this;
	}
	return nullptr;
}