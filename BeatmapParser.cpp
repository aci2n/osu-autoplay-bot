#include "stdafx.h"
#include "BeatmapParser.h"

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
		std::vector<std::string> tokens = mUtilities.split(line, ",");
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
	HitObjectParser hitObjectParser(beatmap);
	read_until_line(file, "[HitObjects]");
	for (std::string line; std::getline(file, line) && line != "";)
	{
		beatmap.add_hit_object(hitObjectParser.parse_hitobject(line));
	}
}

void BeatmapParser::read_until_line(std::ifstream& file, std::string line)
{
	for (std::string s; std::getline(file, s) && s != line;);
}