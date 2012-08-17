#include "menutab.h"
#include "mainwindow.h"

MenuTab::MenuTab(MainWindow *Win)
{
    mainWin = Win;
    createActions();
    createMenu();
    trueIcon = ":/icons/true.png";
    falseIcon =":/icons/false.png";
    QObject::connect(this,SIGNAL(initTangoSettingWin(int)), mainWin,SLOT(initTangoSettingWin(int)));
    QObject::connect(this,SIGNAL(saveSnap()), mainWin,SLOT(saveImg()));
    QObject::connect(this,SIGNAL(printSnap()), mainWin,SLOT(printSnap()));
    QObject::connect(this,SIGNAL(resetImg()), mainWin,SLOT(resetImg()));
    QObject::connect(this,SIGNAL(initStartTangoWin()), mainWin,SLOT(initStartTangoWin()));
    QObject::connect(this,SIGNAL(changeServerManipulation()), mainWin,SLOT(chServerManipulation()));
    QObject::connect(this,SIGNAL(changeFullPictureMode()), mainWin,SLOT(setFullPictureMode()));
    QObject::connect(this,SIGNAL(changeFullPictureModeSnap()), mainWin,SLOT(setFullPictureModeSnap()));
    QObject::connect(this,SIGNAL(mkSnap()), mainWin,SLOT(mkSnapshot()));

    QObject::connect(this,SIGNAL(setTangoAttrNames()), mainWin,SLOT(initTangoNamesWin()));
}

MenuTab::~MenuTab()
{
    delete server;
    delete snapshot;                         //Snapshot menu
    delete realtime;                                               //Realtime menu

    delete addNewDevice;             //set tango device in new app
    delete pushCommand;             //set tango command
    delete serverManipulation;            //Make operations on the server??
    delete serverAttrNames;            //Make operations on the server??
    delete exitAct ;	                  //Stop app

    delete scaleRealtime;
    delete setBrightnessRealtime;
    delete setContrastRealtime;
    delete setGammaRealtime ;
    delete setRotationRealtime;
    delete verFlipRealtime;
    delete horFlipRealtime ;
    delete resetImgRealtime;
    delete makeMarker;

    delete makeSnapshot;
    delete printSnapshot;
    delete saveSnapshot;
    delete scaleSnapshot;
    delete horFlipSnapshot;
    delete verFlipSnapshot;
    delete setBrightnessSnapshot;
    delete setContrastSnapshot;
    delete setGammaSnapshot	;
    delete setRotationSnapshot	;
    delete resetImgSnapshot	;

    delete chOnScaleRealtime;
    delete chOnBrightnessRealtime;
    delete chOnContrastRealtime;
    delete chOnGammaRealtime ;
    delete chOnRotationRealtime;

    delete chOnScaleSnapshot;
    delete chOnBrightnessSnapshot;
    delete chOnContrastSnapshot;
    delete chOnGammaSnapshot	;
    delete chOnRotationSnapshot	;

    delete is16BitGrey;
    delete is8BitGrey;
    delete is8BitColor;
    delete isRGBGrey;
    delete isRGB_ARGB;

    delete fullPictureMode;
    delete fullPictureModeSnap;


    delete setImageFormatIndex8;
            delete setImageFormatRGB32;
            delete setImageFormatARGB32;
            delete setImageFormatARGB32Pre;
            delete setImageFormatRGB16;
            delete setImageFormatARGB8565Pre;
            delete setImageFormatRGB666;
            delete setImageFormatARGB6666Pre;
            delete setImageFormatRGB555;
            delete setImageFormatARGB8555Pre;
            delete setImageFormatRGB888;
            delete setImageFormatRGB444;
            delete setImageFormatARGB4444Pre;
}

void MenuTab::createMenu(){
    server = mainWin->menuBar()->addMenu(QString("&Server"));
    server->addAction(addNewDevice);
    server->addSeparator();
    server->addAction(exitAct);

    realtime = mainWin->menuBar()->addMenu(tr("&Realtime"));
    realtime->addAction(makeSnapshot);
    realtime->addAction(serverManipulation);
    realtime->addAction(serverAttrNames);
    realtime->addAction(pushCommand);
    realtime->addSeparator();
    setValRealtime = realtime->addMenu("Set value");
    setValRealtime->addAction(scaleRealtime);
    setValRealtime->addAction(setBrightnessRealtime);
    setValRealtime->addAction(setContrastRealtime);
    setValRealtime->addAction(setGammaRealtime);
    setValRealtime->addAction(setRotationRealtime);
    setValRealtime->addAction(horFlipRealtime);
    setValRealtime->addAction(verFlipRealtime);
    setValRealtime->addAction(timeOutRealtime);
    changeOnValRealtime = realtime->addMenu("Change on value");
    changeOnValRealtime->addAction(chOnScaleRealtime);             //scale current snapshot  //not used
    changeOnValRealtime->addAction(chOnRotationRealtime);
    setImageMode = realtime->addMenu("Image Mode");
    setImageMode->addAction(is16BitGrey);
    setImageMode->addAction(is8BitGrey);
    setImageMode->addAction(is8BitColor);
    setImageMode->addAction(isRGBGrey);
    setImageMode->addAction(isRGB_ARGB);

    realtime->addAction(makeMarker);
     submenuImageFormat = realtime->addMenu("Image Format");
        submenuImageFormat->addAction(setImageFormatIndex8);
        submenuImageFormat->addAction(setImageFormatRGB32);
        submenuImageFormat->addAction(setImageFormatARGB32);
        submenuImageFormat->addAction(setImageFormatARGB32Pre);
        submenuImageFormat->addAction(setImageFormatRGB16);
        submenuImageFormat->addAction(setImageFormatARGB8565Pre);
        submenuImageFormat->addAction(setImageFormatRGB666);
        submenuImageFormat->addAction(setImageFormatARGB6666Pre);
        submenuImageFormat->addAction(setImageFormatRGB555);
        submenuImageFormat->addAction(setImageFormatARGB8555Pre);
        submenuImageFormat->addAction(setImageFormatRGB888);
        submenuImageFormat->addAction(setImageFormatRGB444);
        submenuImageFormat->addAction(setImageFormatARGB4444Pre);

    realtime->addAction(fullPictureMode);
    realtime->addAction(pauseRealtime);
    realtime->addAction(resetImgRealtime);
    realtime->setEnabled(false);

    snapshot = mainWin->menuBar()->addMenu(tr("&Snapshot"));
    setValSnapshot = snapshot->addMenu("Set value");
    setValSnapshot->addAction(scaleSnapshot);             //scale current snapshot  //not used
    setValSnapshot->addAction(setBrightnessSnapshot);
    setValSnapshot->addAction(setContrastSnapshot);
    setValSnapshot->addAction(setGammaSnapshot);
    setValSnapshot->addAction(setRotationSnapshot);
    setValSnapshot->addAction(horFlipSnapshot);
    setValSnapshot->addAction(verFlipSnapshot);
    changeOnValSnapshot = snapshot->addMenu("Change on value");
    changeOnValSnapshot->addAction(chOnScaleSnapshot);             //scale current snapshot  //not used
    changeOnValSnapshot->addAction(chOnRotationSnapshot);
    snapshot->addAction(fullPictureModeSnap);
    snapshot->addAction(saveSnapshot);
    snapshot->addAction(printSnapshot);
    snapshot->addAction(resetImgSnapshot);
    snapshot->setEnabled(false);
}

void MenuTab::initPropManipRealtime(){
    scaleRealtime = new QAction(tr("&Scale"), this);
    scaleRealtime->setStatusTip(tr("Scale RealTime"));
    QObject::connect(scaleRealtime, SIGNAL(triggered()), this, SLOT(settingScaleRealtime()));

    setBrightnessRealtime = new QAction(tr("&Set Brightness"), this);
    setBrightnessRealtime->setStatusTip(tr("Set Brightness"));
    QObject::connect(setBrightnessRealtime, SIGNAL(triggered()), this, SLOT(settingBrightnessRealtime()));

    setContrastRealtime = new QAction(tr("&Set Contrast"), this);
    setContrastRealtime->setStatusTip(tr("Set Contrast"));
    QObject::connect(setContrastRealtime, SIGNAL(triggered()), this, SLOT(settingContrastRealtime()));

    setGammaRealtime = new QAction(tr("&Set Gamma"), this);
    setGammaRealtime->setStatusTip(tr("Set Gamma"));
    QObject::connect(setGammaRealtime, SIGNAL(triggered()), this, SLOT(settingGammaRealtime()));

    setRotationRealtime = new QAction(tr("&Set Rotation"), this);
    setRotationRealtime->setStatusTip(tr("Set Rotation"));
    QObject::connect(setRotationRealtime, SIGNAL(triggered()), this, SLOT(settingRotationRealtime()));

    horFlipRealtime = new QAction(QIcon(falseIcon), tr("&Horizontal Fliping"), this);
    horFlipRealtime->setStatusTip(tr("Horizontal Fliping"));
    QObject::connect(horFlipRealtime, SIGNAL(triggered()), this, SLOT(changeFlipHorRealtime()));

    verFlipRealtime = new QAction(QIcon(falseIcon), tr("&Vertical Fliping"), this);
    verFlipRealtime->setStatusTip(tr("Vertical Fliping"));
    QObject::connect(verFlipRealtime, SIGNAL(triggered()), this, SLOT(changeFlipVerRealtime()));

    chOnBrightnessRealtime = new QAction(tr("&Brightness"), this);
    chOnBrightnessRealtime->setStatusTip(tr("Set Brightness"));
    QObject::connect(chOnBrightnessRealtime, SIGNAL(triggered()), this, SLOT(onChBrightnessRealtime()));

    chOnContrastRealtime = new QAction(tr("&Contrast"), this);
    chOnContrastRealtime->setStatusTip(tr("Set Contrast"));
    QObject::connect(chOnContrastRealtime, SIGNAL(triggered()), this, SLOT(onChContrastRealtime()));

    chOnGammaRealtime = new QAction(tr("&Gamma"), this);
    chOnGammaRealtime->setStatusTip(tr("Set Gamma"));
    QObject::connect(chOnGammaRealtime, SIGNAL(triggered()), this, SLOT(onChGammaRealtime()));

    chOnRotationRealtime = new QAction(tr("&Rotation"), this);
    chOnRotationRealtime->setStatusTip(tr("Set Rotation"));
    QObject::connect(chOnRotationRealtime, SIGNAL(triggered()), this, SLOT(onChRotationRealtime()));

    chOnScaleRealtime = new QAction(tr("&Scale"), this);
    chOnScaleRealtime->setStatusTip(tr("Ch Scale"));
    QObject::connect(chOnScaleRealtime, SIGNAL(triggered()), this, SLOT(onChScaleRealtime()));
}

void MenuTab::initPropManipSnap(){
    scaleSnapshot = new QAction(tr("&Scale Snapshot"), this);
    scaleSnapshot->setStatusTip(tr("Scale Snapshot"));
    QObject::connect(scaleSnapshot, SIGNAL(triggered()), this, SLOT(settingScaleSnapshot()));

    horFlipSnapshot = new QAction(QIcon(trueIcon), tr("&Horizontal Fliping"), this);
    horFlipSnapshot->setStatusTip(tr("Horizontal Fliping"));
    QObject::connect(horFlipSnapshot, SIGNAL(triggered()), this, SLOT(changeFlipHorSnapshot()));

    verFlipSnapshot = new QAction(QIcon(falseIcon), tr("&Vertical Fliping"), this);
    verFlipSnapshot->setStatusTip(tr("Vertical Fliping"));
    QObject::connect(verFlipSnapshot, SIGNAL(triggered()), this, SLOT(changeFlipVerSnapshot()));

    setBrightnessSnapshot = new QAction(tr("&Set Brightness"), this);
    setBrightnessSnapshot->setStatusTip(tr("Set Brightness"));
    QObject::connect(setBrightnessSnapshot, SIGNAL(triggered()), this, SLOT(settingBrightnessSnapshot()));

    setContrastSnapshot = new QAction(tr("&Set Contrast"), this);
    setContrastSnapshot->setStatusTip(tr("Set Contrast"));
    QObject::connect(setContrastSnapshot, SIGNAL(triggered()), this, SLOT(settingContrastSnapshot()));

    setGammaSnapshot = new QAction(tr("&Set Gamma"), this);
    setGammaSnapshot->setStatusTip(tr("Set Gamma"));
    QObject::connect(setGammaSnapshot, SIGNAL(triggered()), this, SLOT(settingGammaSnapshot()));

    setRotationSnapshot = new QAction(tr("&Set Rotation"), this);
    setRotationSnapshot->setStatusTip(tr("Set Rotation"));
    QObject::connect(setRotationSnapshot, SIGNAL(triggered()), this, SLOT(settingRotationSnapshot()));

    chOnBrightnessSnapshot = new QAction(tr("&Set Brightness"), this);
    chOnBrightnessSnapshot->setStatusTip(tr("Set Brightness"));
    QObject::connect(chOnBrightnessSnapshot, SIGNAL(triggered()), this, SLOT(onChBrightnessSnapshot()));

    chOnContrastSnapshot = new QAction(tr("&Contrast"), this);
    chOnContrastSnapshot->setStatusTip(tr("Ch Contrast"));
    QObject::connect(chOnContrastSnapshot, SIGNAL(triggered()), this, SLOT(onChContrastSnapshot()));

    chOnGammaSnapshot = new QAction(tr("&Gamma"), this);
    chOnGammaSnapshot->setStatusTip(tr("Ch Gamma"));
    QObject::connect(chOnGammaSnapshot, SIGNAL(triggered()), this, SLOT(onChGammaSnapshot()));

    chOnRotationSnapshot = new QAction(tr("&Rotation"), this);
    chOnRotationSnapshot->setStatusTip(tr("Ch Rotation"));
    QObject::connect(chOnRotationSnapshot, SIGNAL(triggered()), this, SLOT(onChRotationSnapshot()));

    chOnScaleSnapshot = new QAction(tr("&Scale"), this);
    chOnScaleSnapshot->setStatusTip(tr("Ch Scale"));
    QObject::connect(chOnScaleSnapshot, SIGNAL(triggered()), this, SLOT(onChScaleSnapshot()));
}
void MenuTab::initPicMode(){
    is16BitGrey =  new QAction(QIcon(trueIcon), tr("&16Bit Grey"), this);
    is16BitGrey->setStatusTip(tr("16Bit Grey"));
    QObject::connect(is16BitGrey, SIGNAL(triggered()), mainWin, SLOT(set16BitGreyImageMode()));

    is8BitGrey =  new QAction(QIcon(trueIcon), tr("&8Bit Grey"), this);
    is8BitGrey->setStatusTip(tr("8Bit Grey"));
    QObject::connect(is8BitGrey, SIGNAL(triggered()), mainWin, SLOT(set8BitGreyImageMode()));

    is8BitColor =  new QAction(QIcon(trueIcon), tr("&8Bit Color"), this);
    is8BitColor->setStatusTip(tr("8Bit Color"));
    QObject::connect(is8BitColor, SIGNAL(triggered()), mainWin, SLOT(set8BitColorImageMode()));

    isRGBGrey =  new QAction(QIcon(trueIcon), tr("&RGB Grey"), this);
    isRGBGrey->setStatusTip(tr("RGB Grey"));
    QObject::connect(isRGBGrey, SIGNAL(triggered()), mainWin, SLOT(setRGBGreyImageMode()));


    isRGB_ARGB =  new QAction(QIcon(trueIcon), tr("&RGB/ARGB"), this);
    isRGB_ARGB->setStatusTip(tr("RGB/ARGB"));
    QObject::connect(isRGB_ARGB, SIGNAL(triggered()), mainWin, SLOT(setRGB_ARGBImageMode()));
}

void MenuTab::initServer(){
    /*Server*/
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Finish working"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

    addNewDevice = new QAction(tr("&Start new device"), this);
    addNewDevice->setShortcuts(QKeySequence::New);
    addNewDevice->setStatusTip(tr("Start new device"));
    connect(addNewDevice, SIGNAL(triggered()), this, SLOT(startNewDevice()));
    pushCommand = new QAction(tr("&Send a command"), this);
    pushCommand->setStatusTip(tr("Send a command"));
    connect(pushCommand, SIGNAL(triggered()), this, SLOT(sendCommand()));



    serverManipulation = new QAction(QIcon(falseIcon), tr("&Server manipulation"), this);
    serverManipulation->setStatusTip(tr("Server manipulation"));
    connect(serverManipulation, SIGNAL(triggered()), this, SLOT(setServerManipulation()));

    serverAttrNames = new QAction(tr("&Set Tango variables"), this);
    serverAttrNames->setStatusTip(tr("Set Tango variables"));
    connect(serverAttrNames, SIGNAL(triggered()), this, SLOT(setServerAttrNames()));
}
void MenuTab::initRealtime(){
    /*Realtime*/
    initPropManipRealtime();
    initPicMode();

    makeSnapshot = new QAction(tr("&Make a snapshot"), this);
    makeSnapshot->setStatusTip(tr("Make a snapshot"));
    QObject::connect(makeSnapshot, SIGNAL(triggered()), this, SLOT(mkSnapshot()));

    resetImgRealtime = new QAction(tr("&Reset Image"), this);
    resetImgRealtime->setStatusTip(tr("Reset Image"));
    QObject::connect(resetImgRealtime, SIGNAL(triggered()), this, SLOT(setResetImgRealtime()));

    fullPictureMode =  new QAction(QIcon(trueIcon), tr("&Full picture"), this);
    fullPictureMode->setStatusTip(tr("Full picture"));
    QObject::connect(fullPictureMode, SIGNAL(triggered()), this, SLOT(setFullPictureMode()));

    pauseRealtime = new QAction(QIcon(falseIcon), tr("&Timeout"), this);
    pauseRealtime->setStatusTip(tr("Timeout"));
    QObject::connect(pauseRealtime, SIGNAL(triggered()), mainWin, SLOT(setRealtimePause()));

    timeOutRealtime = new QAction(tr("&Timeout(ms)"), this);
    timeOutRealtime->setStatusTip(tr("Timeout(ms)"));
    QObject::connect(timeOutRealtime, SIGNAL(triggered()), this, SLOT(settingTimeOutRealtime()));

    makeMarker  = new QAction(tr("&Set Marker"), this);
    makeMarker->setStatusTip(tr("Set Marker"));
    QObject::connect(makeMarker, SIGNAL(triggered()), mainWin, SLOT(setMarkerPos ()));
}
void MenuTab::initSnap(){
    /*Snapshot*/
    initPropManipSnap();

    fullPictureModeSnap = new QAction(QIcon(falseIcon), tr("&Full picture"), this);
    fullPictureModeSnap->setStatusTip(tr("Full picture"));
    QObject::connect(fullPictureModeSnap, SIGNAL(triggered()), this, SLOT(setFullPictureModeSnap()));

    saveSnapshot = new QAction(tr("&Save a snapshot"), this);
    saveSnapshot->setStatusTip(tr("Save a snapshot"));
    QObject::connect(saveSnapshot, SIGNAL(triggered()), this, SLOT(saveCurSnapshot()));

    printSnapshot = new QAction(tr("&Print a snapshot"), this);
    printSnapshot->setStatusTip(tr("Print a snapshot"));
    QObject::connect(printSnapshot, SIGNAL(triggered()), this, SLOT(printCurSnapshot()));

    resetImgSnapshot =  new QAction(tr("&Reset Image"), this);
    resetImgSnapshot->setStatusTip(tr("Set Rotation"));
    QObject::connect(resetImgSnapshot, SIGNAL(triggered()), this, SLOT(setResetImgSnapshot()));

}
void MenuTab::createActions(){
    setImageFormatIndex8 = new QAction(tr("&Index8"), this);
       setImageFormatIndex8->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatIndex8, SIGNAL(triggered()), mainWin, SLOT(setIndex8()));

       setImageFormatRGB32 = new QAction(tr("&RGB32"), this);
       setImageFormatRGB32->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatRGB32, SIGNAL(triggered()), mainWin, SLOT(setRGB32()));

       setImageFormatARGB32 = new QAction(tr("&ARGB32"), this);
       setImageFormatARGB32->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatARGB32, SIGNAL(triggered()), mainWin, SLOT(setARGB32()));

       setImageFormatARGB32Pre = new QAction(tr("&ARGB32Pre"), this);
       setImageFormatARGB32Pre->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatARGB32Pre, SIGNAL(triggered()), mainWin, SLOT(setARGB32Pre()));

       setImageFormatRGB16 = new QAction(tr("&RGB16"), this);
       setImageFormatRGB16->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatRGB16, SIGNAL(triggered()), mainWin, SLOT(setRGB32()));

       setImageFormatARGB8565Pre = new QAction(tr("&ARGB8565Pre"), this);
       setImageFormatARGB8565Pre->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatARGB8565Pre, SIGNAL(triggered()), mainWin, SLOT(setRGB16()));

       setImageFormatRGB666 = new QAction(tr("&RGB666"), this);
       setImageFormatRGB666->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatRGB666, SIGNAL(triggered()), mainWin, SLOT(setRGB666()));

       setImageFormatARGB6666Pre = new QAction(tr("&ARGB666Pre"), this);
       setImageFormatARGB6666Pre->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatARGB6666Pre, SIGNAL(triggered()), mainWin, SLOT(setARGB6666Pre()));

       setImageFormatRGB555 = new QAction(tr("&RGB555"), this);
       setImageFormatRGB555->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatRGB555, SIGNAL(triggered()), mainWin, SLOT(setRGB555()));

       setImageFormatARGB8555Pre = new QAction(tr("&ARGB8555Pre"), this);
       setImageFormatARGB8555Pre->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatARGB8555Pre, SIGNAL(triggered()), mainWin, SLOT(setARGB8555Pre()));

       setImageFormatRGB888 = new QAction(tr("&RGB888"), this);
       setImageFormatRGB888->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatRGB888, SIGNAL(triggered()), mainWin, SLOT(setRGB888()));

       setImageFormatRGB444 = new QAction(tr("&RGB444"), this);
       setImageFormatRGB444->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatRGB444, SIGNAL(triggered()), mainWin, SLOT(setRGB444()));

       setImageFormatARGB4444Pre = new QAction(tr("&ARGB4444Pre"), this);
       setImageFormatARGB4444Pre->setStatusTip(tr("Set Image Format"));
       QObject::connect(setImageFormatARGB4444Pre, SIGNAL(triggered()), mainWin, SLOT(setARGB4444Pre()));
    initServer();
    initSnap();
    initRealtime();
}

void MenuTab::setFullPictureMode(){
    emit changeFullPictureMode();
}

void MenuTab::setFullPictureModeSnap(){
    emit changeFullPictureModeSnap();
}

void MenuTab::saveCurSnapshot(){
    emit saveSnap();
}
void MenuTab::printCurSnapshot(){
    emit printSnap();
}
void MenuTab::mkSnapshot(){
    emit mkSnap();
}

void MenuTab::settingTimeOutRealtime() {
    emit initTangoSettingWin(REALTIMETIMEOUT);
}

void MenuTab::settingBrightnessSnapshot(){
    emit initTangoSettingWin(BRIGHTNESS);
}
void MenuTab::settingGammaSnapshot(){
    emit initTangoSettingWin(GAMMA);
}
void MenuTab::settingContrastSnapshot(){
    emit initTangoSettingWin(CONTRAST);
}
void MenuTab::settingScaleSnapshot()    {
    emit initTangoSettingWin(SCALE);
}
void MenuTab::settingRotationSnapshot() {
    emit initTangoSettingWin(ROTATION);
}
void MenuTab::setResetImgSnapshot()     {
    emit resetImg();
}
void MenuTab::setResetImgRealtime()     {
    emit resetImg();
}
void MenuTab::settingBrightnessRealtime(){
    emit initTangoSettingWin(BRIGHTNESS);
}
void MenuTab::settingGammaRealtime() {
    emit initTangoSettingWin(GAMMA);
}
void MenuTab::settingContrastRealtime(){
    emit initTangoSettingWin(CONTRAST);
}
void MenuTab::settingScaleRealtime()  {
    emit initTangoSettingWin(SCALE);
}
void MenuTab::settingRotationRealtime(){
    emit initTangoSettingWin(ROTATION);
}
void MenuTab::changeFlipHorRealtime(){
    emit initTangoSettingWin(HOR_FLIP);
}
void MenuTab::changeFlipVerRealtime(){
    emit initTangoSettingWin(VER_FLIP);
}
void MenuTab::changeFlipHorSnapshot(){
    emit initTangoSettingWin(HOR_FLIP);
}
void MenuTab::changeFlipVerSnapshot(){
    emit initTangoSettingWin(VER_FLIP);
}

void MenuTab::startNewDevice(){
    emit initStartTangoWin();
}
void MenuTab::sendCommand()    {
    emit initTangoSettingWin(TANGO_COM);
}
void MenuTab::setServerManipulation(){
    emit changeServerManipulation();
}
void MenuTab::setServerAttrNames(){
    emit setTangoAttrNames();
}
void MenuTab::exit(){
    mainWin->close();
}

void MenuTab::setChFlipHorSnapshot(bool val){
    if (val){
        horFlipSnapshot->setIcon(QIcon(trueIcon));
    }
    else{
        horFlipSnapshot->setIcon(QIcon(falseIcon));
    }
}
void MenuTab::setChFlipVerSnapshot(bool val){
    if (val){
        verFlipSnapshot->setIcon(QIcon(trueIcon));
    }
    else{
        verFlipSnapshot->setIcon(QIcon(falseIcon));
    }
}
void MenuTab::setChFlipHorRealtime(bool val){
    if (val){
        horFlipRealtime->setIcon(QIcon(trueIcon));
    }
    else{
        horFlipRealtime->setIcon(QIcon(falseIcon));
    }
}
void MenuTab::setChFlipVerRealtime(bool val){
    if (val){
        verFlipRealtime->setIcon(QIcon(trueIcon));
    }
    else{
        verFlipRealtime->setIcon(QIcon(falseIcon));
    }
}
void MenuTab::setChServerManip(bool val){
    if (val){
        serverManipulation->setIcon(QIcon(trueIcon));
    }
    else{
        serverManipulation->setIcon(QIcon(falseIcon));
    }
}

void MenuTab::setChFullPictureMode(bool val){
    if (val){
        fullPictureMode->setIcon(QIcon(trueIcon));
    }
    else{
        fullPictureMode->setIcon(QIcon(falseIcon));

    }
}
void MenuTab::setChFullPictureModeSnap(bool val){
    if (val){
        fullPictureModeSnap->setIcon(QIcon(trueIcon));
    }
    else{
        fullPictureModeSnap->setIcon(QIcon(falseIcon));

    }
}

void MenuTab::onChBrightnessRealtime(){
    emit initTangoSettingWin(BRIGHTNESS_CH_ON);
}
void MenuTab::onChGammaRealtime() {
    emit initTangoSettingWin(GAMMA_CH_ON);
}
void MenuTab::onChContrastRealtime(){
    emit initTangoSettingWin(CONTRAST_CH_ON);
}
void MenuTab::onChScaleRealtime()  {
    emit initTangoSettingWin(SCALE_CH_ON);
}
void MenuTab::onChRotationRealtime(){
    emit initTangoSettingWin(ROTATION_CH_ON);
}
void MenuTab::onChBrightnessSnapshot(){
    emit initTangoSettingWin(BRIGHTNESS_CH_ON);
}
void MenuTab::onChGammaSnapshot() {
    emit initTangoSettingWin(GAMMA_CH_ON);
}
void MenuTab::onChContrastSnapshot(){
    emit initTangoSettingWin(CONTRAST_CH_ON);
}
void MenuTab::onChScaleSnapshot()    {
    emit initTangoSettingWin(SCALE_CH_ON);
}
void MenuTab::onChRotationSnapshot() {
    emit initTangoSettingWin(ROTATION_CH_ON);
}

void MenuTab::setUCharImageModeEnable(bool mode){
    setBrightnessRealtime->setEnabled(mode);
    setContrastRealtime->setEnabled(mode);
    setGammaRealtime->setEnabled(mode) ;

    is16BitGrey->setEnabled(!mode);
    is8BitColor->setEnabled(mode);
    is8BitGrey->setEnabled(mode);
    isRGBGrey->setEnabled(mode);
    isRGB_ARGB->setEnabled(mode);
}

void MenuTab::chImageMode(int mode){
    is16BitGrey->setIconVisibleInMenu(false);
    is8BitGrey->setIconVisibleInMenu(false);
    is8BitColor->setIconVisibleInMenu(false);
    isRGBGrey->setIconVisibleInMenu(false);
    isRGB_ARGB->setIconVisibleInMenu(false);
    submenuImageFormat->setEnabled(false);

    setUCharImageModeEnable(true);
    switch(mode){
        case IS_16BITIMG_GREY:
            is16BitGrey->setIcon(QIcon(trueIcon));
            is16BitGrey->setIconVisibleInMenu(true);
            setUCharImageModeEnable(false);
            break;
        case IS_8BITIMG_GREY:
            is8BitGrey->setIconVisibleInMenu(true);
            is8BitGrey->setIcon(QIcon(trueIcon));
            break;
        case IS_8BITIMG_COLOR:
            is8BitColor->setIconVisibleInMenu(true);
            is8BitColor->setIcon(QIcon(trueIcon));
            break;
        case IS_RGBIMG_GREY:
            isRGBGrey->setIconVisibleInMenu(true);
            isRGBGrey->setIcon(QIcon(trueIcon));
            break;
        case IS_RGBIMG_COLOR:
            isRGB_ARGB->setIconVisibleInMenu(true);
            isRGB_ARGB->setIcon(QIcon(trueIcon));
            submenuImageFormat->setEnabled(true);
            break;
    }
}

void MenuTab::setRealtimePause(bool val){
    if (val){
        pauseRealtime->setIcon(QIcon(trueIcon));
    }
    else{
         pauseRealtime->setIcon(QIcon(falseIcon));
    }
}

void MenuTab::setRealtimeProp(SubWindowRealtime* rt){
    setChFlipHorRealtime(rt->wgt->manip->getHorFlipVal());
    setChFlipVerRealtime(rt->wgt->manip->getVerFlipVal());
    setChServerManip(rt->serverOperation);
    setChFullPictureMode(rt->fullPictureMode);
    chImageMode(rt->wgt->imgType);
    setRealtimePause(rt->isTimeout);
}
void MenuTab::setSnapshotProp(SubWindowSnapshot* snap){
    setChFlipHorSnapshot(snap->wgt->manip->getHorFlipVal());
    setChFlipVerSnapshot(snap->wgt->manip->getVerFlipVal());
    setChFullPictureModeSnap(snap->fullPictureMode);
}

void MenuTab::setRealTimeEnable(bool val){
    realtime->setEnabled(val);
}
void MenuTab::setSnapshotEnable(bool val){
    snapshot->setEnabled(val);
}

void  MenuTab::setBGCEnable(bool val){
    setBrightnessSnapshot->setEnabled(val);
    setGammaSnapshot->setEnabled(val);
    setContrastSnapshot->setEnabled(val);
}
