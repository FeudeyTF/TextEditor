#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "Color.h";
#include "../Event/Event.h";
#include "EventArgs/MouseEventArgs.h";
#include "EventArgs/KeyEventArgs.h";

using namespace std;
class MouseEventArgs;

class Control
{
	public: int X;

	public: int Y;

	public: int Width;

	public: int Height;

	public: Color BackgroundColor;

	public: Event<Control*, MouseEventArgs> OnClick;

	public: Event<Control*, MouseEventArgs> OnMouseEnter;

	public: Event<Control*, MouseEventArgs> OnMouseLeave;

	private: bool _mouseInControl;

	public: virtual void Draw(HANDLE console);

	public: virtual Control* HandleMouseEvent(MouseEventArgs args);

	public: virtual Control* HandleKeyEvent(KeyEventArgs args);

	protected: bool IsPointInControl(int x, int y);

	protected: void DrawRectangle(int x, int y, int width, int height, Color color, HANDLE console);

	protected: void DrawBox(int x, int y, int width, int height, Color color, bool fill, HANDLE console);

	protected: void CreateText(int x, int y, string text, Color color, HANDLE console);
};