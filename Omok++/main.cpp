#include <Windows.h> 
#include "WindowsEngin.h"

/*
Omok++
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	FILE* outputStream = nullptr;
	freopen_s(&outputStream, "CONOUT$", "wt", stdout);
#endif

	WindowsEngin wndEngin(hInstance, nCmdShow);
	MSG msg = wndEngin.start();

#ifdef _DEBUG
	FreeConsole();
#endif

	return msg.wParam;
}