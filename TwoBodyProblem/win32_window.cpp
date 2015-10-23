#include "win32_window.h"

win32_window::win32_window(const char* windowName, cmdline_attrib* cla)
	: m_szWindowName(windowName), m_nWidth(cla->width), m_nHeight(cla->height), m_bWindowed(cla->windowed)
{
	//	hide the console window
	typedef HWND (WINAPI *GetConsoleWindowT)(void);
	HMODULE hk32 = GetModuleHandle("kernel32.dll");
	GetConsoleWindowT GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32,"GetConsoleWindow");

	HWND hConWnd = GetConsoleWindow();
	ShowWindow(hConWnd, SW_HIDE);

	//	create the win32 window
	m_hInstance = GetModuleHandle(0);

	WNDCLASSEX wcx;
	memset(&wcx, 0, sizeof(WNDCLASSEX));

	wcx.cbSize			= sizeof(WNDCLASSEX);
	wcx.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcx.lpfnWndProc		= (WNDPROC)proc;
	wcx.cbClsExtra		= 0;
	wcx.cbWndExtra		= 0;
	wcx.hInstance		= m_hInstance;
	wcx.hIcon			= NULL;
	wcx.hCursor			= (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground	= (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wcx.lpszMenuName	= NULL;
	wcx.lpszClassName	= m_szWindowName;
	wcx.hIconSm			= NULL;

	RegisterClassEx(&wcx);

	UINT uiStyle, uiStyleX = 0;

	//	if noborder is specified, make a borderless window
	if(cla->noborder)
		uiStyle = WS_POPUP | WS_VISIBLE | WS_SYSMENU;
	//	if windowed is on, make a bordered window
	else if(cla->windowed)
		uiStyle = WS_OVERLAPPEDWINDOW;
	//	if noborder is not specified but windowed is off, make a borderless window
	else
		uiStyle = WS_POPUP | WS_VISIBLE | WS_SYSMENU;


	//	setup coordinates
	int x, y;

	if(cla->x == -1)
		x = (GetSystemMetrics(SM_CXSCREEN)>>1) - (m_nWidth>>1);
	else
		x = cla->x;
	if(cla->y == -1)
		y = (GetSystemMetrics(SM_CYSCREEN)>>1) - (m_nHeight>>1);
	else
		y = cla->y;

	//	create window handle
	m_hWnd = CreateWindowEx(uiStyleX, wcx.lpszClassName, m_szWindowName,
		uiStyle, x, y, m_nWidth, m_nHeight, NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	SetFocus(m_hWnd);
}

win32_window::~win32_window()
{
	UnregisterClass(m_szWindowName, GetModuleHandle(0));
}

LRESULT CALLBACK win32_window::proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	};

	return DefWindowProc(hWnd, msg, wParam, lParam);
};

bool win32_window::Update()
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
		if(!TranslateMessage(&msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if(msg.message == WM_QUIT)
		return false;
	return true;
}

HINSTANCE win32_window::GetInstance() const
{
	return m_hInstance;
}

HWND win32_window::GetHwnd() const
{
	return m_hWnd;
}

int win32_window::GetWindowWidth() const
{
	return m_nWidth;
}

int win32_window::GetWindowHeight() const
{
	return m_nHeight;
}

const char* win32_window::GetWindowName() const
{
	return m_szWindowName;
}