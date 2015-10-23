#include <windows.h>
#include <direct.h>
#include <cmath>
#pragma comment(lib, "winmm.lib")

bool chk_mutex(const char* szName)
{
	//	attempt to create a mutex
	HANDLE handle = CreateMutex(NULL, TRUE, szName);

	//	if it didn't succeed
	if(GetLastError() != ERROR_SUCCESS)
	{
		//	check to see if a window exists with our name
		HWND hWnd = FindWindow(szName, NULL);

		//	if it exists, set the focus on that window and close this one
		if(hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);

			return false;
		}
	}

	return true;
}

bool chk_hdd(unsigned __int64 spaceNeeded)
{
	//	get the system drive
	const int drive = _getdrive();
	struct _diskfree_t diskfree;
	//	get the amount of free space
	_getdiskfree(drive, &diskfree);

	//	calculate how many clusters are needed
	const unsigned __int64 neededClusters = spaceNeeded / (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

	//	check if there are enough free clusters
	if(diskfree.avail_clusters < neededClusters)
		return false;
	return true;
}

bool chk_mem(int physRam, int vRam)
{
	MEMORYSTATUSEX msx;
	GlobalMemoryStatusEx(&msx);

	//	check total physical memory
	if(msx.ullTotalPhys < physRam)
		return false;
	//	check available virtual memory
	if(msx.ullAvailVirtual < vRam)
		return false;

	//	check contiguous virtual memory
	//char* buffer = new char[vRam];

	//if(buffer)
	//	delete buffer;
	//else
	//	return false;

	return true;
}

bool chk_cpu(int minSpeed)
{
	//	TODO	:	make this platform-independent
	//	processor speed is stored in the windows registry
	//	although it's not platform independent, it does
	//	what I want it to do and is acceptable for the time being
	HRESULT res;
	HKEY hKey;
	DWORD data, dataSize;

	//	open HKLM/Hardware/Description/System/CentralProcessor/0
	res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey);

	//	if successful
	if(res == ERROR_SUCCESS)
	{
		//	query the ~MHz value (cpu speed)
		res = RegQueryValueEx(hKey, "~MHz",NULL, NULL, (LPBYTE)&data, &dataSize);

		if(res == ERROR_SUCCESS)
		{
			//	check speed
			if((int)data < minSpeed)
				return false;
		}
	}

	return true;
}