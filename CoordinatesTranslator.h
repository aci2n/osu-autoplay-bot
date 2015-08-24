#pragma once
#include <Windows.h>
#include "HitObject.h"
class CoordinatesTranslator
{
public:
	CoordinatesTranslator();
	~CoordinatesTranslator();
	void translate_coordinates(RECT, std::vector<HitObject>*);
};

