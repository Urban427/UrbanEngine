#pragma once

struct WindowInputs
{
	unsigned char* 	 states = nullptr;
	Vector2*		 poses  = nullptr;
	Vector2*		 oldPoses  = nullptr;
	
	unsigned int number = 0;
};