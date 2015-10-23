#include "win32_app.h"
#include "win32_window.h"
//#include <windows.h>

#define _B  (unsigned int)0x00000001		//	1 Byte
#define _KB (unsigned int)0x00000400		//	1 KB
#define _MB (unsigned int)0x00100000		//	1 MB
#define _GB (unsigned __int64)0x40000000	//	1 GB

void parse_cmdline(int argc, char* argv[], void* cmdAttrib)
{
	cmdline_attrib* cla = reinterpret_cast<cmdline_attrib*>(cmdAttrib);

	for(int i=0; i<argc; ++i)
	{
		const char* arg = argv[i];

		//	windowed/fullscreen
		if(!strcmp(arg, "-windowed"))
		{
			cla->windowed = true;
		}
		//	window border
		else if(!strcmp(arg, "-noborder"))
		{
			cla->noborder = true;
		}
		//	debug output and events
		else if(!strcmp(arg, "-debug"))
		{
			cla->debug = true;
		}
		//	shader support
		else if(!strcmp(arg, "-noshaders"))
		{
			cla->noshaders = true;
		}
		//	window width
		else if(!strcmp(arg, "-width"))
		{
			++i;

			const char* val = argv[i];
			cla->width = atoi(val);
		}
		//	window height
		else if(!strcmp(arg, "-height"))
		{
			++i;

			const char* val = argv[i];
			cla->height = atoi(val);
		}
		//	x coordinate
		else if(!strcmp(arg, "-x"))
		{
			++i;

			const char* val = argv[i];
			cla->x = atoi(val);
		}
		//	y coordinate
		else if(!strcmp(arg, "-y"))
		{
			++i;

			const char* val = argv[i];
			cla->y = atoi(val);
		}
	}
}

win32_app::win32_app(const char* appName, int argc, char* argv[], int nWidth, int nHeight, bool (*AppUpdate)(), void (*UserCmdParse)(int argc, char* argv[]))
	: m_szAppName(appName), m_bRunning(true), m_Window(NULL)
{
	cmdline_attrib cla;
	memset(&cla, 0, sizeof(cmdline_attrib));

	//	setup defaults
	cla.x = -1;
	cla.y = -1;

	if(nWidth == -1)
		cla.width = 640;
	else
		cla.width = nWidth;

	if(nHeight == -1)
		cla.height = 480;
	else
		cla.height = nHeight;

#ifdef _DEBUG
	cla.windowed = true;
#else
	cla.windowed = false;
#endif

	parse_cmdline(argc, argv, (void*)&cla);

	if(UserCmdParse)
		UserCmdParse(argc, argv);

	m_AppUpdate = AppUpdate;

	//	create window
	if(check_resources())
		m_Window = new win32_window(m_szAppName, &cla);
	else
		m_bRunning = false;
}

win32_app::~win32_app()
{
	//	destroy window
	if(m_Window)
	{
		delete m_Window;
		m_Window = NULL;
	}
}

bool win32_app::check_resources()
{
	extern bool chk_mutex(const char* szName);
	extern bool chk_hdd(unsigned __int64 spaceNeeded);
	extern bool chk_mem(int physRam, int vRam);
	extern bool chk_cpu(int minSpeed);

	//	mutex test
	if(!chk_mutex(m_szAppName))
		return false;

	//	hdd test
	if(!chk_hdd(1*_GB))
		return false;

	//	memtest
	if(!chk_mem(256*_MB, 512*_MB))
		return false;

	//	cputest
	if(!chk_cpu(1300))
		return false;

	return true;
}

int win32_app::run()
{
	while(m_bRunning)
	{
		//	update window
		if(!m_Window->Update())
			m_bRunning = false;

		//	update user's application (if supplied)
		if(m_AppUpdate)
			if(!m_AppUpdate())
				m_bRunning = false;
	}

	return 0;
}

const win32_window* const win32_app::GetWindow() const
{
	return m_Window;
}