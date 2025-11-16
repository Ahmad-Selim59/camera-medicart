#include "USBDevice.h"
#include <Setupapi.h>
#include <QDebug>

static std::string ConvertBSTRToString(BSTR pSrc)
{
    std::string sret;
    if (pSrc) {
        DWORD cb, cwch = ::SysStringLen(pSrc);
        char* szOut = NULL;
        if (cb = ::WideCharToMultiByte(CP_ACP, 0, pSrc, cwch + 1, NULL, 0, 0, 0)) {
            szOut = new char[cb];
            if (szOut) {
                szOut[cb - 1] = '\0';
                if (!::WideCharToMultiByte(CP_ACP, 0, pSrc, cwch + 1, szOut, cb, 0, 0)) {
                    delete[] szOut;
                    szOut = NULL;
                }
            }
        }
        if (szOut != NULL) {
            sret = szOut;
            delete[] szOut;
        }
    }
    return sret;
}

bool USBDevice::EnumDevices(DeviceList& list)
{
    ICreateDevEnum *pCreateDevEnum;
    IEnumMoniker   *pEnumMoniker;
    IMoniker       *pMoniker;
    ULONG          cFetched;

    HRESULT hr = CoCreateInstance(
        CLSID_SystemDeviceEnum,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_ICreateDevEnum,
        (void**)&pCreateDevEnum
        );
    if (hr != NOERROR)
        return FALSE;
    hr = pCreateDevEnum->CreateClassEnumerator(
        CLSID_VideoInputDeviceCategory,
        &pEnumMoniker, 0
        );
    pCreateDevEnum->Release();
    if (hr != NOERROR)
        return FALSE;
    pEnumMoniker->Reset();
    list.clear();

    int index = 0;
    while ((hr = pEnumMoniker->Next(1, &pMoniker, &cFetched)) == S_OK) {
        IPropertyBag *pPropertyBag;
        hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropertyBag);
        if (SUCCEEDED(hr)) {
            DeviceInfo devInfo;
            VARIANT var1;
            VARIANT var2;
            VariantInit(&var1);
            VariantInit(&var2);
            hr = pPropertyBag->Read(L"FriendlyName", &var1, 0);
            devInfo.Name = ConvertBSTRToString (var1.bstrVal);
            std::string s1 = devInfo.Name;
            hr = pPropertyBag->Read(L"DevicePath", &var2, 0);
            devInfo.Path = ConvertBSTRToString (var2.bstrVal);
            std::string s4 = devInfo.Path;
            std::string s5 = "pid_8888";
            std::string s6 = "pid_7588";
            std::string s7 = "vid_0000&pid_00f9";//avpiss
            std::string s8 = "pid_9999";

            if ( (s4.find(s5) < s4.length()) | (s4.find(s6) < s4.length()) |(s4.find(s8) < s4.length()) | (s4.find(s7) < s4.length())) {
                devInfo.DeviceId = index;
                list.push_back(devInfo);
                index++;
            }
            VariantClear(&var1);
            VariantClear(&var2);
            pPropertyBag->Release();
        }
        pMoniker->Release();
    }
    pEnumMoniker->Release();
    return TRUE;
}

bool GetVideoDevice(int id, IBaseFilter** pVCap, char* info)
{
    ICreateDevEnum* pCreateDevEnum;
    IEnumMoniker* pEnumMoniker;
    IMoniker* pMoniker;
    ULONG cFetched;

    HRESULT hr = CoCreateInstance(
        CLSID_SystemDeviceEnum,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_ICreateDevEnum,
        (void**)&pCreateDevEnum
    );
    if (hr != NOERROR)
        return FALSE;
    hr = pCreateDevEnum->CreateClassEnumerator(
        CLSID_VideoInputDeviceCategory,
        &pEnumMoniker, 0
    );
    pCreateDevEnum->Release();
    if (hr != NOERROR)
        return FALSE;
    pEnumMoniker->Reset();
    int index = 0;
    while ((hr = pEnumMoniker->Next(1, &pMoniker, &cFetched)) == S_OK) {
        IPropertyBag* pPropertyBag;
        hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pPropertyBag);
        if (SUCCEEDED(hr)) {
            VARIANT var1;
            VARIANT var2;
            VariantInit(&var1);
            VariantInit(&var2);
            hr = pPropertyBag->Read(L"FriendlyName", &var1, 0);
            std::string s1 = ConvertBSTRToString(var1.bstrVal);
            hr = pPropertyBag->Read(L"DevicePath", &var2, 0);
            std::string s4 = ConvertBSTRToString(var2.bstrVal);
            std::string s5 = "pid_8888";
            std::string s6 = "pid_7588";
            std::string s7 = "vid_0000&pid_00f9";//avpiss
            std::string s8 = "pid_9999";

            if ( (s4.find(s5) < s4.length()) | (s4.find(s6) < s4.length()) |(s4.find(s8) < s4.length()) | (s4.find(s7) < s4.length())) {
                if (index == id) {
                    VariantClear(&var1);
                    VariantClear(&var2);
                    pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)pVCap);
                    pPropertyBag->Release();
                    pMoniker->Release();
                    pEnumMoniker->Release();
                    strcpy(info, s1.c_str());
                    return TRUE;
                }
                index++;
            }
            VariantClear(&var1);
            VariantClear(&var2);
            pPropertyBag->Release();
        }
        pMoniker->Release();
    }
    pEnumMoniker->Release();
    return FALSE;
}


bool USBDevice::OpenDevice(const char* name, int cid)
{
    CloseDevice();
    int id = atoi(name);
    if (GetVideoDevice(id, &gVCBaseFilter, szDevInfo) == FALSE) {
        return FALSE;
    }
    if (gVCBaseFilter) {
        m_pKsPropertyVideoSet = NULL;
        gVCBaseFilter->QueryInterface(IID_IAMVideoProcAmp, (void **)&m_pKsPropertyVideoSet );
        m_pKsControl = NULL;
        gVCBaseFilter->QueryInterface(IID_IKsControl, (void **)&m_pKsControl);
        m_pKsPropertySet = NULL;
        gVCBaseFilter->QueryInterface(IID_IKsPropertySet, (void **)&m_pKsPropertySet);
        m_pKsPropertyCameraSet = NULL;
        gVCBaseFilter->QueryInterface(IID_IAMCameraControl, (void **)&m_pKsPropertyCameraSet );
    }
    if (!m_pKsPropertySet)
        return FALSE;
    if (!m_pKsPropertyCameraSet)
        return FALSE;
    if (!m_pKsPropertyVideoSet)
        return FALSE;
    if (!m_pKsControl)
        return FALSE;
    return TRUE;
}

void USBDevice::CloseDevice(void)
{
    if (m_pKsPropertySet) {
        m_pKsPropertySet->Release();
        m_pKsPropertySet = NULL;
    }
    if (m_pKsControl) {
        m_pKsControl->Release();
        m_pKsControl = NULL;
    }
    if (m_pKsPropertyCameraSet) {
        m_pKsPropertyCameraSet->Release();
        m_pKsPropertyCameraSet = NULL;
    }
    if (m_pKsPropertyVideoSet) {
        m_pKsPropertyVideoSet->Release();
        m_pKsPropertyVideoSet = NULL;
    }
    if (gVCBaseFilter) {
        gVCBaseFilter->Release();
        gVCBaseFilter = NULL;
    }
}



bool USBDevice::StartMoveUp(int value)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = value;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_TILT_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StopMoveUp(void)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 0; //stop motor;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_TILT_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StartMoveDown(int value)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = -value;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_TILT_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StopMoveDown(void)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 0;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_TILT_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StartMoveLeft(int value)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = -value;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_PAN_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StopMoveLeft(void)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 0;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_PAN_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StartMoveRight(int value)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = value;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_PAN_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StopMoveRight(void)
{
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 0;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_PAN_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetFocusManual(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 8;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetFocusAuto(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 7;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetIRON(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 14;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetIROFF(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 15;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetIR_DAY_MODE(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 16;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}
bool USBDevice::SetIR_NIGHT_MODE(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 17;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}
bool USBDevice::Set_ptz_reset(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 18;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetFocusPush(void) {
    return false;
}

bool USBDevice::StartFocusNear(int value) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 1;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_FOCUS_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StartFocusFar(int value) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = -1;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_FOCUS_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StopFocus(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 0;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_FOCUS_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StartZoomTele(int value) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 1;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ZOOM_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StartZoomWide(int value) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = -1;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ZOOM_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::StopZoom(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 0;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ZOOM_RELATIVE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetZoom(long* value) {
    long flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertyCameraSet->Get(KSPROPERTY_CAMERACONTROL_ZOOM, &Zoom.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Zoom.Current;
    return TRUE;
}

bool USBDevice::SetZoom0(){

        KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
        KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
        KsPropCameraControl.Value = 0;

       HRESULT  hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
            KSPROPERTY_CAMERACONTROL_ZOOM,
            &KsPropCameraControl,
            sizeof(KsPropCameraControl),
            &KsPropCameraControl,
            sizeof(KSPROPERTY_CAMERACONTROL_S));
        if (FAILED(hr))
        {
            return FALSE;
        }
        return TRUE;
}
bool USBDevice::SetP0(){

    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = 0;

   HRESULT  hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_PAN,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
    {
        return FALSE;
    }
    return TRUE;

}
bool USBDevice::SetT0(){

    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = 0;

   HRESULT  hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_TILT,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
    {
        return FALSE;
    }
    return TRUE;

}

bool USBDevice::SetPan(long value){

    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = value;

   HRESULT  hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_PAN,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
    {
        return FALSE;
    }
    return TRUE;

}
bool USBDevice::SetTilt(long value){

    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = value;

   HRESULT  hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_TILT,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
    {
        return FALSE;
    }
    return TRUE;

}
bool USBDevice::GetPan(long* value) {
    long flags = CameraControl_Flags_Manual;
    HRESULT hr = m_pKsPropertyCameraSet->Get(CameraControl_Pan, &Pan.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Pan.Current;
    return TRUE;
}
bool USBDevice::GetTilt(long* value) {
    long flags = CameraControl_Flags_Manual;
    HRESULT hr = m_pKsPropertyCameraSet->Get(CameraControl_Tilt, &Tilt.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Tilt.Current;
    return TRUE;
}

bool USBDevice::GetRoll(long* value) {
    long flags = CameraControl_Flags_Manual;
    HRESULT hr = m_pKsPropertyCameraSet->Get(CameraControl_Roll, &Roll.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Roll.Current;
    return TRUE;
}

bool USBDevice::GetFocus(long* value) {
    long flags = CameraControl_Flags_Manual;
    HRESULT hr = m_pKsPropertyCameraSet->Get(CameraControl_Focus, &Focus.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Focus.Current;
    return TRUE;
}

bool USBDevice::OpenPower(void) {
    return false;
}

bool USBDevice::ClosePower(void) {
    return false;
}

bool USBDevice::OpenMute(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 6;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseMute(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 5;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}
bool USBDevice::OpenFlip(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 3;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseFlip(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 4;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}



bool USBDevice::OpenMirror(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 1;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseMirror(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 2;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


bool USBDevice::OpenMenu(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 10;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseMenu(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 11;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::HomePosition(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 9;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::OpenFreeze(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 18;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseFreeze(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 19;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::OpenAI(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 16;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseAI(void) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = 17;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetDefaultValues(void)
{
    long flags = 0;
    HRESULT hr = S_OK;
    hr = m_pKsPropertyCameraSet->Set(KSPROPERTY_CAMERACONTROL_ZOOM, Zoom.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_BRIGHTNESS, Brightness.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_CONTRAST, Contrast.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_GAMMA, Gamma.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION, BLC.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_GAIN, Gain.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_SATURATION, Saturation.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_SHARPNESS, Sharpness.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_WHITEBALANCE, WhiteBalance.Default, flags);
    Sleep(100);
    hr = m_pKsPropertyVideoSet->Set(KSPROPERTY_VIDEOPROCAMP_POWERLINE_FREQUENCY, Flicker.Default, flags);
    Sleep(100);
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::PushWB(void) {
    return FALSE;
}
bool USBDevice::PushMF(void) {
    return FALSE;
}

bool USBDevice::OpenBLC(void) {
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = 1;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CloseBLC(void) {
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = 0;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}



bool USBDevice::ClearPreset(unsigned char presetno)
{
    //Method 2, by m_pKsPropertySet;
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = presetno+60;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetPreset(unsigned char presetno)
{
    //Method 2, by m_pKsPropertySet;
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = presetno+20;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::CallPreset(unsigned char presetno)
{
    //Method 2, by m_pKsPropertySet;
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    KsPropCameraControl.Value = presetno +100;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_ROLL,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetBrightness(long* value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_BRIGHTNESS,  &Brightness.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Brightness.Current;
    return TRUE;
}
bool USBDevice::SetBrightness(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_BRIGHTNESS,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetGamma(long *value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_GAMMA,  &Gamma.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Gamma.Current;
    return TRUE;
}
bool USBDevice::SetGamma(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_GAMMA,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


bool USBDevice::GetContrast(long* value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_CONTRAST,  &Contrast.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Contrast.Current;
    return TRUE;
}
bool USBDevice::SetContrast(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_CONTRAST,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


bool USBDevice::GetBLC(long* value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION,  &BLC.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = BLC.Current;
    return TRUE;
}
bool USBDevice::SetBLC(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


bool USBDevice::GetSaturation(long* value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_SATURATION,  &Saturation.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Saturation.Current;
    return TRUE;
}
bool USBDevice::SetSaturation(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_SATURATION,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetSharpness(long* value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_SHARPNESS,  &Sharpness.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Sharpness.Current;
    return TRUE;
}
bool USBDevice::SetSharpness(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_SHARPNESS,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetHue(long *value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_HUE,  &Hue.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Hue.Current;
    return TRUE;
}
bool USBDevice::SetHue(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_HUE,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


bool USBDevice::GetWhiteBalance(long* value)
{
    long flags = VideoProcAmp_Flags_Manual;
    HRESULT hr = m_pKsPropertyVideoSet->Get(VideoProcAmp_WhiteBalance,  &WhiteBalance.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = WhiteBalance.Current;
    return TRUE;
}
bool  USBDevice::SetWhiteBalance(int value) {
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = value == 0 ? KSPROPERTY_VIDEOPROCAMP_FLAGS_AUTO : KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL; // ?§Ø???????????
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_WHITEBALANCE,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


bool  USBDevice::SetWhiteBalanceAuto(int value) {
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Flags = value == 1 ? KSPROPERTY_VIDEOPROCAMP_FLAGS_AUTO : KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL; // ?§Ø???????????
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_WHITEBALANCE,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetGain(long* value)
{
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_GAIN,  &Gain.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Gain.Current;
    return TRUE;
}


bool USBDevice::SetGain(int value)
{
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_GAIN,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::GetFlicker(long* value) {
    long flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertyVideoSet->Get(KSPROPERTY_VIDEOPROCAMP_POWERLINE_FREQUENCY, &Flicker.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Flicker.Current;
    return TRUE;
}

bool USBDevice::SetFlicker(int value) {
    KSPROPERTY_VIDEOPROCAMP_S KsPropVideoProCamp;
    KsPropVideoProCamp.Value = value;
    KsPropVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_POWERLINE_FREQUENCY,
        &KsPropVideoProCamp,
        sizeof(KsPropVideoProCamp),
        &KsPropVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}



bool USBDevice::GetPropertyValues(void)
{
    long flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL, Step = 1;
    HRESULT hr = S_OK;
    // ???????????§³??????
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_WHITEBALANCE, &WhiteBalance.Min, &WhiteBalance.Max, &WhiteBalance.Step, &WhiteBalance.Default, &flags);
    hr = m_pKsPropertyCameraSet->GetRange(KSPROPERTY_CAMERACONTROL_EXPOSURE, &AE.Min, &AE.Max, &AE.Step, &AE.Default, &flags);
    hr = m_pKsPropertyCameraSet->GetRange(KSPROPERTY_CAMERACONTROL_IRIS, &Iris.Min, &Iris.Max, &Iris.Step, &Iris.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_GAIN, &Gain.Min, &Gain.Max, &Gain.Step, &Gain.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_BRIGHTNESS, &Brightness.Min, &Brightness.Max, &Brightness.Step, &Brightness.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_CONTRAST, &Contrast.Min, &Contrast.Max, &Contrast.Step, &Contrast.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_GAMMA, &Gamma.Min, &Gamma.Max, &Gamma.Step, &Gamma.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_BACKLIGHT_COMPENSATION, &BLC.Min, &BLC.Max, &BLC.Step, &BLC.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_SATURATION, &Saturation.Min, &Saturation.Max, &Saturation.Step, &Saturation.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_SHARPNESS, &Sharpness.Min, &Sharpness.Max, &Sharpness.Step, &Sharpness.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_HUE, &Hue.Min, &Hue.Max, &Hue.Step, &Hue.Default, &flags);
    hr = m_pKsPropertyVideoSet->GetRange(KSPROPERTY_VIDEOPROCAMP_POWERLINE_FREQUENCY, &Flicker.Min, &Flicker.Max, &Flicker.Step, &Flicker.Default, &flags);
    // ???????
    WhiteBalance.Valid = GetWhiteBalance(&WhiteBalance.Current) ? 1 : 0;
    AE.Valid = GetAE(&AE.Current) ? 1 : 0;
    Iris.Valid = GetIris(&Iris.Current) ? 1 : 0;
    Gain.Valid = GetGain(&Gain.Current) ? 1 : 0;
    Brightness.Valid = GetBrightness(&Brightness.Current) ? 1 : 0;
    Saturation.Valid = GetSaturation(&Saturation.Current) ? 1 : 0;
    Sharpness.Valid = GetSharpness(&Sharpness.Current) ? 1 : 0;
    Hue.Valid = GetHue(&Hue.Current) ? 1 : 0;
    Flicker.Valid = GetFlicker(&Flicker.Current) ? 1 : 0;
    Contrast.Valid = GetContrast(&Contrast.Current) ? 1 : 0;
    Gamma.Valid = GetGamma(&Gamma.Current) ? 1 : 0;
    BLC.Valid = GetBLC(&BLC.Current) ? 1 : 0;
    // ???????§¹????
    RGain.Valid = 0;
    BGain.Valid = 0;
    AEBright.Valid = 0;
    Shutter.Valid = 0;
    WDR.Valid = 0;
    WDRLevel.Valid = 0;

    return TRUE;
}



char* USBDevice::GetDeviceInfo(void)
{
    return szDevInfo;
}

bool USBDevice::GetRGain(long* value) {
    return false;
}

bool USBDevice::GetBGain(long* value) {
    return false;
}

bool USBDevice::GetAE(long* value) {
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertyCameraSet->Get(KSPROPERTY_CAMERACONTROL_EXPOSURE, &AE.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = AE.Current;
    return TRUE;
}

bool USBDevice::GetShutter(long* value) {
    return false;
}

bool USBDevice::GetIris(long* value) {
    long flags = KSPROPERTY_CAMERACONTROL_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertyCameraSet->Get(KSPROPERTY_CAMERACONTROL_IRIS, &Iris.Current, &flags);
    if (FAILED(hr))
        return FALSE;
    *value = Iris.Current;
    return TRUE;
}

bool USBDevice::GetAEBright(long* value) {
    return false;
}

bool USBDevice::GetWDR(long* value) {
    return false;
}

bool USBDevice::GetWDRLevel(long* value) {
    return false;
}





bool USBDevice::SetRGain(int value) {
    KSPROPERTY_VIDEOPROCAMP_NODE_S2 KsProVideoProCamp;
    KsProVideoProCamp.Value1 = value;
    KsProVideoProCamp.Value2 = BGain.Current;
    KsProVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_WHITEBALANCE_COMPONENT,
        &KsProVideoProCamp,
        sizeof(KsProVideoProCamp),
        &KsProVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_NODE_S2));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetBGain(int value) {
    KSPROPERTY_VIDEOPROCAMP_NODE_S2 KsProVideoProCamp;
    KsProVideoProCamp.Value1 = RGain.Current;
    KsProVideoProCamp.Value2 = value;
    KsProVideoProCamp.Flags = KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_VIDEOPROCAMP,
        KSPROPERTY_VIDEOPROCAMP_WHITEBALANCE_COMPONENT,
        &KsProVideoProCamp,
        sizeof(KsProVideoProCamp),
        &KsProVideoProCamp,
        sizeof(KSPROPERTY_VIDEOPROCAMP_NODE_S2));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetAE(int value) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = value;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_MANUAL;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_EXPOSURE,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetShutter(int value) {
    return false;
}

bool USBDevice::SetIris(int value) {
    KSPROPERTY_CAMERACONTROL_S KsPropCameraControl;
    KsPropCameraControl.Value = value;
    KsPropCameraControl.Flags = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE;
    HRESULT hr = m_pKsPropertySet->Set(PROPSETID_VIDCAP_CAMERACONTROL,
        KSPROPERTY_CAMERACONTROL_IRIS,
        &KsPropCameraControl,
        sizeof(KsPropCameraControl),
        &KsPropCameraControl,
        sizeof(KSPROPERTY_CAMERACONTROL_S));
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}

bool USBDevice::SetAEBright(int value) {
    return false;
}



bool USBDevice::SetWDR(int value) {
    return false;
}

bool USBDevice::SetWDRLevel(int value) {
    return false;
}




