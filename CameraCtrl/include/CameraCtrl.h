#ifndef _CAMERA_CTRL_H
#define _CAMERA_CTRL_H

#include <string>
#include <vector>

#ifdef CAMCTRL_EXPORTS
#define CAMCTRL_API __declspec(dllexport)
#else
#define CAMCTRL_API __declspec(dllimport)
#endif

struct CAMCTRL_API DeviceInfo {
	unsigned int DeviceId;
	std::string Name;
	std::string Path;
};

struct CAMCTRL_API PropertyInfo {
	long Min;
	long Max;
	long Step;
	long Default;
	long Current;
	long Valid;
};

typedef std::vector<DeviceInfo> DeviceList;

enum class CAMCTRL_API DeviceType {
	USB_Device
};

class CAMCTRL_API BaseDevice {
public:
	PropertyInfo WhiteBalance;
	PropertyInfo RGain;
	PropertyInfo BGain;
	PropertyInfo AE;
	PropertyInfo Shutter;
	PropertyInfo Iris;
	PropertyInfo Gain;
	PropertyInfo AEBright;
	PropertyInfo Brightness;
    PropertyInfo Hue;
	PropertyInfo Saturation;
	PropertyInfo Sharpness;
	PropertyInfo WDR;
	PropertyInfo Flicker;
	PropertyInfo WDRLevel;
	PropertyInfo Zoom;
	PropertyInfo Focus; // disuse
    PropertyInfo Pan;
    PropertyInfo Tilt; // disuse
    PropertyInfo Roll;
	PropertyInfo Power;
    PropertyInfo Mute;
    PropertyInfo Flip;
    PropertyInfo Mirror;
    PropertyInfo Menu;
    PropertyInfo Home;
    PropertyInfo Freeze;
    PropertyInfo BLC;
    PropertyInfo Gamma;
    PropertyInfo Contrast;

public:
	static void Initial(void);
	static void Release(void);
	static bool EnumUSBDevices(DeviceList& list);
	static BaseDevice* CreateDevice(DeviceType dt);
	static void DeleteDevice(BaseDevice* dev);
	/// <summary>
	/// 打开设备
	/// </summary>
	/// <param name="name"></param>
	/// <param name="id">仅使用串口方式需要传参，默认为1</param>
	/// <returns></returns>
	virtual bool OpenDevice(const char* name, int cid = 1) = 0;
	virtual void CloseDevice(void) = 0; 

    //releative position(ptzf)
	virtual bool StartMoveUp(int value) = 0; 
	virtual bool StopMoveUp(void) = 0;  
	virtual bool StartMoveDown(int value) = 0; 
	virtual bool StopMoveDown(void) = 0;     
	virtual bool StartMoveLeft(int value) = 0; 
	virtual bool StopMoveLeft(void) = 0;    
	virtual bool StartMoveRight(int value) = 0;
	virtual bool StopMoveRight(void) = 0; 


    virtual bool SetFocusManual(void) = 0;
    virtual bool SetFocusAuto(void) = 0;
    virtual bool SetFocusPush(void) = 0;
    virtual bool StartFocusNear(int value) = 0;
    virtual bool StartFocusFar(int value) = 0;
    virtual bool StopFocus(void) = 0;

    virtual bool StartZoomTele(int value) = 0;
    virtual bool StartZoomWide(int value) = 0;
    virtual bool StopZoom(void) = 0;

   //absolute position(ptzf)
	virtual bool GetZoom(long* value) = 0; 
    virtual bool GetFocus(long* value) = 0;
    virtual bool SetZoom0()= 0;
    virtual bool SetP0()= 0;
    virtual bool SetT0()= 0;

  //power
	virtual bool OpenPower(void) = 0;
	virtual bool ClosePower(void) = 0;
  //mute
	virtual bool OpenMute(void) = 0;
	virtual bool CloseMute(void) = 0;
 //flip
	virtual bool OpenFlip(void) = 0;
	virtual bool CloseFlip(void) = 0;
 //mirror
	virtual bool OpenMirror(void) = 0;
	virtual bool CloseMirror(void) = 0;
  //menu
	virtual bool OpenMenu(void) = 0;
	virtual bool CloseMenu(void) = 0;
  //set home position
	virtual bool HomePosition(void) = 0;
  //freeze
	virtual bool OpenFreeze(void) = 0;
	virtual bool CloseFreeze(void) = 0;
  //AI
    virtual bool OpenAI(void) = 0;
    virtual bool CloseAI(void) = 0;
  //set default value
    virtual bool SetDefaultValues(void) = 0;
  //push
    virtual bool PushWB(void) = 0;
    virtual bool PushMF(void) = 0;
 // blc
	virtual bool OpenBLC(void) = 0;
	virtual bool CloseBLC(void) = 0;
//preset
	virtual bool ClearPreset(unsigned char presetno) = 0;
	virtual bool SetPreset(unsigned char presetno) = 0;
	virtual bool CallPreset(unsigned char presetno) = 0;
//absolute
	virtual bool GetBrightness(long* value) = 0; 
    virtual bool SetBrightness(int value) = 0;

    virtual bool GetHue(long* value) = 0;
    virtual bool SetHue(int value) = 0;

    virtual bool GetBLC(long* value) = 0;
    virtual bool SetBLC(int value) = 0;

    virtual bool GetGamma(long* value) = 0;
    virtual bool SetGamma(int value) = 0;

    virtual bool GetContrast(long* value) = 0;
    virtual bool SetContrast(int value) = 0;


    virtual bool GetSaturation(long* value) = 0;
    virtual bool SetSaturation(int value) = 0;

	virtual bool GetSharpness(long* value) = 0; 
    virtual bool SetSharpness(int value) = 0;

    virtual bool GetWhiteBalance(long* value) = 0;
    virtual bool SetWhiteBalance(int value) = 0;

    virtual bool SetWhiteBalanceAuto(int value) = 0;

    virtual bool GetGain(long* value) = 0;
	virtual bool SetGain(int value) = 0;


    virtual bool GetFlicker(long* value) = 0;
    virtual bool SetFlicker(int value) = 0;

    //get max,min,default,current value
    virtual bool GetPropertyValues(void) = 0;
	virtual char* GetDeviceInfo(void) = 0;

	virtual bool GetRGain(long* value) = 0; 
	virtual bool GetBGain(long* value) = 0; 
	virtual bool GetAE(long* value) = 0; 
	virtual bool GetShutter(long* value) = 0; 
	virtual bool GetIris(long* value) = 0; 
    virtual bool GetAEBright(long* value) = 0;
	virtual bool GetWDR(long* value) = 0; 
	virtual bool GetWDRLevel(long* value) = 0; 


	virtual bool SetRGain(int value) = 0; 
	virtual bool SetBGain(int value) = 0; 
	virtual bool SetAE(int value) = 0; 
	virtual bool SetShutter(int value) = 0; 
	virtual bool SetIris(int value) = 0; 
    virtual bool SetAEBright(int value) = 0;
	virtual bool SetWDR(int value) = 0; 
	virtual bool SetWDRLevel(int value) = 0; 

    virtual bool SetIRON(void)= 0;
    virtual bool SetIROFF(void)= 0;
    virtual bool SetIR_DAY_MODE(void)= 0;
    virtual bool SetIR_NIGHT_MODE(void)= 0;
    virtual bool Set_ptz_reset(void)=0;

    virtual bool SetPan(long value)=0;
    virtual bool SetTilt(long value)=0;
    virtual bool GetPan(long* value)=0;
    virtual bool GetTilt(long* value)=0;
    virtual bool GetRoll(long* value)=0;
};

#endif
