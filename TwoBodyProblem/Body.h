#ifndef _BODY_H_
#define _BODY_H_

#include "float2.h"

namespace GravitationalPhysics
{
	const float g_GravitationalConstant = 6.67 * 0.000000000001;

	class Body
	{
	public:
		float2 position;
		float2 velocity;
		float2 totalForces;
		float mass;

	private:

	public:
		Body();
		~Body();

		void Reset();
		void Update(float dt);

		void SetPosition(float2 _pos);
		void SetVelocity(float2 _vel);
		void SetTotalForces(float2 _tf);
		void SetMass(float _mass);

		float2 GetPosition();
		float2 GetVelocity();
		float2 GetTotalForces();
		float GetMass();

	private:
		Body(const Body&) {};
		Body& operator=(const Body&) {};
	};
}

#endif