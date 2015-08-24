#include "stdafx.h"
#include "MouseRobot.h"
#define CYCLES_FACTOR 3


MouseRobot::MouseRobot()
{
}

MouseRobot::MouseRobot(int screenWidth, int screenHeight) : mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	mInput.type = INPUT_MOUSE;
	mInput.mi.mouseData = 0;
	mInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	mInput.mi.time = 0;
	mInput.mi.dwExtraInfo = 0;
}

MouseRobot::~MouseRobot()
{
}

void MouseRobot::mouse_move_absolute(int x, int y)
{
	mInput.mi.dx = (x * (0xFFFF / mScreenWidth));
	mInput.mi.dy = (y * (0xFFFF / mScreenHeight));
	mInput.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
	SendInput(1, &mInput, sizeof(INPUT));
}

void MouseRobot::emulate_line_move(int xFrom, int yFrom, int xTo, int yTo, int time)
{
	const int offsetX = xTo - xFrom;
	const int offsetY = yTo - yFrom;

	if (offsetX != 0 || offsetY != 0)
	{
		const int minOffset = get_min_not_zero(abs(offsetX), abs(offsetY));
		//std::cout << "time: " << time << ", minOffset: " << minOffset << std::endl;
		int cycles = min(time, minOffset);
		const int cyclesWithFactor = cycles / CYCLES_FACTOR;
		if (cyclesWithFactor > 0)
		{
			cycles = cyclesWithFactor;
		}
		const int moveX = offsetX / cycles;
		const int moveY = offsetY / cycles;
		const int sleepTime = time / cycles;

		for (int i = 0; i < cycles; i++)
		{
			xFrom += moveX;
			yFrom += moveY;
			mouse_move_absolute(xFrom, yFrom);
			time -= sleepTime;
			Sleep(sleepTime);
		}
	}

	//will enter here if there was leftover in divisions
	if (time > 0)
	{
		mouse_move_absolute(xTo, yTo);
		Sleep(time);
	}
}

int MouseRobot::get_min_not_zero(int a, int b)
{
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	return min(a, b);
}