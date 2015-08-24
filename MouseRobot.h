#pragma once
#include <Windows.h>

class MouseRobot
{
	INPUT mInput;
	int mScreenWidth;
	int mScreenHeight;
public:
	MouseRobot();
	MouseRobot(int, int);
	~MouseRobot();
	void mouse_move_absolute(int, int);
	void emulate_line_move(int, int, int, int, int);
private:
	int get_min_not_zero(int, int);
};