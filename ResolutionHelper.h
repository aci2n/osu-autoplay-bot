#pragma once
#include <Windows.h>

class ResolutionHelper
{
public:
	ResolutionHelper();
	~ResolutionHelper();
	RECT get_desktop_rect();
};

