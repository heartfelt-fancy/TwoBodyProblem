#include <stdlib.h>
#include "Body.h"
#include "win32_app.h"
#include "timer.h"

timer t;

bool update()
{
	t.tick();

	for (list<Body*>::iterator it = g_Bodies.begin(); it != g_Bodies.end(); it++)
	{
		(*it)->Update(t.timestep());
	}

	return true;
}

int main(int argc, char* argv[])
{
	win32_app app("TwoBodyProblem", argc, argv, -1, -1, &update);

	for (int i = 0; i < 2; i++)
	{
		Body b;

		g_Bodies.push_back(&b);
	}

	return 	app.run();
}
