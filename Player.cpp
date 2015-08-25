#include "stdafx.h"
#include "Player.h"

const int key1 = 'X';
const int key2 = 'Z';
const int streamTime = 60;
const int spinnerTime = 800;
const int minWaitTime = 10;

Player::Player()
{

}

Player::Player(std::vector<HitObject> hitObjects, RECT desktopRect, std::vector<int> windowValues)
	: mHitObjects(hitObjects), mKeyboardRobot(),
	mMouseRobot(desktopRect.right, desktopRect.bottom, windowValues)
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
	int afterHoldX;
	int afterHoldY;
	const int size = mHitObjects.size();

	mMouseRobot.mouse_move_absolute(mHitObjects[0].x(), mHitObjects[0].y()); //first beat

	for (int i = 0; i < size; i++)
	{
		//std::cout << "x move: " << mHitObjects[i].x() << ", y move: " << mHitObjects[i].y() << std::endl;
		mKeyboardRobot.press_key(key);

		process_hitobject_hold(&mHitObjects[i], &waitTime, &afterHoldX, &afterHoldY);

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
				//std::cout << "afterholdX: " << afterHoldX << ", afterholdY: " << afterHoldY << std::endl;
				mMouseRobot.emulate_line_move(afterHoldX, afterHoldY, mHitObjects[i + 1].x(), mHitObjects[i + 1].y(), sleepTime);
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

void Player::process_hitobject_hold(HitObject* hitObject, int* waitTime, int* afterHoldX, int* afterHoldY)
{
	switch (hitObject->type())
	{
	case HitObjectType::NORMAL:
		*waitTime = minWaitTime;
		*afterHoldX = hitObject->x();
		*afterHoldY = hitObject->y();
		Sleep(*waitTime);
		break;
	case HitObjectType::SLIDER:
		*waitTime = hitObject->hold_for();
		process_slider_movements(hitObject, afterHoldX, afterHoldX);
		break;
	case HitObjectType::SPINNER:
		*waitTime = hitObject->hold_for();
		mMouseRobot.emulate_spin(*waitTime, afterHoldX, afterHoldY);
		break;
	}
}

void Player::process_slider_movements(HitObject* hitObject, int* afterHoldX, int* afterHoldY)
{
	std::vector<SliderMovement>* pSliders = hitObject->slider_movements();
	const int size = hitObject->slider_movements()->size();
	int previousX = hitObject->x();
	int previousY = hitObject->y();
	int currentX;
	int currentY;

	//if only because not all sliders are implemented yet
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "sliding... components: " << size << std::endl;
			currentX = pSliders->at(i).to().first;
			currentY = pSliders->at(i).to().second;

			mMouseRobot.emulate_line_move(
				previousX,
				previousY,
				currentX,
				currentY,
				pSliders->at(i).time()
				);

			previousX = currentX;
			previousY = currentY;
			
		}
	}
	else
	{
		Sleep(hitObject->hold_for());
	}

	*afterHoldX = previousX;
	*afterHoldY = previousY;
}