#include "stdafx.h"
#include "Player.h"

const int key1 = 'X';
const int key2 = 'Z';
const int streamTime = 60;
const int spinnerTime = 800;

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
	int startTime = GetTickCount(); //for first beat
	int expectedTime;
	int diff;
	int adjustedTime = 0; //for first beat
	int sleepTime;
	int afterHoldX;
	int afterHoldY;
	int betweenReleaseAndClick;
	const int size = mHitObjects.size();

	mMouseRobot.mouse_move_absolute(mHitObjects[0].x(), mHitObjects[0].y()); //first beat

	for (int i = 0; i < size; i++)
	{
		//std::cout << "x move: " << mHitObjects[i].x() << ", y move: " << mHitObjects[i].y() << std::endl;
		mKeyboardRobot.press_key(key);

		process_hitobject_hold(&mHitObjects[i], &afterHoldX, &afterHoldY);
		//std::cout << "afterholdX: " << afterHoldX << ", afterholdY: " << afterHoldY << std::endl;

		mKeyboardRobot.release_key();

		if (i < size - 1)
		{
			diff = mHitObjects[i + 1].start_time() - mHitObjects[i].start_time();
			betweenReleaseAndClick = diff - mHitObjects[i].hold_for();

			key = betweenReleaseAndClick > streamTime ? key1 : (key == key1 ? key2 : key1);

			//calculate expected time for next beat start
			expectedTime = startTime + diff + adjustedTime;
			//emulate line move between beats
			sleepTime = betweenReleaseAndClick + adjustedTime;
			if (sleepTime > 0)
			{
				//std::cout << "afterholdX: " << afterHoldX << ", afterholdY: " << afterHoldY << std::endl << std::endl;
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

void Player::process_hitobject_hold(HitObject* hitObject, int* afterHoldX, int* afterHoldY)
{
	switch (hitObject->type())
	{
	case HitObjectType::NORMAL:
		*afterHoldX = hitObject->x();
		*afterHoldY = hitObject->y();
		Sleep(hitObject->hold_for());
		break;
	case HitObjectType::SLIDER:
		process_slider_movements(hitObject, afterHoldX, afterHoldY);
		break;
	case HitObjectType::SPINNER:
		mMouseRobot.emulate_spin(hitObject->hold_for(), afterHoldX, afterHoldY);
		break;
	}
}

void Player::process_slider_movements(HitObject* hitObject, int* afterHoldX, int* afterHoldY)
{
	std::vector<SliderMovement>* pSliders = hitObject->slider_movements();
	const int size = pSliders->size();
	int previousX = hitObject->x();
	int previousY = hitObject->y();
	int holdFor = hitObject->hold_for();
	int currentX;
	int currentY;
	int time;

	for (int i = 0; i < size; i++)
	{
		time = pSliders->at(i).time();
		//std::cout << "sliding... components: " << size << std::endl;
		currentX = pSliders->at(i).to().first;
		currentY = pSliders->at(i).to().second;
		//std::cout << "pX: " << previousX << " pY: " << previousY << std::endl;
		//std::cout << "cX: " << currentX << " cY: " << currentY << std::endl << std::endl;
		mMouseRobot.emulate_line_move(
			previousX,
			previousY,
			currentX,
			currentY,
			time
			);

		previousX = currentX;
		previousY = currentY;

		holdFor -= time;
	}

	*afterHoldX = previousX;
	*afterHoldY = previousY;

	/*if (holdFor > 0)
	{
		//std::cout << "sleeping leftovers: " << holdFor << std::endl;
		Sleep(holdFor);
	}*/
}