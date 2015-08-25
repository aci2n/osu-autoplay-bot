#pragma once
#include "HitObject.h"
#include "Beatmap.h"
#include "Utilities.h"

class HitObjectParser
{
	Beatmap mBeatmap;
	Utilities mUtilities;
public:
	HitObjectParser(Beatmap);
	~HitObjectParser();
	HitObject parse_hitobject(std::string);
private:
	std::vector<SliderMovement> parse_slider_movements(std::string, int);
	std::vector<SliderMovement> parse_l_slider(std::string, int);
	std::vector<SliderMovement> parse_p_slider(std::string, int);
	std::vector<SliderMovement> parse_b_slider(std::string, int);
};