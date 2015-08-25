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
};