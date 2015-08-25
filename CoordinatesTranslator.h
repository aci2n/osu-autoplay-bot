#pragma once
#include <Windows.h>
#include "HitObject.h"
class CoordinatesTranslator
{
public:
	CoordinatesTranslator();
	~CoordinatesTranslator();
	std::vector<int> translate_coordinates(RECT, std::vector<HitObject>*);
};

