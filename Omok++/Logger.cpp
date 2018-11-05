#include <iostream>
#include "Logger.h"
#include "WindowsEngin.h"

Logger::Logger(const HWND hWnd) : hWnd(hWnd)
{
	/*
	hEdit = CreateWindow("edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_READONLY |
		WS_HSCROLL | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		300, 100, 400, 200, hWnd, (HMENU)ID, WindowsCreate::hInstance, NULL);
		*/

//	msgBuf = new char[16384];
}

void Logger::loop(std::unique_lock<std::mutex>& ul)
{
	while (true)
	{
		ul.lock();
		if (_q.empty()) break;

		const string& msg = _q.front();
		cout << msg << '\n';
		_q.pop();

		ul.unlock();
	}
}

Logger::~Logger()
{
//	delete[]msgBuf;
}
