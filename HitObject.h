#pragma once
#include "SliderMovement.h"

enum HitObjectType {
	NORMAL,
	SLIDER,
	SPINNER
};

class HitObject
{
	int mStartTime;
	int mHoldFor;
	int mX;
	int mY;
	HitObjectType mType;
	std::vector<SliderMovement> mSliderMovements;
public:
	HitObject(int startTime, int holdFor, int x, int y, HitObjectType type, std::vector<SliderMovement>);
	~HitObject();
	int start_time();
	int hold_for();
	bool is_spinner();
	void set_coordinates(int, int);
	int x();
	int y();
	HitObjectType type();
	std::vector<SliderMovement>* slider_movements();
};

