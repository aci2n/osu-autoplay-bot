#include "stdafx.h"
#include "KeyboardRobot.h"


KeyboardRobot::KeyboardRobot()
{
	mInput.type = INPUT_KEYBOARD;
	mInput.ki.wScan = 0;
	mInput.ki.time = 0;
	mInput.ki.dwExtraInfo = 0;
	mInput.ki.dwFlags = 0;
}

KeyboardRobot::~KeyboardRobot()
{
}

void KeyboardRobot::press_key(int key)
{
	mInput.ki.wVk = key;
	mInput.ki.dwFlags = 0;
	SendInput(1, &mInput, sizeof(INPUT));
}

void KeyboardRobot::release_key()
{
	mInput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &mInput, sizeof(INPUT));
}