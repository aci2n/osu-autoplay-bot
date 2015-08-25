#pragma once
#include "Beatmap.h"
#include <Windows.h>
#include "MouseRobot.h"
#include "KeyboardRobot.h"

class Player
{
	MouseRobot mMouseRobot;
	KeyboardRobot mKeyboardRobot;
	std::vector<HitObject> mHitObjects;
public:
	Player();
	Player(std::vector<HitObject>, RECT, std::vector<int>);
	void operator()();
	~Player();
private:
	void processHitObjectHold(HitObject*, int*, int*, int*);
};

