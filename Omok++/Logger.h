#pragma once

#include <Windows.h>
#include <string>
#include "Event.h"

using namespace std;

class Logger : public Event<string>
{
private:
	const HWND hWnd;
//	HWND hEdit;
//	const int ID = 100;
//	char* msgBuf;

public:
	Logger(const HWND hWnd);
	
	inline void log(const string& msg) { Event<string>::push(msg); }
	virtual void loop(unique_lock<mutex>& ul) override;

	~Logger();
};

