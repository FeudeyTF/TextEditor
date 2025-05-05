#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "Color.h";
#include "../Event/Event.h";
#include "EventArgs/MouseEventArgs.h"
#include "EventArgs/KeyEventArgs.h"
#include "Rectangle.h"

using namespace std;

class Control
{
	public: RectangleBox Rectangle;

	public: Color BackgroundColor;

	public: Event<Control*, MouseEventArgs> OnClick;

	public: Event<Control*, MouseEventArgs> OnMouseEnter;

	public: Event<Control*, MouseEventArgs> OnMouseLeave;

	public: bool Active;

	private: bool _mouseInControl;

	public: Control(RectangleBox rectangle, Color color);

	public: virtual void Draw(RectangleBox rectangle, HANDLE console);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args);

	public: virtual Control* HandleKeyEvent(KeyEventArgs args);

	protected: bool IsPointInControl(int x, int y);

	protected: void DrawRectangle(RectangleBox rectangle, Color color, HANDLE console);

	protected: void DrawBox(RectangleBox rectangle, RectangleBox maxRectangle, Color color, bool fill, HANDLE console);

	protected: void DrawLine(int x, int y, int width, char start, char end, char mid, Color color, HANDLE console);

	protected: void CreateText(int x, int y, RectangleBox rectangle, string text, Color color, HANDLE console);
};