#include "KeyEventArgs.hpp"
KeyEventArgs::KeyEventArgs(KEY_EVENT_RECORD record, HANDLE outputConsole)
{
	Record = record;
	OutputConsole = outputConsole;
	Char = record.uChar.UnicodeChar;
	VirtualKeyCode = record.wVirtualKeyCode;
	VirtualScanCode = record.wVirtualScanCode;
	Status = record.bKeyDown ? KeyStatus::Pressed : KeyStatus::Released;
	RepeatCount = record.wRepeatCount;
}