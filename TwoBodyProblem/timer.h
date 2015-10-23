#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>

class timer
{
private:
	DWORD m_dwLastTime;
	int m_nTicks;
	float m_fAccumulator;
	float m_fTicksPerSec;
	float m_fTimeStep;

private:
	timer(const timer&);
	timer& operator=(const timer&);

public:
	timer();
	~timer();

	void reset();
	float tick();

	float ticks_per_second();
	float timestep();
};

#endif