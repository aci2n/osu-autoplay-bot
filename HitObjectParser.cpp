#include "stdafx.h"
#include "HitObjectParser.h"

std::regex rgxSlider(R"([LPB]\|.+)");
std::regex rgxSpinner(R"(\d+)");

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
	std::string identifier = tokens[5];
	std::vector<SliderMovement> sliderMovements;

	if (std::regex_match(identifier, rgxSlider))
	{
		type = SLIDER;
		double factor = section.ms_per_beat() / mBeatmap.slider_multiplier();
		double relativeDuration = std::stod(tokens[7]);
		double bounces = std::stod(tokens[6]);
		holdFor = (int)(factor * relativeDuration * bounces);
		sliderMovements = parse_slider_movements(identifier, holdFor);
	}
	else if (std::regex_match(identifier, rgxSpinner))
	{
		type = SPINNER;
		holdFor = std::stoi(identifier) - time;
	}
	else
	{
		type = NORMAL;
	}

	return HitObject(time, holdFor, x, y, type, sliderMovements);
}

std::vector<SliderMovement> HitObjectParser::parse_slider_movements(std::string line, int holdFor)
{
	switch (line[0])
	{
	case 'L':
		return parse_l_slider(line, holdFor);
	case 'P':
		return parse_p_slider(line, holdFor);
	case 'B':
		return parse_b_slider(line, holdFor);
	}
}

std::vector<SliderMovement> HitObjectParser::parse_l_slider(std::string line, int holdFor)
{
	std::vector<SliderMovement> sliderMovements;
	std::vector<std::string> tokens = mUtilities.split(line, "|");
	std::pair<int, int> to;
	std::vector<std::string> subTokens;
	for (int i = 1; i < tokens.size(); i++)
	{
		subTokens = mUtilities.split(tokens[i], ":");
		to.first = std::stoi(subTokens[0]);
		to.second = std::stoi(subTokens[1]);
		sliderMovements.push_back(SliderMovement(to, holdFor / (tokens.size() - 1)));
	}
	return sliderMovements;
}

std::vector<SliderMovement> HitObjectParser::parse_p_slider(std::string line, int holdFor)
{
	std::vector<SliderMovement> sliderMovements;
	return sliderMovements;
}

std::vector<SliderMovement> HitObjectParser::parse_b_slider(std::string line, int holdFor)
{
	std::vector<SliderMovement> sliderMovements;
	return sliderMovements;
}