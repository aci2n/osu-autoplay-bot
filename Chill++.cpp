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
		BeatmapParser parser(R"(C:\Users\alvaro.daniel.calace\AppData\Local\osu!\Songs\118768 xi - Akasha\xi - Akasha (Jemmmmy) [Test].osu)");
		Beatmap beatmap(parser.parse_beatmap());
		int procId = ProcessIdFinder().get_process_id(std::wstring(L"xampp-control.exe"));
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