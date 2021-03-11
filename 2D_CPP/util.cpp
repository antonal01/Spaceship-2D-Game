#include "util.h"

float rand0to1()
{
    return rand() / (float)RAND_MAX;
}

Delay::Delay()
{
}

bool Delay::delay()
{
	if (delay1 < time) {
		delay1 += graphics::getDeltaTime() * speed;
		return false;
	}
	else {
		return true;
	}
}
