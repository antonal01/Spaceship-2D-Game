#pragma once
#include <random>
#include "graphics.h"
class Delay {
	float delay1 = 0.0f;
	float speed = 0.5f;
	float time = 500.0f; 
	float prevx=-200.0f, prevy= -200.0f;
public:
	Delay();
	bool delay();
	void setPrevX_Y(float delay, float delay1) { prevx = delay; prevy = delay1; }
	float getPrevx() { return prevx; }
	float getPrevy() { return prevy; }
	float getTime() { return time; }
	void setSpeed(float delay) { speed = delay; }
	void setTime(float time) { this->time = time; }
	void resetDelay() { delay1 = 0.0f; }
};


float rand0to1();


struct Disk {
	float cx, cy;
	float radius;
	float time;
};

struct prev
{
	float size;
	float prevx, prevy;
};