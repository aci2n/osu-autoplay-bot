#include "stdafx.h"
#include "SliderMovement.h"


SliderMovement::SliderMovement(std::pair<int, int> to)
	:mTo(to)
{
}


SliderMovement::~SliderMovement()
{
}

std::pair<int, int> SliderMovement::to()
{
	return mTo;
}

int SliderMovement::time()
{
	return mTime;
}

void SliderMovement::set_pair(int first, int second)
{
	mTo.first = first;
	mTo.second = second;
}

void SliderMovement::set_time(int time)
{
	mTime = time;
}