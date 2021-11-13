#ifndef MATH_H
#define MATH_H

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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