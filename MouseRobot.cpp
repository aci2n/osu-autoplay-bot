#include "stdafx.h"
#include "MouseRobot.h"
#define CYCLES_FACTOR 3
#define SPINNER_SPEED 10 //lower == faster
#define SPINNER_POINTS 4

MouseRobot::MouseRobot()
{
}

MouseRobot::MouseRobot(int screenWidth, int screenHeight, std::vector<int> windowValues)
	: mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	mInput.type = INPUT_MOUSE; mInput.mi.mouseData = 0;
	mInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	mInput.mi.time = 0;
	mInput.mi.dwExtraInfo = 0;
	init_spinner_points(windowValues[0], windowValues[1], windowValues[2]);
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

	mouse_move_absolute(xTo, yTo);

	//will enter here if there was leftover in divisions
	if (time > 0)
	{
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

void MouseRobot::emulate_spin(int time, int* lastX, int* lastY)
{
	int c = 0;
	int n = 1;
	int cycles = time / SPINNER_SPEED;
	for (int i = 0; i < cycles; i++)
	{
		emulate_line_move(
			mSpinnerPoints[c].first,
			mSpinnerPoints[c].second,
			mSpinnerPoints[n].first,
			mSpinnerPoints[n].second,
			SPINNER_SPEED
			);
		c = c < SPINNER_POINTS - 1 ? c + 1 : 0;
		n = n < SPINNER_POINTS - 1 ? n + 1 : 0;
	}

	*lastX = mSpinnerPoints[c].first;
	*lastY = mSpinnerPoints[c].second;
}

void MouseRobot::init_spinner_points(int x, int y, int spinnerWidth)
{
	mSpinnerPoints = std::vector<std::pair<int, int>>(SPINNER_POINTS);
	mSpinnerPoints[0].first = x + spinnerWidth;
	mSpinnerPoints[0].second = y;
	mSpinnerPoints[1].first = x;
	mSpinnerPoints[1].second = y - spinnerWidth;
	mSpinnerPoints[2].first = x - spinnerWidth;
	mSpinnerPoints[2].second = y;
	mSpinnerPoints[3].first = x;
	mSpinnerPoints[3].second = y + spinnerWidth;
}