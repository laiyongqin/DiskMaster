// DiskMaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include "ftd2xx.h"
#include "FTChipID.h"

#include "ForTest.h"

#pragma comment(lib, "ftd2xx.lib")
#pragma comment(lib, "FTChipID.lib")

int _tmain(int argc, _TCHAR* argv[])
{

	HardwareMonitor hw_monitor;

	////////////////////////////////////////////////////////
	// Message loop
	//
	MSG msg;
	BOOL ret = FALSE;
	memset(&msg, 0x00, sizeof(MSG));
	while (ret = ::GetMessage(&msg, NULL, 0, 0)) {
		if (ret == -1) {
			return ::GetLastError();
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

