#include "WindowsEngin.h"
#include "GameBoard.h"

WindowsEngin::WindowsEngin(HINSTANCE hInstance, int nCmdShow) : WindowsCreate(hInstance, nCmdShow)
{
	logger = new Logger(hWnd);
	objManager = ObjectManager::getInstance();

	objManager->add(new GameBoard(hWnd, logger));

}

WindowsEngin::~WindowsEngin()
{
	WindowsCreate::~WindowsCreate();
}

void WindowsEngin::draw(HDC hdc, PAINTSTRUCT ps)
{
	objManager->draw(hdc, ps);
}

void WindowsEngin::mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam)
{
	objManager->mouseEvent(ent, wParam, lParam);
}

void WindowsEngin::cmdEvent(WPARAM wParam, LPARAM lParam)
{
	objManager->cmdEvent(wParam, lParam);
}

void WindowsEngin::init()
{
}

void WindowsEngin::destroy()
{
	delete objManager;
	logger->end();
}
