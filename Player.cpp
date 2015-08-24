#include "stdafx.h"
#include "Player.h"

const int key1 = 'X';
const int key2 = 'Z';
const int streamTime = 115;
const int spinnerTime = 800;
const int minWaitTime = 10;

Player::Player()
{

}

Player::Player(std::vector<HitObject> hitObjects, RECT desktopRect) 
	: mHitObjects(hitObjects), mKeyboardRobot(), mMouseRobot(desktopRect.right, desktopRect.bottom)
{
}

Player::~Player()
{
}

void Player::operator()()
{
	int key = key1;
	int waitTime;
	int startTime = GetTickCount(); //for first beat
	int expectedTime;
	int diff;
	int adjustedTime = 0; //for first beat
	int sleepTime;
	const int size = mHitObjects.size();

	mMouseRobot.mouse_move_absolute(mHitObjects[0].x(), mHitObjects[0].y()); //first beat

	for (int i = 0; i < size; i++)
	{
		//std::cout << "x move: " << mHitObjects[i].x() << ", y move: " << mHitObjects[i].y() << std::endl;
		mKeyboardRobot.press_key(key);

		waitTime = mHitObjects[i].hold_for() > 0 ? mHitObjects[i].hold_for() : minWaitTime;
		Sleep(waitTime);

		mKeyboardRobot.release_key();

		key = waitTime > streamTime ? key1 : (key == key1 ? key2 : key1);

		if (i < size - 1)
		{
			diff = mHitObjects[i + 1].start_time() - mHitObjects[i].start_time();
			//calculate expected time for next beat start
			expectedTime = startTime + diff + adjustedTime;
			//emulate line move between beats
			sleepTime = diff - waitTime + adjustedTime;
			if (sleepTime > 0)
			{
				mMouseRobot.emulate_line_move(mHitObjects[i].x(), mHitObjects[i].y(), mHitObjects[i + 1].x(), mHitObjects[i + 1].y(), sleepTime);
			}
			else
			{
				mMouseRobot.mouse_move_absolute(mHitObjects[i + 1].x(), mHitObjects[i + 1].y());
			}
			//set next beat start time and calculate difference from expected time
			startTime = GetTickCount();
			adjustedTime = expectedTime - startTime;
		}
	}
}