#include "stdafx.h"
#include "BeatmapParser.h"
#include "Player.h"
#include <Windows.h>
#include "WindowHelper.h"
#include "CoordinatesTranslator.h"
#include "KeyboardHook.h"
#include "ProcessIdFinder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		/*"C:\Program Files (x86)\osu!\Songs\7385 IOSYS - Utage wa Eien ni ~SHD~\IOSYS - Utage wa Eien ni ~SHD~ (DJPop) [TAG4].osu"*/
		/*C:\Program Files (x86)\osu!\Songs\20949 Demetori - Wind God Girl\Demetori - Wind God Girl (lkp) [Extra].osu*/
		/*"C:\Program Files (x86)\osu!\Songs\123839 Akiyama Uni - The Grimoire of Alice\Akiyama Uni - The Grimoire of Alice (Hollow Wings) [Extra].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\134151 Hanatan - Airman ga Taosenai (SOUND HOLIC Ver)\Hanatan - Airman ga Taosenai (SOUND HOLIC Ver.) (Natsu) [CRN's Extra].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\33052 Syrsa - Mad Machine\Syrsa - Mad Machine (Louis Cyphre) [Champion].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\39804 xi - FREEDOM DiVE\xi - FREEDOM DiVE (Nakagawa-Kanon) [FOUR DIMENSIONS].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\24313 Team Nekokan - Can't Defeat Airman\Team Nekokan - Can't Defeat Airman (Blue Dragon) [Holy Shit! It's Airman!!].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\41823 The Quick Brown Fox - The Big Black\The Quick Brown Fox - The Big Black (Blue Dragon) [WHO'S AFRAID OF THE BIG BLACK].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\65994 MiddleIsland - Roze\MiddleIsland - Roze (Lan wings) [Lan].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\29691 Hatsune Miku - With a Dance Number\Hatsune Miku - With a Dance Number (val0108) [0108 style].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\96143 Rtnario - Guitar vs Piano 18X\Rtnario - Guitar vs Piano 18X (Practice) [185 Fullscreen AR10 CS5].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\87509 Mind Vortex - Arc\Mind Vortex - Arc (Natteke) [Nsane].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\37054 Megpoid GUMI - Cosmos\Megpoid GUMI - Cosmos (val0108) [Cosmos].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\93523 Tatsh - IMAGE -MATERIAL- -Version 0-\Tatsh - IMAGE -MATERIAL- Version 0 (Scorpiour) [Scorpiour].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\79725 Nthonius - Trapce\Nthonius - Trapce (ykcarrot) [Trap].osu"*/
		/*"C:\Program Files (x86)\osu!\Songs\180138 Halozy - Genryuu Kaiko\Halozy - Genryuu Kaiko (Hollow Wings) [Mysterious Hymn].osu"*/
		BeatmapParser parser(R"(C:\Program Files (x86)\osu!\Songs\180138 Halozy - Genryuu Kaiko\Halozy - Genryuu Kaiko (Hollow Wings) [Mysterious Hymn].osu)");
		Beatmap beatmap(parser.parse_beatmap());
		//beatmap.apply_doubletime();
		int procId = ProcessIdFinder().get_process_id(std::wstring(L"osu!.exe"));
		WindowHelper w;
		RECT windowRect = w.get_rect(procId);
		RECT desktopRect = w.get_desktop_rect();
		std::vector<int> windowValues = CoordinatesTranslator().translate_coordinates(windowRect, beatmap.get_hit_objects());
		Player player(*beatmap.get_hit_objects(), desktopRect, windowValues);
		KeyboardHook hook(player);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}