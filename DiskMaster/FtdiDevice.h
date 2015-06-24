#ifndef _FTDI_DEVICE_H
#define _FTDI_DEVICE_H

#include "ftd2xx.h"
#include "FTChipID.h"

#pragma comment(lib, "ftd2xx.lib")
#pragma comment(lib, "FTChipID.lib")

class FtdiDevice
{
public:
	FtdiDevice();
	~FtdiDevice();
};

#endif // _FTDI_DEVICE_H

