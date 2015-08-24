#pragma once
#include <Windows.h>

class KeyboardRobot
{
	INPUT mInput;
public:
	KeyboardRobot();
	~KeyboardRobot();
	void press_key(int);
	void release_key();
};

