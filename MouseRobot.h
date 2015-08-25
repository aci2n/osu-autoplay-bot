#pragma once
#include <Windows.h>

class MouseRobot
{
	INPUT mInput;
	int mScreenWidth;
	int mScreenHeight;
	std::vector<std::pair<int, int>> mSpinnerPoints;
public:
	MouseRobot();
	MouseRobot(int, int, std::vector<int>);
	~MouseRobot();
	void mouse_move_absolute(int, int);
	void emulate_line_move(int, int, int, int, int);
	void emulate_spin(int, int*, int*);
private:
	int get_min_not_zero(int, int);
	void init_spinner_points(int, int, int);
};