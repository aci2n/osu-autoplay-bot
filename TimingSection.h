#pragma once
class TimingSection
{
	int mStartTime;
	double mMsPerBeat;
public:
	TimingSection();
	TimingSection(int startTime, double msPerBeat);
	~TimingSection();
	int start_time();
	double ms_per_beat();
};

