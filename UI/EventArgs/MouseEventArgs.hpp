#pragma once

#include <windows.h>
#include "MouseEventType.hpp"

class MouseEventArgs
{
	public: MouseEventType EventType;

	public: int X;

	public: int Y;

	public: MOUSE_EVENT_RECORD Record;

	public: HANDLE OutputConsole;

	public: MouseEventArgs(MOUSE_EVENT_RECORD record, HANDLE outputConsole);
};