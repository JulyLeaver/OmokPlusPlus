#include <Windows.h> 
#include "WindowsEngin.h"

// edit으로 로그창 만들려다 어려워서 포기함...괜히 GUI에 신경쓰가 시간 날림
#define CONSOLE

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
#ifdef CONSOLE
	AllocConsole();
	FILE* outputStream = nullptr;
	freopen_s(&outputStream, "CONOUT$", "wt", stdout);
#endif

	WindowsEngin wndEngin(hInstance, nCmdShow);
	MSG msg = wndEngin.start();

#ifdef CONSOLE
	FreeConsole();
#endif

	

	return static_cast<int>(msg.wParam);
}