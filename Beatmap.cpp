#include "stdafx.h"
#include "Beatmap.h"

Beatmap::Beatmap(std::string title, std::string artist, std::string version,
	double overallDifficulty, double sliderMultiplier, double sliderTickRate,
	std::vector<TimingSection> timingSections)
	:mTitle(title), mArtist(artist), mVersion(version), mOverallDifficulty(overallDifficulty),
	mSliderMultiplier(sliderMultiplier), mSliderTickRate(sliderTickRate), mTimingSections(timingSections)
{
}

Beatmap::~Beatmap()
{
}

void Beatmap::add_hit_object(HitObject hitObject)
{
	mHitObjects.push_back(hitObject);
}

TimingSection Beatmap::get_section_at(int time)
{
	TimingSection currentSection;
	for (TimingSection t : mTimingSections)
	{
		if (time >= t.start_time())
		{
			currentSection = t;
		}
		else
		{
			break;
		}
	}
	return currentSection;
}

double Beatmap::slider_multiplier()
{
	return mSliderMultiplier;
}

std::vector<HitObject>* Beatmap::get_hit_objects()
{
	return &mHitObjects;
}