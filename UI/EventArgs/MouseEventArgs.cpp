#include "MouseEventArgs.h";

MouseEventArgs::MouseEventArgs(MOUSE_EVENT_RECORD record, HANDLE outputConsole)
{
	OutputConsole = outputConsole;
    X = record.dwMousePosition.X;
    Y = record.dwMousePosition.Y;
    Record = record;
    EventType = MouseEventType::None;
    switch (record.dwEventFlags)
    {
        case 0:
            if (record.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                EventType = MouseEventType::LeftMouseButton;
            }
            else if (record.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
                EventType = MouseEventType::RightMouseButton;
            }

            break;
        case DOUBLE_CLICK:
            EventType = MouseEventType::DoubleClick;
            break;
        case MOUSE_HWHEELED:
            EventType = MouseEventType::HorizontalWheel;
            break;
        case MOUSE_MOVED:
            EventType = MouseEventType::MouseMoved;
            break;
        case MOUSE_WHEELED:
            EventType = MouseEventType::VerticalWheel;
            break;
    }
}