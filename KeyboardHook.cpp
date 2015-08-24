#include "stdafx.h"
#include "KeyboardHook.h"

LRESULT CALLBACK ChillKeyboardHook(int, WPARAM, LPARAM);

HHOOK kHook = NULL;
Player gPlayer;
const int startKey = 115; //F4
bool gPlaying = false;

KeyboardHook::KeyboardHook(Player player)
{
	std::cout << "Press F4 to start..." << std::endl;
	gPlayer = player;

	MSG msg;
	kHook = SetWindowsHookEx(WH_KEYBOARD_LL, ChillKeyboardHook, NULL, NULL);

	while (!GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(kHook);
}


KeyboardHook::~KeyboardHook()
{
}

LRESULT CALLBACK ChillKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0 || nCode != HC_ACTION)
	{
		return CallNextHookEx(kHook, nCode, wParam, lParam);
	}

	if (wParam == WM_KEYDOWN && ((KBDLLHOOKSTRUCT*)lParam)->vkCode == startKey)
	{
		if (!gPlaying)
		{
			gPlaying = true;
			std::cout << "Starting!" << std::endl;
			new std::thread(gPlayer);
		}
		else
		{
			exit(0);
		}
	}

	return CallNextHookEx(kHook, nCode, wParam, lParam);
}
