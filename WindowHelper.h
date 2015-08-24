#pragma once
#include <Windows.h>

class WindowHelper
{
public:
	WindowHelper();
	~WindowHelper();
	RECT get_rect(int);	
	RECT get_desktop_rect();
};

