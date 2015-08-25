#include "stdafx.h"
#include "HitObjectParser.h"

const std::vector<std::string> sliderIdentifiers(std::initializer_list<std::string>{"2", "3", "6", "22", "38", "70"});
const std::vector<std::string> spinnerIdentifiers(std::initializer_list<std::string>{"8", "12"});

HitObjectParser::HitObjectParser(Beatmap beatmap) : mBeatmap(beatmap)
{
}


HitObjectParser::~HitObjectParser()
{
}

HitObject HitObjectParser::parse_hitobject(std::string line)
{
	std::vector<std::string> tokens = mUtilities.split(line, ",");
	int x = std::stoi(tokens[0]);
	int y = std::stoi(tokens[1]);
	int time = std::stoi(tokens[2]);
	int holdFor = 0;
	TimingSection section = mBeatmap.get_section_at(time);
	HitObjectType type;

	if (mUtilities.contains(sliderIdentifiers, tokens[3]))
	{
		type = SLIDER;
		double factor = section.ms_per_beat() / mBeatmap.slider_multiplier();
		double relativeDuration = std::stod(tokens[7]);
		double bounces = std::stod(tokens[6]);
		holdFor = (int)(factor * relativeDuration * bounces);
	}
	else if (mUtilities.contains(spinnerIdentifiers, tokens[3]))
	{
		type = SPINNER;
		holdFor = std::stoi(tokens[5]) - time;
	}
	else
	{
		type = NORMAL;
	}

	return HitObject(time, holdFor, x, y, type);
}