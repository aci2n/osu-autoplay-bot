#include "stdafx.h"
#include "CoordinatesTranslator.h"

CoordinatesTranslator::CoordinatesTranslator()
{
}


CoordinatesTranslator::~CoordinatesTranslator()
{
}

void CoordinatesTranslator::translate_coordinates(RECT rect, std::vector<HitObject>* hitObjects)
{
	int resX = rect.right - rect.left;
	int resY = rect.bottom - rect.top;

	int playAreaLeft = (int)(rect.left + resX * .13);
	int playAreaTop = (int)(rect.top + resY * .14);
	int playAreaRight = (int)(rect.right - resX * .1);
	int playAreaBottom = (int)(rect.bottom - resY * .075);

	int playAreaResX = playAreaRight - playAreaLeft;
	int playAreaResY = playAreaBottom - playAreaTop;

	double factorX = (double)playAreaResX / 512;
	double factorY = (double)playAreaResY / 384;

	int finalX;
	int finalY;

	for (HitObject& h : *hitObjects)
	{
		finalX = playAreaLeft + (int)(h.x() * factorX);
		finalY = playAreaTop + (int)(h.y() * factorY);
		h.set_coordinates(finalX, finalY);
	}
};