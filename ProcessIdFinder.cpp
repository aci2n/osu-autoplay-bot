#include "stdafx.h"
#include "ProcessIdFinder.h"


ProcessIdFinder::ProcessIdFinder()
{
}


ProcessIdFinder::~ProcessIdFinder()
{
}

int ProcessIdFinder::get_process_id(std::wstring& processName)
{
	std::exception pIdException("Could not find PID.");

	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		throw pIdException;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	throw pIdException;
}
