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
	HitObjectType type = NORMAL;
	std::string identifier = tokens[5];
	std::vector<SliderMovement> sliderMovements;

	if (std::regex_match(identifier, rgxSlider))
	{
		type = SLIDER;
		double factor = section.ms_per_beat() / mBeatmap.slider_multiplier();
		double relativeDuration = std::stod(tokens[7]);
		double bounces = std::stod(tokens[6]);
		holdFor = (int)(factor * relativeDuration * bounces);
		sliderMovements = parse_slider_movements(identifier, holdFor, x, y);
	}
	else if (std::regex_match(identifier, rgxSpinner))
	{
		type = SPINNER;
		holdFor = std::stoi(identifier) - time;
	}

	return HitObject(time, holdFor, x, y, type, sliderMovements);
}

std::vector<SliderMovement> HitObjectParser::parse_slider_movements(std::string line, int holdFor, int x, int y)
{
	switch (line[0])
	{
	case 'L':
		return parse_l_slider(line, holdFor, x, y);
	case 'P':
		return parse_p_slider(line, holdFor);
	case 'B':
		return parse_b_slider(line, holdFor);
	}
	return std::vector<SliderMovement>();
}

std::vector<SliderMovement> HitObjectParser::parse_l_slider(std::string line, int holdFor, int x, int y)
{
	std::vector<SliderMovement> sliderMovements;
	std::vector<std::string> tokens = mUtilities.split(line, "|");
	std::pair<int, int> to;
	std::vector<std::string> subTokens;
	const int size = tokens.size();
	std::pair<int, int> previous(x, y);
	int totalLength = 0;

	for (int i = 1; i < size; i++)
	{
		subTokens = mUtilities.split(tokens[i], ":");
		to.first = std::stoi(subTokens[0]);
		to.second = std::stoi(subTokens[1]);
		totalLength += calculate_length(previous, to);
		sliderMovements.push_back(SliderMovement(to));
		previous = to;
	}

	previous = std::pair<int, int>(x, y);
	for (SliderMovement& sm : sliderMovements)
	{
		to = sm.to();
		sm.set_time(holdFor / (totalLength / calculate_length(previous, to)));
		previous = to;
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

int HitObjectParser::calculate_length(std::pair<int, int> a, std::pair<int, int> b)
{
	const int x = b.first - a.first;
	const int y = b.second - a.second;
	return (int)std::sqrt(x * x + y * y);
}