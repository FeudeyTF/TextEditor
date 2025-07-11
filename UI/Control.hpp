#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "../Event/Event.hpp"
#include "EventArgs/MouseEventArgs.hpp"
#include "EventArgs/KeyEventArgs.hpp"
#include "Graphics/Graphics.hpp"

using namespace std;

class Control
{
	public: RectangleBox Rectangle;

	public: Color BackgroundColor;

	public: Event<Control*, MouseEventArgs> OnClick;

	public: Event<Control*, MouseEventArgs> OnMouseEnter;

	public: Event<Control*, MouseEventArgs> OnMouseLeave;

	public: bool Active;

	protected: Graphics* _graphics;

	private: bool _mouseInControl;

	public: Control(RectangleBox rectangle, Color color, Graphics* graphics);

	public: virtual void Draw(RectangleBox rectangle);

	public: virtual RectangleBox GetInvalidationRectangle();

	public: virtual Control* HandleMouseEvent(MouseEventArgs args);

	public: virtual Control* HandleKeyEvent(KeyEventArgs args);

	protected: bool IsPointInControl(int x, int y);
};