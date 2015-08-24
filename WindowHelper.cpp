#include "stdafx.h"
#include "WindowHelper.h"
#include <Windows.h>

BOOL CALLBACK EnumWindowsProc(HWND, LPARAM);

HWND wHandle = NULL;

WindowHelper::WindowHelper()
{
}

WindowHelper::~WindowHelper()
{
}

RECT WindowHelper::get_rect(int processId)
{
	RECT rect;
	EnumWindows(EnumWindowsProc, processId);
	GetWindowRect(wHandle, &rect);
	return rect;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		wHandle = hwnd;
		return FALSE;
	}
	return TRUE;
}

RECT WindowHelper::get_desktop_rect()
{
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	return desktop;
}