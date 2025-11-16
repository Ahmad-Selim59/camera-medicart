#include "CameraCtrl.h"
#include "USBDevice.h"
#pragma warning(disable:6031) // 解决WSAStartup返回值被忽略警告

void BaseDevice::Initial(void)
{
	(void)CoInitialize(NULL);
    WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
}

void BaseDevice::Release(void)
{
	WSACleanup();
	CoUninitialize();
}

bool BaseDevice::EnumUSBDevices(DeviceList& list)
{
	return USBDevice::EnumDevices(list);
}



BaseDevice* BaseDevice::CreateDevice(DeviceType dt)
{
	if (dt == DeviceType::USB_Device)
		return new USBDevice();
	return NULL;
}

void BaseDevice::DeleteDevice(BaseDevice* dev)
{
	if (dev != NULL) delete dev;
}