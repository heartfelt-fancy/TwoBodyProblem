//----------------------------------------------------------------------------------
//	File	:	win32_window.h
//
//	Created	:	11/30/09
//
//	Purpose	:	Represent the win32 window the application runs in
//----------------------------------------------------------------------------------
#ifndef _WIN32_WINDOW_H_
#define _WIN32_WINDOW_H_

#include <windows.h>

//	All recognized command line attributes
//	--Find a more fitting place to put this
//	--The info is set in win32_app.cpp and
//	--used in win32_window.cpp
struct cmdline_attrib
{
	int x;
	int y;
	int width;
	int height;
	bool windowed;
	bool noborder;
	bool noshaders;
	bool debug;
};

class win32_window
{
private:
	friend class win32_app;

	HWND m_hWnd;
	HINSTANCE m_hInstance;
	bool m_bWindowed;
	int m_nWidth;
	int m_nHeight;
	const char* m_szWindowName;

private:
	//------------------------------------------------------------------------------
	//	copy ctor and = operator disabled
	//------------------------------------------------------------------------------
	win32_window(const win32_window&);
	win32_window& operator=(const win32_window&);

	//------------------------------------------------------------------------------
	//	windowName - name of the window
	//	cla - cmd line attributes
	//------------------------------------------------------------------------------
	explicit win32_window(const char* windowName, cmdline_attrib* cla);
	~win32_window();

	//------------------------------------------------------------------------------
	//	Function	:	proc
	//
	//	Params		:	hWnd
	//					msg
	//					wParam
	//					lParam
	//
	//	Return		:	Successful or not
	//
	//	Purpose		:	win32 callback for message processing
	//------------------------------------------------------------------------------
	static LRESULT CALLBACK proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//------------------------------------------------------------------------------
	//	Function	:	Update
	//
	//	Params		:	none
	//
	//	Return		:	Continue running (t) or not (f)
	//
	//	Purpose		:	Update the win32 message loop
	//------------------------------------------------------------------------------
	bool Update();

public:
	HINSTANCE GetInstance() const;
	HWND GetHwnd() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	const char* GetWindowName() const;
};

#endif