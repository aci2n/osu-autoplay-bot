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
	Player(std::vector<HitObject>, RECT);
	void operator()();
	~Player();
};

