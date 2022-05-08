#pragma once

#include <math.h>
#define PI 3.14159265358f

inline float toRadians(float degrees)
{
	return degrees * (PI / 180.0f);
}