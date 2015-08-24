#pragma once
class HitObject
{
	int mStartTime;
	int mHoldFor;
	bool mIsSpinner;
	int mX;
	int mY;
public:
	HitObject(int startTime, int holdFor, bool isSpinner, int x, int y);
	~HitObject();
	int start_time();
	int hold_for();
	bool is_spinner();
	void set_coordinates(int, int);
	int x();
	int y();
};

