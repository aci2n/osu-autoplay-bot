#include "stdafx.h"
#include "CoordinatesTranslator.h"

CoordinatesTranslator::CoordinatesTranslator()
{
}


CoordinatesTranslator::~CoordinatesTranslator()
{
}

std::vector<int> CoordinatesTranslator::translate_coordinates(RECT rect, std::vector<HitObject>* hitObjects)
{
	int resX = rect.right - rect.left;
	int resY = rect.bottom - rect.top;

	int playAreaLeft = rect.left + int(resX * .105); //.105 casa y .13 laburo
	int playAreaTop = rect.top + int(resY * .14);
	int playAreaRight = rect.right - int(resX * .1);
	int playAreaBottom = rect.bottom - int(resY * .075);

	int playAreaResX = playAreaRight - playAreaLeft;
	int playAreaResY = playAreaBottom - playAreaTop;

	double factorX = (double)playAreaResX / 512;
	double factorY = (double)playAreaResY / 384;

	int finalX;
	int finalY;
	std::vector<SliderMovement>* pSliders;
	std::pair<int, int> to;
	int size;

	for (HitObject& h : *hitObjects)
	{
		finalX = playAreaLeft + (int)(h.x() * factorX);
		finalY = playAreaTop + (int)(h.y() * factorY);
		h.set_coordinates(finalX, finalY);

		//translate slider movement coordinates
		pSliders = h.slider_movements();
		size = pSliders->size();
		for (int i = 0; i < size; i++)
		{
			to = pSliders->at(i).to();
			finalX = playAreaLeft + (int)(to.first * factorX);
			finalY = playAreaTop + (int)(to.second * factorY);
			pSliders->at(i).set_pair(finalX, finalY);
		}
	}

	std::vector<int> v(3);
	v[0] = playAreaLeft + (int)(256 * factorX);
	v[1] = playAreaTop + (int)(192 * factorX);
	v[2] = playAreaResX / 4;
	return v;
};