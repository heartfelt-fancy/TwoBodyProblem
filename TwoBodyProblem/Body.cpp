#include "Body.h"

namespace GravitationalPhysics
{
	Body::Body() : position(0, 0), velocity(0, 0), mass(0)
	{
		Reset();
	}

	Body::~Body()
	{

	}

	void Body::SetPosition(float2 _pos)
	{
		position = _pos;
	}

	void Body::SetVelocity(float2 _vel)
	{
		velocity = _vel;
	}

	void Body::SetTotalForces(float2 _tf)
	{
		totalForces = _tf;
	}

	void Body::SetMass(float _mass)
	{
		mass = _mass;
	}

	float2 Body::GetPosition()
	{
		return position;
	}

	float2 Body::GetVelocity()
	{
		return velocity;
	}

	float2 Body::GetTotalForces()
	{
		return totalForces;
	}

	float Body::GetMass()
	{
		return mass;
	}

	void Body::Reset()
	{
		//	set random position

		//	set random mass between x and y
	}

	void Body::Update(float dt)
	{
		//	Update velocity by all forces acting on object

		//	Calculate position/velocity for next frame

		//	Zeroize totalForces
	}
}