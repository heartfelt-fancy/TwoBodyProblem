#include "fmath.h"

const float PRECISION_TOLERANCE = 0.00001f;
const float FMATH_PI = 3.14159f;


bool fIsEqual(float a, float b)
{
	return (fabs(a - b) < PRECISION_TOLERANCE);
}

bool fIsZero(float a)
{
	return (fabs(a) < PRECISION_TOLERANCE);
}

float fMin(float a, float b)
{
	return ((a < b) ? a : b);
}

float fMax(float a, float b)
{
	return ((a > b) ? a : b);
}

float fRad2Deg(float r)
{
	return (r * 180.0f / FMATH_PI);
}

float fDeg2Rad(float d)
{
	return (d * FMATH_PI / 180.0f);
}
