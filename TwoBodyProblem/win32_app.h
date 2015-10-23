//----------------------------------------------------------------------------------
//	File	:	win32_app.h
//
//	Created	:	11/30/09
//
//	Purpose	:	Create a win32 application layer that handles
//				all functionality specific to win32
//----------------------------------------------------------------------------------
#ifndef _WIN32_APP_H_
#define _WIN32_APP_H_

class win32_window;

class win32_app
{
private:
	//------------------------------------------------------------------------------
	//	Application name
	//------------------------------------------------------------------------------
	const char* m_szAppName;

	//------------------------------------------------------------------------------
	//	Application window
	//------------------------------------------------------------------------------
	win32_window* m_Window;

	//------------------------------------------------------------------------------
	//	Running or not
	//------------------------------------------------------------------------------
	bool m_bRunning;

	//------------------------------------------------------------------------------
	//	Function	:	m_AppUpdate
	//
	//	Params		:	none
	//
	//	Return		:	Successful update
	//
	//	Purpose		:	Allow the user to insert their own code into the win32
	//					system to expand the functionality of the main loop.
	//------------------------------------------------------------------------------
	bool (*m_AppUpdate)();

public:

private:
	//------------------------------------------------------------------------------
	//	copy ctor and = operator disabled
	//------------------------------------------------------------------------------
	win32_app(const win32_app&);
	win32_app& operator=(const win32_app&);

	//	TODO	:	when integration comes, update this to
	//				return error codes for which parts failed
	//				and use debug messages to fprint output
	bool check_resources();

public:
	//------------------------------------------------------------------------------
	//	appName - application name
	//	argc - cmd line argument count
	//	argv - cmd line arguments
	//	AppUpdate - The user update routine to use in the main loop
	//	UserCmdParse - Any special actions to take on the command line
	//------------------------------------------------------------------------------
	explicit win32_app(const char* appName, int argc, char* argv[], int nWidth = -1, int nHeight = -1, bool (*AppUpdate)() = 0, void (*UserCmdParse)(int argc, char* argv[]) = 0);
	~win32_app();

	//------------------------------------------------------------------------------
	//	Function	:	run
	//
	//	Params		:	none
	//
	//	Return		:	exit code
	//
	//	Purpose		:	win32 app's main execution body
	//------------------------------------------------------------------------------
	int run();

	//------------------------------------------------------------------------------
	//	Function	:	GetWindow
	//
	//	Params		:	none
	//
	//	Return		:	Pointer to the window
	//
	//	Purpose		:	Allow the user to look at the window attributes but
	//					not to change anything
	//------------------------------------------------------------------------------
	const win32_window* const GetWindow() const;
};

#endif