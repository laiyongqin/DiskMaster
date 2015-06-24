#ifndef _FOR_TEST_H
#define _FOR_TEST_H

#include <windows.h>
#include <dbt.h>

#include <exception>
#include <system_error>

#define HARDWARE_MONITOR_CLASS_NAME					"Hardware PnP Monitor CLASS"
#define HARDWARE_MONITOR_WND_NAME					"Hardware PnP Monitor WND"

class HardwareMonitor
{
private:
	HWND wnd;
	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		PDEV_BROADCAST_HDR header = (PDEV_BROADCAST_HDR)lParam;
		DEV_BROADCAST_PORT *port_info = nullptr;
		char *name = nullptr;

		if (uMsg == WM_DEVICECHANGE) {			
			switch (wParam) {
				case DBT_DEVICEARRIVAL:
					if (header->dbch_devicetype == DBT_DEVTYP_PORT) {
						port_info = (PDEV_BROADCAST_PORT)(lParam);
						name = (char *)port_info->dbcp_name;
						
					}
					break;
				case DBT_DEVICEREMOVECOMPLETE:
					if (header->dbch_devicetype == DBT_DEVTYP_PORT) {
						port_info = (PDEV_BROADCAST_PORT)(lParam);
						name = (char *)port_info->dbcp_name;
					}
					break;
			}
			return TRUE;
		}
		else {
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void RegisterWindowClass(void)
	{
		WNDCLASSEXA wce;
		memset(&wce, 0x00, sizeof(WNDCLASSEX));

		wce.cbSize = sizeof(wce);
		wce.lpfnWndProc = HardwareMonitor::StaticWindowProc;
		
		wce.hInstance = ::GetModuleHandle(NULL);
		if (wce.hInstance == NULL) {
			std::error_code error(::GetLastError(), std::system_category());
			throw std::system_error(error, "HardwareMonitor::RegisterWindowClass()");
		}

		wce.lpszClassName = HARDWARE_MONITOR_CLASS_NAME;

		if (!::RegisterClassExA(&wce)) {
			std::error_code error(::GetLastError(), std::system_category());
			if (ERROR_CLASS_ALREADY_EXISTS != error.value()) {
				throw std::system_error(error, "HardwareMonitor::RegisterWindowClass()");
			}
		}
	}

	void UnregisterWindowClass(void)
	{
		DestroyWindow();
		::UnregisterClassA(HARDWARE_MONITOR_CLASS_NAME, ::GetModuleHandle(NULL));
	}

	void CraeteWindow(void)
	{
		HINSTANCE hinst = ::GetModuleHandle(NULL);
		wnd = ::CreateWindowA(HARDWARE_MONITOR_CLASS_NAME, HARDWARE_MONITOR_WND_NAME, 0,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinst, NULL);
		if (!wnd) {
			std::error_code error(::GetLastError(), std::system_category());
			throw std::system_error(error, "HardwareMonitor::CraeteWindow()");
		} 
	}

	void DestroyWindow(void)
	{
		if (wnd) {
			::DestroyWindow(wnd);
			wnd = NULL;
		}
	}

	void Initialize(void)
	{
		RegisterWindowClass();
		CraeteWindow();
	}

public:
	HardwareMonitor(void) : wnd(NULL)
	{
		Initialize();
	}

	~HardwareMonitor(void)
	{
		UnregisterWindowClass();
	}
};

#endif // _FOR_TEST_H