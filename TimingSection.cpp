#include "stdafx.h"
#include "TimingSection.h"

TimingSection::TimingSection()
{

}

TimingSection::TimingSection(int startTime, double msPerBeat) : mStartTime(startTime), mMsPerBeat(msPerBeat)
{
}


TimingSection::~TimingSection()
{
}

int TimingSection::start_time()
{
	return mStartTime;
}

double TimingSection::ms_per_beat()
{
	return mMsPerBeat;
}