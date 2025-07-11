#pragma once

#include <windows.h>
#include "KeyStatus.hpp"

class KeyEventArgs
{
	public: KeyStatus Status;

	public: int RepeatCount;

	public: int VirtualKeyCode;

	public: int VirtualScanCode;

	public: wchar_t Char;

	public: HANDLE OutputConsole;

	public: KEY_EVENT_RECORD Record;

	public: KeyEventArgs(KEY_EVENT_RECORD record, HANDLE outputConsole);
};

