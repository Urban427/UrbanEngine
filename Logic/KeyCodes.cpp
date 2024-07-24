#include "KeyCodes.h"

Vector2* poses;
Vector2* oldPoses;
unsigned char* keyBoardState;
unsigned char* oldkeyBoarState;

void initKeyCodes(unsigned char* state, unsigned char* old_state, Vector2* pose, Vector2* oldPose)
{
	poses = pose;
	oldPoses = oldPose;
	keyBoardState 	= state;
	oldkeyBoarState = old_state;
}

bool GetKey(unsigned char key)
{
	return keyBoardState[key] & 0x80;
}

bool GetKeyDown(unsigned char key)
{
	return (keyBoardState[key] & 0x80) && (oldkeyBoarState[key] & 0x80) != 0x80;
}

bool GetKeyUp(unsigned char key)
{
	return (keyBoardState[key] & 0x80) != 0x80 && (oldkeyBoarState[key] & 0x80);
}

Vector2 mousePositionDelta()
{
	return Vector2(poses->x - oldPoses->x, poses->y - oldPoses->y);
}