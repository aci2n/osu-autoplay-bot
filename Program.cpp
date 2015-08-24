#include "stdafx.h"
#include "BeatmapParser.h"

int main()
{
	BeatmapParser parser("C:/Program Files (x86)/osu!/Songs/3678 Tenacious D - Tribute/Tenacious D - Tribute (awp) [Easy].osu");
	Beatmap beatmap = parser.parse_beatmap();
}