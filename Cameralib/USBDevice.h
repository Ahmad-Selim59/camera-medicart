#ifndef _USB_DEVICE_H
#define _USB_DEVICE_H

#include <string>
#include <tchar.h>
#include <Dshow.h>
#include <Ks.h>
#include <KsMedia.h>
#include <Vidcap.h>
#include <dmksctrl.h>
#include <Ksmedia.h>
#include "CameraCtrl.h"

class USBDevice : public BaseDevice {
private:
	char szDevInfo[1024];
	IBaseFilter* gVCBaseFilter;
	IKsControl* m_pKsControl;
	IKsPropertySet* m_pKsPropertySet;
	IAMCameraControl* m_pKsPropertyCameraSet;
	IAMVideoProcAmp* m_pKsPropertyVideoSet;
public:
	static bool EnumDevices(DeviceList& list);

	virtual bool OpenDevice(const char* name, int id = 1);
	virtual void CloseDevice(void);
	virtual bool StartMoveUp(int value); 
	virtual bool StopMoveUp(void); 
	virtual bool StartMoveDown(int value); 
	virtual bool StopMoveDown(void); 
	virtual bool StartMoveLeft(int value); 
	virtual bool StopMoveLeft(void); 
	virtual bool StartMoveRight(int value); 
	virtual bool StopMoveRight(void); 


	virtual bool SetFocusManual(void);
	virtual bool SetFocusAuto(void);
	virtual bool SetFocusPush(void);
	virtual bool StartFocusNear(int value);
	virtual bool StartFocusFar(int value);
	virtual bool StopFocus(void);

	virtual bool StartZoomTele(int value);
	virtual bool StartZoomWide(int value);
	virtual bool StopZoom(void);

	virtual bool GetZoom(long* value);
	virtual bool GetFocus(long* value);
    virtual bool SetZoom0();
    virtual bool SetP0();
    virtual bool SetT0();


    virtual bool OpenPower(void);
    virtual bool ClosePower(void) ;


    virtual bool OpenMute(void) ;
    virtual bool CloseMute(void) ;


    virtual bool OpenFlip(void) ;
    virtual bool CloseFlip(void);


    virtual bool OpenMirror(void);
    virtual bool CloseMirror(void) ;


    virtual bool OpenMenu(void) ;
    virtual bool CloseMenu(void);



    virtual bool HomePosition(void);

    virtual bool OpenFreeze(void);
    virtual bool CloseFreeze(void);
	
	virtual bool SetDefaultValues(void);


    //AI
      virtual bool OpenAI(void);
      virtual bool CloseAI(void);
    //push
      virtual bool PushWB(void);
      virtual bool PushMF(void);
    // ·ÏÆú
    virtual bool OpenBLC(void);
    virtual bool CloseBLC(void);



	virtual bool ClearPreset(unsigned char presetno);
	virtual bool SetPreset(unsigned char presetno);
	virtual bool CallPreset(unsigned char presetno);
	
	
	virtual bool GetBrightness(long* value); 
	virtual bool SetBrightness(int value); 

    virtual bool GetHue(long* value);
    virtual bool SetHue(int value);
	
	virtual bool GetSaturation(long* value); 
	virtual bool SetSaturation(int value); 
	
	virtual bool GetSharpness(long* value); 
	virtual bool SetSharpness(int value); 
	
    virtual bool GetWhiteBalance(long* value);
	virtual bool SetWhiteBalance(int value);

    virtual bool SetWhiteBalanceAuto(int value);

    virtual bool GetBLC(long* value);
    virtual bool SetBLC(int value);

    virtual bool GetGamma(long* value);
    virtual bool SetGamma(int value);

    virtual bool GetContrast(long* value);
    virtual bool SetContrast(int value);

		
	virtual bool GetGain(long* value);
	virtual bool SetGain(int value);
	
	virtual bool GetFlicker(long* value);
	virtual bool SetFlicker(int value);
	
	virtual bool GetPropertyValues(void);
	virtual char* GetDeviceInfo(void);

	virtual bool GetRGain(long* value);
	virtual bool GetBGain(long* value);
	virtual bool GetAE(long* value);
	virtual bool GetShutter(long* value);
	virtual bool GetIris(long* value);
	virtual bool GetAEBright(long* value);
	virtual bool GetWDR(long* value);
	virtual bool GetWDRLevel(long* value);


	virtual bool SetRGain(int value);
	virtual bool SetBGain(int value);
	virtual bool SetAE(int value);
	virtual bool SetShutter(int value);
	virtual bool SetIris(int value);
	virtual bool SetAEBright(int value);
	virtual bool SetWDR(int value);
	virtual bool SetWDRLevel(int value);

    virtual bool SetIRON(void);
    virtual bool SetIROFF(void);
    virtual bool SetIR_DAY_MODE(void);
    virtual bool SetIR_NIGHT_MODE(void);

    virtual bool Set_ptz_reset(void);

    virtual bool SetPan(long value);
    virtual bool SetTilt(long value);
    virtual bool GetPan(long* value);
    virtual bool GetTilt(long* value);
    virtual bool GetRoll(long* value);


};

#endif
