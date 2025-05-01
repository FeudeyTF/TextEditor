#include "UI/Forms/TextEditor.h"

int main()
{
	HANDLE outputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE inputConsole = GetStdHandle(STD_INPUT_HANDLE);

	TextEditor editor = TextEditor(outputConsole, inputConsole);
	editor.Run();

	return 0;
}