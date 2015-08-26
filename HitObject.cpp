#include "stdafx.h"
#include "HitObject.h"


HitObject::HitObject(int startTime, int holdFor, int x, int y, HitObjectType type, std::vector<SliderMovement> sliderMovements)
	: mStartTime(startTime), mHoldFor(holdFor), mX(x), mY(y), mType(type), mSliderMovements(sliderMovements)
{
}


HitObject::~HitObject()
{
}

int HitObject::start_time()
{
	return mStartTime;
}

int HitObject::hold_for()
{
	return mHoldFor;
}

void HitObject::set_coordinates(int x, int y)
{
	mX = x;
	mY = y;
}

int HitObject::x()
{
	return mX;
}

int HitObject::y()
{
	return mY;
}

HitObjectType HitObject::type()
{
	return mType;
}

std::vector<SliderMovement>* HitObject::slider_movements()
{
	return &mSliderMovements;
}

void HitObject::set_time(int time)
{
	mStartTime = time;
}

void HitObject::set_hold_for(int holdFor)
{
	mHoldFor = holdFor;
}