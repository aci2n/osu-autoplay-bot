#pragma once
#include <Windows.h>
#include <tlhelp32.h>

class ProcessIdFinder
{
public:
	ProcessIdFinder();
	~ProcessIdFinder();
	int get_process_id(std::wstring&);
};

