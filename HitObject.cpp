#include "stdafx.h"
#include "HitObject.h"


HitObject::HitObject(int startTime, int holdFor, bool isSpinner, int x, int y)
: mStartTime(startTime), mHoldFor(holdFor), mIsSpinner(isSpinner), mX(x), mY(y)
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

bool HitObject::is_spinner()
{
	return mIsSpinner;
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