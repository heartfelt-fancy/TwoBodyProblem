#include "fmath.h"
#include "float2.h"

float2::float2(void) : x(0), y(0)
{

}

float2::float2(float _x, float _y) : x(_x), y(_y)
{

}

float2::float2(const float* f) : x(f[0]), y(f[1])
{

}

float2::float2(const float2& v) : x(v.x), y(v.y)
{

}

float2::~float2(void)
{

}

float2& float2::operator  =(const float2& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

float2& float2::operator  =(const float*  v)
{
	x = v[0];
	y = v[1];

	return *this;
}

float2& float2::operator +=(const float2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

float2& float2::operator -=(const float2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

float2& float2::operator *=(float f)
{
	x *= f;
	y *= f;

	return *this;
}

float2& float2::operator /=(float f)
{
	x /= f;
	y /= f;

	return *this;
}

float2 float2::operator +(void) const
{
	return *this;
}

float2 float2::operator -(void) const
{
	return (*this * -1);
}

float2 float2::operator +(const float2& v) const
{
	float2 res;

	res.x = x + v.x;
	res.y = y + v.y;

	return res;
}

float2 float2::operator -(const float2& v) const
{
	float2 res;

	res.x = x - v.x;
	res.y = y - v.y;

	return res;
}

float2 float2::operator *(float f) const
{
	float2 res;

	res.x = x * f;
	res.y = y * f;

	return res;
}

float2 float2::operator /(float f) const
{
	float2 res;

	res.x = x / f;
	res.y = y / f;

	return res;
}

float2 operator *(float f, const float2& v)
{
	return v * f;
}

bool float2::operator ==(const float2& v) const
{
	return (fIsEqual(x, v.x) && fIsEqual(y, v.y));
}

bool float2::operator !=(const float2& v) const
{
	return (!fIsEqual(x, v.x) && !fIsEqual(y, v.y));
}

float float2::operator[](unsigned int i)
{
	if (i < 2)
		return e[i];
	return 0;
}

float f2Length(const float2* pV)
{
	return sqrt(f2LengthSq(pV));
}

float f2LengthSq(const float2* pV)
{
	return (pV->x * pV->x) + (pV->y * pV->y);
}

float f2Dot(const float2* pV, const float2* pW)
{
	return (pV->x * pW->x) + (pV->y * pW->y);
}

float2* f2Normalize(float2* pOut, const float2* pV)
{
	float fLen = f2Length(pV);

	if (fLen)
		*pOut = *pV / fLen;
	else
		*pOut = *pV;

	return pOut;
}

float2* f2Add(float2* pOut, const float2* pV, const float2* pW)
{
	*pOut = *pV + *pW;

	return pOut;
}

float2* f2Subtract(float2* pOut, const float2* pV, const float2* pW)
{
	*pOut = *pV - *pW;

	return pOut;
}


float2* f2Cross(float2* pOut, const float2* pV, const float2* pW)
{
	//      TODO    :       THIS, DERP
	return pOut;
}

float2* f2Minimize(float2* pOut, const float2* pV, const float2* pW)
{
	pOut->x = fMin(pV->x, pW->x);
	pOut->y = fMin(pV->y, pW->y);

	return pOut;
}

float2* f2Maximize(float2* pOut, const float2* pV, const float2* pW)
{
	pOut->x = fMax(pV->x, pW->x);
	pOut->y = fMax(pV->y, pW->y);

	return pOut;
}

float2* f2Scale(float2* pOut, const float2* pV, float s)
{
	*pOut = *pV * s;

	return pOut;
}

float2* f2Lerp(float2* pOut, const float2* pV, const float2* pW, float s)
{
	*pOut = *pV + (*pW * s);

	return pOut;
}
