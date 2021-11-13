#ifndef MATH_H
#define MATH_H
#include <cmath>

struct Mouse
{
	float x, y;
	bool lDown, rDown;

	Mouse() : x(0), y(0), lDown(false), rDown(false) {}
};

// Convert radian value to degreees
inline float degrees(const float f)
{
	return (f * 180 / M_PI);
}

// Convert degree value to radians
inline float radians(const float f)
{
	return (f * M_PI / 180);
}

#endif /* MATH_H */