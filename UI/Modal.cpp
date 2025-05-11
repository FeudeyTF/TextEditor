#include "Modal.hpp"

Modal::Modal(String title, RectangleBox rectangle, Color color, Graphics* graphics) : Control(rectangle, color, graphics)
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