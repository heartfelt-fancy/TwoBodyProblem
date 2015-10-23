#include <stdlib.h>
#include "Body.h"
#include "win32_app.h"

int main(int argc, char* argv[])
{
	win32_app app("TwoBodyProblem", argc, argv);

	return 	app.run();
}