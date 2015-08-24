#include "stdafx.h"
#include "BeatmapParser.h"

const std::vector<std::string> sliderIdentifiers(std::initializer_list<std::string>{"2", "3", "6", "22", "38", "70"});
const std::vector<std::string> spinnerIdentifiers(std::initializer_list<std::string>{"8", "12"});

BeatmapParser::BeatmapParser(std::string filename) : mFilename(filename)
{
}


BeatmapParser::~BeatmapParser()
{
}

Beatmap BeatmapParser::parse_beatmap()
{
	std::ifstream file(mFilename);
	if (file)
	{
		std::string title(read_value(file, "Title"));
		std::string artist(read_value(file, "Artist"));
		std::string version(read_value(file, "Version"));
		double overallDifficulty(std::stod(read_value(file, "OverallDifficulty")));
		double sliderMultiplier(std::stod(read_value(file, "SliderMultiplier")) * 100);
		double sliderTickRate(std::stod(read_value(file, "SliderTickRate")));
		std::vector<TimingSection> timingSections(read_timing_sections(file));
		Beatmap beatmap(title, artist, version, overallDifficulty, sliderMultiplier, sliderTickRate, timingSections);
		add_hitobjects(file, beatmap);
		file.close();

		return beatmap;
	}

	throw std::exception(("Could not open file: " + mFilename + ".").c_str());
}

std::string BeatmapParser::read_value(std::ifstream& file, std::string key)
{
	std::regex rgxLine(key + ":.*");
	std::regex rgxValue(key + ":\\s?");
	for (std::string line; std::getline(file, line);)
	{
		if (std::regex_match(line, rgxLine))
		{
			return std::regex_replace(line, rgxValue, "");
		}
	}

	throw std::exception(("Could not parse beatmap value: " + key + ".").c_str());
}

std::vector<TimingSection> BeatmapParser::read_timing_sections(std::ifstream& file)
{
	read_until_line(file, "[TimingPoints]");
	std::vector<TimingSection> sections;
	double currentFather;
	for (std::string line; std::getline(file, line) && line != "";)
	{
		std::vector<std::string> tokens = split(line, ",");
		int startTime = std::stoi(tokens[0]);
		double msPerBeat = std::stod(tokens[1]);
		if (msPerBeat > 0)
		{
			currentFather = msPerBeat;
		}
		else
		{
			msPerBeat = currentFather * (msPerBeat / -100);
		}
		sections.push_back(TimingSection(startTime, msPerBeat));
	}
	return sections;
}

void BeatmapParser::add_hitobjects(std::ifstream& file, Beatmap& beatmap)
{
	read_until_line(file, "[HitObjects]");
	for (std::string line; std::getline(file, line) && line != "";)
	{
		std::vector<std::string> tokens = split(line, ",");
		int x = std::stoi(tokens[0]);
		int y = std::stoi(tokens[1]);
		int time = std::stoi(tokens[2]);
		TimingSection section = beatmap.get_section_at(time);
		bool isSpinner = false;
		int holdFor = 0;
		if (contains(sliderIdentifiers, tokens[3]))
		{
			double factor = section.ms_per_beat() / beatmap.slider_multiplier();
			double relativeDuration = std::stod(tokens[7]);
			double bounces = std::stod(tokens[6]);
			holdFor = (int)(factor * relativeDuration * bounces);
		}
		if (contains(spinnerIdentifiers, tokens[3]))
		{
			holdFor = std::stoi(tokens[5]) - time;
			isSpinner = true;
		}
		beatmap.add_hit_object(HitObject(time, holdFor, isSpinner, x, y));
	}
}

template<typename T>
bool BeatmapParser::contains(std::vector<T> v, T t)
{
	for (T x : v)
	{
		if (x == t)
		{
			return true;
		}
	}
	return false;
}

void BeatmapParser::read_until_line(std::ifstream& file, std::string line)
{
	for (std::string s; std::getline(file, s) && s != line;);
}

std::vector<std::string> BeatmapParser::split(std::string base, std::string delim)
{
	std::string token;
	int pos;
	std::vector<std::string> tokens;
	while ((pos = base.find(delim)) != std::string::npos) {
		token = base.substr(0, pos);
		base = base.substr(pos + 1, base.length());
		tokens.push_back(token);
	}
	if (base.length() > 0)
	{
		tokens.push_back(base);
	}
	return tokens;
}