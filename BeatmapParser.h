#pragma once
#include "Beatmap.h"

class BeatmapParser
{
	std::string mFilename;
public:
	BeatmapParser(std::string filename);
	~BeatmapParser();
	Beatmap parse_beatmap();
private:
	std::string read_value(std::ifstream&, std::string);
	std::vector<TimingSection> read_timing_sections(std::ifstream&);
	void add_hitobjects(std::ifstream&, Beatmap&);
	template<typename T>
	bool contains(std::vector<T>, T);
	std::vector<std::string> split(std::string, std::string);
	void read_until_line(std::ifstream&, std::string);
};

