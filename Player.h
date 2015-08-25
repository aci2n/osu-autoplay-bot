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
	void process_hitobject_hold(HitObject*, int*, int*, int*);
	void process_slider_movements(HitObject*, int*, int*);
};

