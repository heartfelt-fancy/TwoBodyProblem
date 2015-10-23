#ifndef _FLOAT2_H_
#define _FLOAT2_H_

class float2
{
public:
	union
	{
		float e[2];

		struct
		{
			float x, y;
		};
	};

	float2(void);
	float2(float _x, float _y);
	float2(const float* f);
	float2(const float2& v);
	~float2(void);

	// Assignment operators
	float2& operator  =(const float2& v);
	float2& operator  =(const float*  v);
	float2& operator +=(const float2& v);
	float2& operator -=(const float2& v);
	float2& operator *=(float f);
	float2& operator /=(float f);

	// Unary operators
	float2 operator +(void) const;
	float2 operator -(void) const;

	// Binary operators
	float2 operator +(const float2& v) const;
	float2 operator -(const float2& v) const;
	float2 operator *(float f) const;
	float2 operator /(float f) const;
	friend float2 operator *(float f, const float2& v);

	// Logical operators
	bool operator ==(const float2& v) const;
	bool operator !=(const float2& v) const;

	// Indexing operators
	float operator[](unsigned int i);
};

float f2Length(const float2* pV);
float f2LengthSq(const float2* pV);
float f2Dot(const float2* pV, const float2* pW);

float2* f2Normalize(float2* pOut, const float2* pV);
float2* f2Add(float2* pOut, const float2* pV, const float2* pW);
float2* f2Subtract(float2* pOut, const float2* pV, const float2* pW);
float2* f2Cross(float2* pOut, const float2* pV, const float2* pW);
float2* f2Minimize(float2* pOut, const float2* pV, const float2* pW);
float2* f2Maximize(float2* pOut, const float2* pV, const float2* pW);
float2* f2Scale(float2* pOut, const float2* pV, float s);
float2* f2Lerp(float2* pOut, const float2* pV, const float2* pW, float s);

#endif