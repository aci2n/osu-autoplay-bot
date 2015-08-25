#pragma once
#include "Beatmap.h"
#include "Utilities.h"
#include "HitObjectParser.h"

class BeatmapParser
{
	std::string mFilename;
	Utilities mUtilities;
public:
	BeatmapParser(std::string filename);
	~BeatmapParser();
	Beatmap parse_beatmap();
private:
	std::string read_value(std::ifstream&, std::string);
	std::vector<TimingSection> read_timing_sections(std::ifstream&);
	void add_hitobjects(std::ifstream&, Beatmap&);
	void read_until_line(std::ifstream&, std::string);
};

