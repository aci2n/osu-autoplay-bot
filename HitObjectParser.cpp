#include "stdafx.h"
#include "HitObjectParser.h"
#define MIN_WAIT_TIME 15

std::regex rgxSlider(R"([[:upper:]]\|.+)");
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
	int holdFor = MIN_WAIT_TIME;
	TimingSection section = mBeatmap.get_section_at(time);
	HitObjectType type = NORMAL;
	std::string identifier = "";
	if (tokens.size() > 5)
	{
		identifier = tokens[5];
	}
	std::vector<SliderMovement> sliderMovements;

	if (std::regex_match(identifier, rgxSlider))
	{
		type = SLIDER;
		double factor = section.ms_per_beat() / mBeatmap.slider_multiplier();
		double relativeDuration = std::stod(tokens[7]);
		int bounces = std::stoi(tokens[6]);
		holdFor = (int)(factor * relativeDuration * bounces);
		sliderMovements = parse_slider_movements(identifier, holdFor, x, y, bounces);
	}
	else if (std::regex_match(identifier, rgxSpinner))
	{
		type = SPINNER;
		holdFor = std::stoi(identifier) - time;
	}

	return HitObject(time, holdFor, x, y, type, sliderMovements);
}

std::vector<SliderMovement> HitObjectParser::parse_slider_movements(std::string line, int holdFor, int x, int y, int bounces)
{
	return parse_linear_slider(line, holdFor, x, y, bounces);
}

std::vector<SliderMovement> HitObjectParser::parse_linear_slider(std::string line, const int holdFor, int x, int y, const int bounces)
{
	std::vector<SliderMovement> sliderMovements;
	std::vector<std::string> tokens = mUtilities.split(line, "|");
	std::pair<int, int> to;
	std::vector<std::string> subTokens;
	const int size = tokens.size();
	std::pair<int, int> previous(x, y);
	double totalLength = 0;
	//int auxHoldFor = holdFor;
	int auxBounces = bounces;

	for (int i = 1; i < size; i++)
	{
		subTokens = mUtilities.split(tokens[i], ":");
		to.first = std::stoi(subTokens[0]);
		to.second = std::stoi(subTokens[1]);
		if (to != previous)
		{
			totalLength += calculate_length(previous, to);
			sliderMovements.push_back(SliderMovement(to));
		}
		previous = to;
	}

	totalLength *= bounces;

	std::vector<SliderMovement> copy = sliderMovements;
	bool bounceBack = false;
	const int copySize = copy.size();
	while (auxBounces > 1)
	{
		if (!bounceBack)
		{
			for (int i = copySize - 2; i >= 0; i--)
			{
				sliderMovements.push_back(copy[i].to());
			}
			sliderMovements.push_back(std::pair<int, int>(x, y));
		}
		else
		{
			for (int i = 0; i < copySize; i++)
			{
				sliderMovements.push_back(copy[i].to());
			}
		}
		bounceBack = !bounceBack;
		auxBounces--;
	}

	previous = std::pair<int, int>(x, y);
	double factor;
	int movementTime;
	for (SliderMovement& sm : sliderMovements)
	{
		to = sm.to();
		factor = totalLength / calculate_length(previous, to);
		movementTime = (int)(holdFor / factor);
		//auxHoldFor -= movementTime;
		sm.set_time(movementTime);
		previous = to;
	}
	//std::cout << auxHoldFor << std::endl;
	return sliderMovements;
}

double HitObjectParser::calculate_length(std::pair<int, int> a, std::pair<int, int> b)
{
	const int x = b.first - a.first;
	const int y = b.second - a.second;
	return std::sqrt(x * x + y * y);
}