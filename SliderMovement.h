#pragma once
class SliderMovement
{
	std::pair<int, int> mTo;
	int mTime;
public:
	SliderMovement(std::pair<int, int>);
	~SliderMovement();
	std::pair<int, int> to();
	int time();
	void set_pair(int, int);
	void set_time(int);
};

