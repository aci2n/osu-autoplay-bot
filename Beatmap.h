#pragma once
#include "TimingSection.h"
#include "HitObject.h"

class Beatmap
{
	std::string mTitle;
	std::string mArtist;
	std::string mVersion;
	double mOverallDifficulty;
	double mSliderMultiplier;
	double mSliderTickRate;
	std::vector<TimingSection> mTimingSections;
	std::vector<HitObject> mHitObjects;
public:
	Beatmap(std::string title, std::string artist, std::string version,
		double overallDifficulty, double sliderMultiplier, double sliderTickRate,
		std::vector<TimingSection> timingSections);
	~Beatmap();
	void add_hit_object(HitObject);
	TimingSection get_section_at(int time);
	double slider_multiplier();
	std::vector<HitObject>* get_hit_objects();
};