#include "mainwindow.h"
#include "ui_mainwindow.h"

int cur_blc,min_blc,max_blc,default_blc,step_blc;
int cur_gamma,min_gamma,max_gamma,default_gamma,step_gamma;
int cur_contrast,min_contrast,max_contrast,default_contrast,step_contrast;
int cur_saturation,min_saturation,max_saturation,default_saturation,step_saturation;
int cur_brightness,min_brightness,max_brightness,default_brightness,step_brightness;
int cur_hue,min_hue,max_hue,default_hue,step_hue;
int cur_sharpness,min_sharpness,max_sharpness,default_sharpness,step_sharpness;
int cur_wb,min_wb,max_wb,default_wb,step_wb;
int cur_fliker,min_fliker,max_fliker,default_fliker;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshDPI();
    InitValue();
    InitWindows();
    InitFindChild();
    InitConnect();
    InitUSBGuid();
}

MainWindow::~MainWindow(){delete ui;}

//启动时缩放一次api
void MainWindow::refreshDPI()
{
    QList<QScreen*> screens = QApplication::screens();
    QScreen* screen = screens[0];
    qreal dpi = screen->logicalDotsPerInch();
    //计算dpi对应的缩放比例
    double objectRate = dpi/96.0;   //缩放比例
    changeObjectSize(*this, objectRate);
    resize(width()*objectRate,height()*objectRate);
    connect(screen,SIGNAL(logicalDotsPerInchChanged(qreal)),this,SLOT(onLogicalDotsPerInchChanged(qreal)));
    //缩放完成后获取左侧窗口的当前长宽
    //获取缩放后左侧窗口的大小
    lwidth = ui->Win_Left->width();
    lheight = ui->Win_Left->height();
    fwidth = ui->frame->width();
    fheight = ui->frame->height();
}

void MainWindow::onLogicalDotsPerInchChanged(qreal dpi)
{
    double objectRate = dpi/96.0;
    changeObjectSize(*this, objectRate);
    resize(width()*objectRate,height()*objectRate);
    //重新获取缩放后左侧窗口的大小
    lwidth = ui->Win_Left->width();
    lheight = ui->Win_Left->height();

    fwidth = ui->frame->width();
    fheight = ui->frame->height();

}

void MainWindow::changeObjectSize(const QObject &o, double objectRate)
{

    for (int i=0; i<o.children().size(); ++i) {
        QWidget *pWidget = qobject_cast<QWidget *>(o.children().at(i));
        if (pWidget != nullptr) {
            pWidget->setGeometry(pWidget->x()*objectRate,pWidget->y()*objectRate,
                                 pWidget->width()*objectRate, pWidget->height()*objectRate);
            changeObjectSize(*(o.children().at(i)),objectRate);
        }
    }
}

void MainWindow::InitValue()
{
    hide_flag = true;
    R_Hide = false;
    Show_flag = false;
    Tim = new QTimer(this);
    USB_Mode 		= true;
    InitRun         = false;
    TopFlag         = true;
    USB_Dev = BaseDevice::CreateDevice(DeviceType::USB_Device);
}

void MainWindow::InitWindows()
{
    //设置窗口无边框,背景透明，初始位置，窗口置顶
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    /*界面初始化------简洁功能窗口*/
    ui->frame->setGeometry(268,0,0,417);
    ui->Win_Left->setGeometry(268,0,0,417);
    ui->Label_Hide_L->hide();
    ui->Label_Hide_R->hide();
    QApplication::setEffectEnabled(Qt::UI_AnimateCombo, false);
}

void MainWindow::InitFindChild()
{
    /*左侧窗口*/


    slider_brightness   = ui->Win_Left->findChild<QSlider *>("Slider_Brightness");
    v_brightness   = ui->Win_Left->findChild<QLineEdit *>("v_brightness");
    slider_contrast     = ui->Win_Left->findChild<QSlider *>("Slider_Contrast");
    v_contrast     = ui->Win_Left->findChild<QLineEdit *>("v_contrast");
    slider_hue          = ui->Win_Left->findChild<QSlider *>("Slider_Hue");
    v_hue          = ui->Win_Left->findChild<QLineEdit *>("v_hue");
    slider_saturation   = ui->Win_Left->findChild<QSlider *>("Slider_Saturation");
    v_saturation   = ui->Win_Left->findChild<QLineEdit *>("v_saturation");
    slider_sharpness    = ui->Win_Left->findChild<QSlider *>("Slider_Sharpness");
    v_sharpness    = ui->Win_Left->findChild<QLineEdit *>("v_sharpness");
    slider_gamma        = ui->Win_Left->findChild<QSlider *>("Slider_Gamma");
    v_gamma        = ui->Win_Left->findChild<QLineEdit *>("v_gamma");
    slider_blc          = ui->Win_Left->findChild<QSlider *>("Slider_BLC");
    v_blc          = ui->Win_Left->findChild<QLineEdit *>("v_blc");
    slider_wb           = ui->Win_Left->findChild<QSlider *>("Slider_WB");
    v_wb           = ui->Win_Left->findChild<QLineEdit *>("v_wb");


    cb_wb          =ui->Win_Left->findChild<QCheckBox *>("cb_wb");
    ComboBox_Flicker    = ui->Win_Left->findChild<QComboBox *>("ComboBox_Flicker");

    /*右侧窗口*/
    Box_Camera_USB     = ui->Win_Right->findChild<QComboBox *>("Box_Camera_USB");
    Slider_Fucus        = ui->Win_Right->findChild<QSlider *>("Slider_Fucus");
    Slider_Zoom         = ui->Win_Right->findChild<QSlider *>("Slider_Zoom");
    BT_AF               = ui->Win_Right->findChild<QPushButton *>("BT_AF");


    v_set_pan_data =ui->Win_Right->findChild<QLineEdit *>("set_pan_data");
    v_set_tilt_data =ui->Win_Right->findChild<QLineEdit *>("set_tilt_data");
    v_get_pan_data =ui->Win_Right->findChild<QLineEdit *>("get_pan_data");
    v_get_tilt_data =ui->Win_Right->findChild<QLineEdit *>("get_tilt_data");
    v_get_roll_data =ui->Win_Right->findChild<QLineEdit *>("get_roll_data");

}

void MainWindow::InitConnect()
{
    /*左侧窗口*/
    connect(ui->Win_Left,SIGNAL(BT_Pressed(int)),this,SLOT(LWin_BT_Pressed(int)));
    connect(ComboBox_Flicker,SIGNAL(currentTextChanged(QString)),this,SLOT(FlickerChange()));

    connect(slider_brightness,SIGNAL(sliderMoved(int)),this,SLOT(Brightness_Change(int)));
    connect(slider_contrast,SIGNAL(sliderMoved(int)),this,SLOT(Contrast_Change(int)));
    connect(slider_hue,SIGNAL(sliderMoved(int)),this,SLOT(Hue_Change(int)));
    connect(slider_saturation,SIGNAL(sliderMoved(int)),this,SLOT(Saturation_Change(int)));
    connect(slider_sharpness,SIGNAL(sliderMoved(int)),this,SLOT(Sharpness_Change(int)));
    connect(slider_gamma,SIGNAL(sliderMoved(int)),this,SLOT(Gamma_Change(int)));
    connect(slider_blc,SIGNAL(sliderMoved(int)),this,SLOT(BLC_Change(int)));
    connect(slider_wb,SIGNAL(sliderMoved(int)),this,SLOT(WB_Change(int)));

    /*右侧窗口*/
    connect(ui->Win_Right,SIGNAL(BT_Show(bool)),this,SLOT(Tool_Show(bool)));
    connect(ui->Win_Right,SIGNAL(keyNumchanged(int)),this,SLOT(MovePlace(int)));
    connect(ui->Win_Right,SIGNAL(Speed_Pan(int)),this,SLOT(SpeedX(int)));
    connect(ui->Win_Right,SIGNAL(Speed_Tilt(int)),this,SLOT(SpeedY(int)));
    connect(ui->Win_Right,SIGNAL(Speed_Tilt(int)),this,SLOT(SpeedY(int)));
    connect(ui->Win_Right,SIGNAL(BT_Pressed(int)),this,SLOT(RWin_BT_Pressed(int)));
    connect(ui->Win_Right,SIGNAL(IPCAMChange(int)),this,SLOT(IPCAMChange(int)));
    connect(Slider_Zoom,SIGNAL(valueChanged(int)),this,SLOT(ZoomChange()));
    connect(Slider_Zoom,SIGNAL(sliderReleased()),this,SLOT(ZoomStop()));
    connect(ui->Win_Right,SIGNAL(ChangePresetno(int)),this,SLOT(ChangePresetno(int)));

    connect(ui->Win_Right,SIGNAL(Setting_Press(int)),this,SLOT(Setting_Press(int)));


    /*设置窗口*/

    /*其他槽函数*/
   connect(Tim,SIGNAL(timeout()),this,SLOT(TimerInit()));
    Tim->start(500);
}
int maxcam;
void MainWindow::TimerInit()
{
    int i=0;
        if(Tim->isActive()){
            BaseDevice::Initial();
            if(BaseDevice::EnumUSBDevices(USB_List)){
                for (auto item : USB_List){
                    QString qstr2 = QString::fromStdString(item.Name);
                 //   qDebug()<<"line 176"<<qstr2;
                    Box_Camera_USB->addItem(QString::fromStdString(item.Name));
                    i=item.DeviceId+1;
                }
                maxcam = i;
                //虚拟摄像头
                if(maxcam==0)
                {
                    Warn_NoDev();
                    USB_Mode=0;
                }
                else
                {//发现摄像头
                    Setting_Press(0);

                }
            }
            else
            {//没有摄像头
                Warn_NoDev();
                USB_Mode=0;
                maxcam=0;
            }

        }
        Tim->stop();
}

void MainWindow::InitUSBGuid()
{
    static const GUID GUID_DEVINTERFACE_LIST[] =
    {
        { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },// GUID_DEVINTERFACE_USB_DEVICE
    };
    //注册插拔事件
    HDEVNOTIFY hDevNotify;
    DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
    ZeroMemory(&NotifacationFiler,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    for(int i=0;i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID);i++)
    {
        NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];//GetCurrentUSBGUID();
        hDevNotify = RegisterDeviceNotification(HANDLE(this->winId()),&NotifacationFiler,DEVICE_NOTIFY_WINDOW_HANDLE);
        if(!hDevNotify)
        {
            GetLastError();
          //  qDebug() << "注册失败" <<endl;
        }
    }

}

void MainWindow::DeviceChange()
{
    BaseDevice::Initial();
    Box_Camera_USB->clear();
    if(BaseDevice::EnumUSBDevices(USB_List)){
     //   qDebug()<<"Get USB_List success";
        for (auto item : USB_List){
          //  qDebug()<<"line 176"<<item.DeviceId;
            Box_Camera_USB->addItem(QString::fromStdString(item.Name));
        }
    }
    else
    {
        USB_Mode=0;
        Warn_NoDev();
    }
    ChangeTimer->stop();
}

/*设置窗口部分*/
void MainWindow::Setting_Press(int flag)
{
        USB_Dev->CloseDevice();
        USB_Mode = true;
        BaseDevice::Initial();
            char *DeviceId=NULL;
            QByteArray temp_2;
            int temp = Box_Camera_USB->currentIndex();
            QString temp_1 = QString::number(temp,10);
            temp_2 = temp_1.toLatin1();
            DeviceId = temp_2.data();
            if(DeviceId != NULL){
                if(USB_Dev->OpenDevice(DeviceId)){
                    USB_Dev->GetPropertyValues();
                    USB_Mode = true;


                    USB_Dev->CloseMenu();

                    cur_blc=USB_Dev->BLC.Current;
                    min_blc=USB_Dev->BLC.Min;
                    max_blc=USB_Dev->BLC.Max;
                    default_blc=USB_Dev->BLC.Default;
                    step_blc=0;//USB_Dev->BLC.Step;

                    //Gamma
                    cur_gamma=USB_Dev->Gamma.Current;
                    min_gamma=USB_Dev->Gamma.Min;
                    max_gamma=USB_Dev->Gamma.Max;
                    default_gamma=USB_Dev->Gamma.Default;
                    step_gamma=0;//USB_Dev->Gamma.Step;

                    //contrast
                    cur_contrast=USB_Dev->Contrast.Current;
                    min_contrast=USB_Dev->Contrast.Min;
                    max_contrast=USB_Dev->Contrast.Max;
                    default_contrast=USB_Dev->Contrast.Default;
                    step_contrast=0;//USB_Dev->Contrast.Step;

                    //saturation
                    cur_saturation=USB_Dev->Saturation.Current;
                    min_saturation=USB_Dev->Saturation.Min;
                    max_saturation=USB_Dev->Saturation.Max;
                    default_saturation=USB_Dev->Saturation.Default;
                    step_saturation=0;//USB_Dev->Saturation.Step;

                    //brightness
                    cur_brightness=USB_Dev->Brightness.Current;
                    min_brightness=USB_Dev->Brightness.Min;
                    max_brightness=USB_Dev->Brightness.Max;
                    default_brightness=USB_Dev->Brightness.Default;
                    step_brightness=0;//USB_Dev->Brightness.Step;


                    //brightness
                    cur_hue=USB_Dev->Hue.Current;
                    min_hue=USB_Dev->Hue.Min;
                    max_hue=USB_Dev->Hue.Max;
                    default_hue=USB_Dev->Hue.Default;
                    step_hue=0;//USB_Dev->Brightness.Step;

                    //sharpness
                    cur_sharpness=USB_Dev->Sharpness.Current;
                    min_sharpness=USB_Dev->Sharpness.Min;
                    max_sharpness=USB_Dev->Sharpness.Max;
                    default_sharpness=USB_Dev->Sharpness.Default;
                    step_sharpness=0;//USB_Dev->Sharpness.Step;
                    //wb
                    min_wb=USB_Dev->WhiteBalance.Min;
                    max_wb=USB_Dev->WhiteBalance.Max;
                    default_wb=USB_Dev->WhiteBalance.Default;
                    step_wb=0;//USB_Dev->WhiteBalance.Step;
                    cur_wb=USB_Dev->WhiteBalance.Current;


                    //fliker
                    cur_fliker=USB_Dev->Flicker.Current;
                    min_fliker=USB_Dev->Flicker.Min;
                    max_fliker=USB_Dev->Flicker.Max;
                    default_fliker=USB_Dev->Flicker.Default;
                    //setting




                     //init min,max,cur,value
                     slider_blc->setMinimum(min_blc);
                     slider_blc->setMaximum(max_blc);
                     slider_blc->setPageStep(step_blc);
                     slider_blc->setValue(cur_blc);

                     slider_gamma->setMinimum(min_gamma);
                     slider_gamma->setMaximum(max_gamma);
                     slider_gamma->setPageStep(step_gamma);
                     slider_gamma->setValue(cur_gamma);



                     slider_contrast->setMinimum(min_contrast);
                     slider_contrast->setMaximum(max_contrast);
                     slider_contrast->setPageStep(step_contrast);
                     slider_contrast->setValue(cur_contrast);

                     slider_saturation->setValue(cur_saturation);
                     slider_saturation->setMinimum(min_saturation);
                     slider_saturation->setMaximum(max_saturation);
                     slider_saturation->setPageStep(step_saturation);


                     slider_brightness->setMinimum(min_brightness);
                     slider_brightness->setMaximum(max_brightness);
                     slider_brightness->setPageStep(step_brightness);
                     slider_brightness->setValue(cur_brightness);


                     slider_hue->setMinimum(min_hue);
                     slider_hue->setMaximum(max_hue);
                     slider_hue->setPageStep(step_hue);
                     slider_hue->setValue(cur_hue);



                     slider_sharpness->setMinimum(min_sharpness);
                     slider_sharpness->setMaximum(max_sharpness);
                     slider_sharpness->setPageStep(step_sharpness);
                     slider_sharpness->setValue(cur_sharpness);

                    // QTest::qSleep ( 10 );

                     slider_wb->setMinimum(min_wb);
                     slider_wb->setMaximum(max_wb);
                     slider_wb->setPageStep(step_wb);
                     slider_wb->setValue(cur_wb);


                     if(USB_Dev->Brightness.Valid==1)
                     {slider_brightness->setEnabled(true);}
                     else
                     {slider_brightness->setEnabled(false);}

                     if(USB_Dev->Hue.Valid==1)
                     {slider_hue->setEnabled(true);}
                     else
                     {slider_hue->setEnabled(false);}




                     v_blc->setText(QString::number(cur_blc));
                     v_gamma->setText(QString::number(cur_gamma));
                     v_contrast->setText(QString::number(cur_contrast));
                     v_saturation->setText(QString::number(cur_saturation));
                     v_brightness->setText(QString::number(cur_brightness));
                     v_hue->setText(QString::number(cur_hue));
                     v_sharpness->setText(QString::number(cur_sharpness));
                     v_wb->setText(QString::number(cur_wb));
                   //  cb_fliker->setCurrentIndex(cur_fliker);
                }
            }


}

/*右侧窗口部分*/
void MainWindow::MovePlace(int num){
    if(MoveChange != num){
      //  qDebug()<<"MovePlace:"<<num;
        MoveChange = num;
        if(USB_Mode){MoveEvent(USB_Dev,MoveChange,XChange*3,YChange*2);}
    }
}
void MainWindow::SpeedX(int num){
    if(XChange != num){
     //   qDebug()<<"SpeedX:"<<num;
        XChange = num;
        if(USB_Mode){MoveEvent(USB_Dev,MoveChange,XChange*3,YChange*2);}
    }
}
void MainWindow::SpeedY(int num){
    if(YChange != num){
     //   qDebug()<<"SpeedY:"<<num;
        YChange = num;
        if(USB_Mode){MoveEvent(USB_Dev,MoveChange,XChange*3,YChange*2);}
    }
}

void MainWindow::MoveEvent(BaseDevice *dev,int place,int x,int y)
{
   // if(menu==1)
    {
        if(place == 0){
            dev->StartMoveLeft(x);
            dev->StartMoveUp(y);
        }else if(place == 1){
            dev->StartMoveUp(y);
        }else if(place == 2){
            dev->StartMoveRight(x);
            dev->StartMoveUp(y);
        }else if(place == 3){
            dev->StartMoveLeft(x);
        }else if(place == 4){
            dev->StopMoveUp();
            dev->StopMoveDown();
            dev->StopMoveLeft();
            dev->StopMoveRight();
        }else if(place == 5){
            dev->StartMoveRight(x);
        }else if(place == 6){
            dev->StartMoveLeft(x);
            dev->StartMoveDown(y);
        }else if(place == 7){
            dev->StartMoveDown(y);
        }else if(place == 8){
            dev->StartMoveDown(y);
            dev->StartMoveRight(x);
        }
    }
   // else
    /*
    {
        if(place == 1){
            dev->StartMoveUp(y);
            qDebug()<<"UP";
        }else if(place == 3){
            dev->StartMoveLeft(x);
            qDebug()<<"LEFT";
        }else if(place == 5){
            dev->StartMoveRight(x);
            qDebug()<<"RIGHT";
        }else if(place == 7){
            dev->StartMoveDown(y);
            qDebug()<<"DOWN";
        }
    }
    */
}

void MainWindow::IPCAMChange(int flag)
{
    IPCAM = flag;
    USB_Dev->CloseDevice();
    USB_Mode = false;
}


void MainWindow::ZoomChange()
{
    static int Zoom_Flag = 7;
    zoom_num_L = Zoom_Flag - Slider_Zoom->value();
    zoom_num_R = Slider_Zoom->value() - Zoom_Flag;
	if(USB_Mode){
        if(zoom_num_L > 0){USB_Dev->StartZoomWide(zoom_num_L);return;}//StartZoomWide
        if(zoom_num_R > 0){USB_Dev->StartZoomTele(zoom_num_R);return;}//StartZoomTele
    }else {Warn_NoDev();}
}

void MainWindow::ZoomStop()
{
    if(USB_Mode){USB_Dev->StopZoom();return;
    }else{Warn_NoDev();}
}

void MainWindow::FocusChange()
{
    static int Focus_Flag = 7;
    foucs_num_L = Focus_Flag - Slider_Fucus->value();
    foucs_num_R = Slider_Fucus->value() - Focus_Flag;
    if(USB_Mode){
        if(foucs_num_L > 0){USB_Dev->StartFocusNear(foucs_num_L);}
        if(foucs_num_R > 0){USB_Dev->StartFocusFar(foucs_num_R);}
    }else{Warn_NoDev();}
}

void MainWindow::FucusStop()
{
    if(USB_Mode){USB_Dev->StopFocus();return;
    }else{Warn_NoDev();}
}

bool MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    return true;
}

void MainWindow::AF_MF_Push(int num)
{
    if(!InitRun){
        if(num == 1){
            if(USB_Mode){USB_Dev->SetFocusAuto();return;
            }else{Warn_NoDev();return;
            }
        }else if(num == 2){
            if(USB_Mode){USB_Dev->SetFocusManual();return;
            }else{Warn_NoDev();return;
            }
        }
    }
}

void MainWindow::ChangePresetno(int num)
{
    Presetno = num;
}

void MainWindow::RWin_BT_Pressed(int flag)
{
    switch (flag) {
    case 1: if(USB_Mode){
            USB_Dev->CloseMenu();
        }QApplication::exit(0);
    case 201: ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);  TopFlag = true;break;
    case 202: ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);TopFlag = false;break;
    case 301: hide_flag = true;break;
    case 302: hide_flag = false;break;
            if(TopFlag){
                ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            }
            if(TopFlag){
                ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            }
            break;
    case 5: if(USB_Mode){USB_Dev->CallPreset(Presetno);}
            break;
    case 6: if(USB_Mode){USB_Dev->SetPreset(Presetno);}
            break;
    case 7:if(USB_Mode){USB_Dev->ClearPreset(Presetno);}
            break;
//set pt position
    case 8:
        if(USB_Mode)
        {
            long str_pan=v_set_pan_data->text().toLong();
            sleep ( 5 );
            long str_tilt=v_set_tilt_data->text().toLong();

            USB_Dev->SetPan(str_pan);
            sleep ( 50 );
            USB_Dev->SetTilt(str_tilt);
        }
        break;
//get pt position
    case 9:

        long str_pan_val;
        long str_tilt_val;
        if(USB_Mode)
        {
            USB_Dev->GetPan(&str_pan_val);
           // qDebug()<<str_pan_val;
            sleep ( 50 );
            USB_Dev->GetTilt(&str_tilt_val);

            v_get_pan_data->setText(QString::number(str_pan_val));
            v_get_tilt_data->setText(QString::number(str_tilt_val));
        }
        break;
    //get pt position
        case 10:
            long str_roll_val;
            if(USB_Mode)
            {
                USB_Dev->GetRoll(&str_roll_val);
                qDebug()<<str_roll_val;
                v_get_roll_data->setText(QString::number(str_roll_val));
            }
            break;
    }
}

int autoai_flag;
/*左侧窗口部分*/
void MainWindow::LWin_BT_Pressed(int flag)
{
   // qDebug()<<flag;
    if(!InitRun){
    switch(flag)
    {
    case 1: //auto  whitebalance
        if(USB_Mode)
        {
            USB_Dev->SetWhiteBalanceAuto(true);
            slider_wb->setEnabled(false);
        }
            break;
    case 2://manual whitebalance
        if(USB_Mode)
        {
            USB_Dev->SetWhiteBalanceAuto(false);
            slider_wb->setEnabled(true);
            slider_wb->setValue(default_wb);
            v_wb->setText(QString::number(default_wb));
            USB_Dev->SetWhiteBalance(default_wb);
        }
            break;
    case 3://flip
        if(USB_Mode){
            if(flip == 1){
                USB_Dev->CloseFlip();flip = 0;
            }else{
                USB_Dev->OpenFlip();flip = 1;
            }
        }
        break;

    case 4://mirror
        if(USB_Mode){
            if(mirror == 1){                   //当前开
                USB_Dev->CloseMirror();mirror = 0;
            }else{
                USB_Dev->OpenMirror();mirror = 1;
            }
        }
       break;

    case 5://menu
        if(USB_Mode){
                USB_Dev->OpenMenu();menu = 1;
             }
            break;

    case 10://menu
        if(USB_Mode){                  //当前开
                USB_Dev->CloseMenu();menu = 0;
        }
            break;

    case 6://home
            if(USB_Mode){USB_Dev->HomePosition();}
            break;

    case 7://freeze

            if(USB_Mode==1)
            {
                USB_Dev->OpenAI();
            }


        break;

    case 8://ai

        if(USB_Mode==1)
        {
            USB_Dev->CloseAI();
        }

        break;

    case 9://reset
        if(USB_Mode==1)
        {
            Value_Reset(USB_Dev);
        }
        break;

    case 11://IR ON
        if(USB_Mode==1)
        {
            USB_Dev->SetIRON();
        }
        break;

    case 12://IR OFF
        if(USB_Mode==1)
        {
            USB_Dev->SetIROFF();
        }
        break;

    case 13://DAY
        if(USB_Mode==1)
        {
            USB_Dev->SetIR_DAY_MODE();
        }
        break;

    case 14://NIGHT
        if(USB_Mode==1)
        {
            USB_Dev->SetIR_NIGHT_MODE();
        }
        break;

    case 15://PTZ RESET
        if(USB_Mode==1)
        {
            USB_Dev->Set_ptz_reset();
        }
        break;
    }

   }
}




void MainWindow::FlickerChange()
{
    if(!InitRun){
        if(ComboBox_Flicker->currentText() == "50Hz"){
            if(USB_Mode){USB_Dev->SetFlicker(1);
            }else{Warn_NoDev();}
        }else if(ComboBox_Flicker->currentText() == "60Hz"){
            if(USB_Mode){USB_Dev->SetFlicker(2);
            }else{Warn_NoDev();}
        }
    }
}




void MainWindow::Brightness_Change(int position)
{
  //  qDebug()<<position;
    v_brightness->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetBrightness(position);
        }else{Warn_NoDev();}
    }
}

void MainWindow::Contrast_Change(int position)
{
    v_contrast->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetContrast(position);
        }else{Warn_NoDev();}
    }
}

void MainWindow::Hue_Change(int position)
{
    v_hue->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetHue(position);
        }else{Warn_NoDev();}
    }
}
void MainWindow::Saturation_Change(int position)
{
    v_saturation->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetSaturation(position);
        }else{Warn_NoDev();}
    }
}

void MainWindow::Sharpness_Change(int position)
{
    v_sharpness->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetSharpness(position);
        }else{Warn_NoDev();}
    }
}

void MainWindow::Gamma_Change(int position)
{
    v_gamma->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetGamma(position);
        }else{Warn_NoDev();}
    }
}

void MainWindow::BLC_Change(int position)
{
    v_blc->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetBLC(position);
        }else{Warn_NoDev();}
    }
}
void MainWindow::WB_Change(int position)
{
    v_wb->setText(QString::number(position));
    if(!InitRun){
        if(USB_Mode){USB_Dev->SetWhiteBalance(position);
        }else{Warn_NoDev();}
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){m_pressed = true;m_pos = event->pos();}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed){move(event->pos() - m_pos + this->pos());}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    if(Screen_edge()){R_Hide = true;}
    else{R_Hide = false;}
    QWidget::mouseReleaseEvent(event);
}
void MainWindow::timerEvent(QTimerEvent *event)
{
}

void MainWindow::enterEvent(QEvent *event)
{
    if(Show_flag == true){
        if(QApplication::desktop()->width() - this->x() != 10){
            return QWidget::enterEvent(event);
        }
    }
    if(R_Hide){
        if(Show_flag == false){
            for(int i = 10;i<=ui->Win_Right->width()-10;i+=10){
                move(this->frameGeometry().x()-10,this->frameGeometry().y());
            }
            move(this->frameGeometry().x()-ui->Win_Right->width()%10,this->frameGeometry().y());
        }
        else{
            for(int i = 10;i<=width()-10;i+=10){
                move(this->frameGeometry().x()-10,this->frameGeometry().y());
            }
            move(this->frameGeometry().x()-width()%10,this->frameGeometry().y());

        }
        ui->Label_Hide_L->hide();ui->Label_Hide_R->hide();
    }
    return QWidget::enterEvent(event);
}

void MainWindow::leaveEvent(QEvent *event)
{
    if(R_Hide){
        if(Show_flag == true){
            //全窗口收缩
            setGeometry(QApplication::desktop()->width() - width() + 10, pos().y(), width(), height());
            for(int i=10;i<=width()-20;i+=10){
                move(this->frameGeometry().x()+10,this->frameGeometry().y());
            }
            move(this->frameGeometry().x()+width()%10,this->frameGeometry().y());
            ui->Label_Hide_L->show();
        }
        else{
            //简洁窗口收缩
            setGeometry(QApplication::desktop()->width() - width() + 10, pos().y(), width(), height());
            for(int i=10;i<=ui->Win_Right->width()-20;i+=10){
                move(this->frameGeometry().x()+10,this->frameGeometry().y());
            }
            move(this->frameGeometry().x()+ui->Win_Right->width()%10,this->frameGeometry().y());
            ui->Label_Hide_R->show();
        }
    }
    return QWidget::leaveEvent(event);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if (eventType == "windows_generic_MSG")
    {
        bool bResult = false;
        MSG* msg = reinterpret_cast<MSG*>(message);
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        if(msg->message == WM_DEVICECHANGE && msg->wParam >= DBT_DEVICEARRIVAL)
        {
            switch (msg->wParam)
            {
            case DBT_DEVICEARRIVAL:
            //    qDebug()<<"Device Add";
                Tim->start(500);
                bResult = true;
                break;

            case DBT_DEVICEREMOVECOMPLETE:
             //   qDebug()<<"Device Leave";
                Tim->start(500);
                bResult = true;
                break;

            case DBT_DEVNODES_CHANGED:
            //    qDebug()<<"Device Change";
                bResult = true;
                break;
            default:
                bResult = false;
                break;
            }
        }
        return bResult;
    }
    else
    {
        return QWidget::nativeEvent(eventType, message, result);
    }
}



bool MainWindow::Screen_edge()
{
    if(QApplication::desktop()->width() <= (this->x() + width())){return true;}
    else{return false;}
}

//左侧窗口伸缩动画部分
void MainWindow::Tool_Show(bool flag)
{
    if(flag == true){
        //左侧窗口弹出
        for(int i = 20;i<=lwidth;i+=20){
            ui->frame->setGeometry(lwidth-i,0,i,height());
            ui->Win_Left->setGeometry(lwidth-i,0,i,height());
            repaint();
        }
        ui->frame->setGeometry(0,0,lwidth,height());
        ui->Win_Left->setGeometry(0,0,lwidth,height());

        Show_flag = true;
    }else if(flag == false){
        //左侧窗口缩入
        for(int i = 20;i<=lwidth;i+=20){
            ui->frame->setGeometry(i,0,lwidth-i,height());
            ui->Win_Left->setGeometry(i,0,lwidth-i,height());
            repaint();
        }
        ui->frame->setGeometry(lwidth,0,0,height());
        ui->Win_Left->setGeometry(lwidth,0,0,height());

        Show_flag = false;
    }
}


void MainWindow::Value_Reset(BaseDevice *dev)
{

    slider_brightness->setValue(dev->Brightness.Default);
    slider_contrast->setValue(dev->Contrast.Default);
    slider_hue->setValue(dev->Hue.Default);
    slider_saturation->setValue(dev->Saturation.Default);
    slider_sharpness->setValue(dev->Sharpness.Default);
    slider_gamma->setValue(dev->Gamma.Default);
    slider_blc->setValue(dev->BLC.Default);
    slider_wb->setValue(dev->WhiteBalance.Default);


    v_blc->setText(QString::number(default_blc));
    v_gamma->setText(QString::number(default_gamma));
    v_contrast->setText(QString::number(default_contrast));
    v_saturation->setText(QString::number(default_saturation));
    v_brightness->setText(QString::number(default_brightness));
    v_hue->setText(QString::number(default_hue));
    v_sharpness->setText(QString::number(default_sharpness));
    v_wb->setText(QString::number(default_wb));

    dev->SetDefaultValues();
}

void MainWindow::Warn_NoDev(){
    if(TopFlag){
        ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
    QMessageBox::warning(NULL,"Warning","Please plug in the telycam's camera !", QMessageBox::Yes, QMessageBox::Yes);
    if(TopFlag){
        ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
}

