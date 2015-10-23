#include "timer.h"

timer::timer() : m_dwLastTime(GetTickCount()), m_nTicks(0), m_fAccumulator(0), m_fTicksPerSec(0), m_fTimeStep(0)
{

}

timer::~timer()
{

}

void timer::reset()
{
	m_dwLastTime = GetTickCount();
	m_nTicks = 0;
	m_fAccumulator = 0;
	m_fTicksPerSec = 0;
	m_fTimeStep = 0;
}

float timer::tick()
{
	m_fTimeStep = (GetTickCount() - m_dwLastTime) * 0.001f;
	m_dwLastTime = GetTickCount();

	m_fAccumulator += m_fTimeStep;
	++m_nTicks;

	if(m_fAccumulator >= 0.1f)
	{
		m_fTicksPerSec = ((float)m_nTicks / m_fAccumulator);
		m_nTicks = 0;
		m_fAccumulator = 0;
	}

	return m_fTimeStep;
}

float timer::ticks_per_second()
{
	return m_fTicksPerSec;
}

float timer::timestep()
{
	return m_fTimeStep;
}