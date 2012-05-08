/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

//Creating Menu
void MainWindow::createMenu(){
    server = menuBar()->addMenu(QString("&Server"));
    server->addAction(addNewDevice);
    server->addAction(setDevice);
    server->addAction(pushCommand);
    server->addSeparator();
    server->addAction(exitAct);

    snapshot = menuBar()->addMenu(tr("&Snapshot"));
    snapshot->addAction(makeSnapshot);
    snapshot->addAction(saveSnapshot);
    snapshot->addAction(scaleSnapshot);             //scale current snapshot  //not used
    snapshot->addAction(horFlipSnapshot);
    snapshot->addAction(verFlipSnapshot);
    snapshot->addAction(setBrightnessSnapshot);
    snapshot->addAction(setContrastSnapshot);
    snapshot->addAction(setGammaSnapshot);
    snapshot->addAction(setRotationSnapshot);
    snapshot->addAction(resetImgSnapshot);

    realtime = menuBar()->addMenu(tr("&Realtime"));
    realtime->addAction(scaleRealtime);
    realtime->addAction(setBrightnessRealtime);
    realtime->addAction(setContrastRealtime);
    realtime->addAction(setGammaRealtime);
    realtime->addAction(setRotationRealtime);
    realtime->addAction(horFlipRealtime);
    realtime->addAction(verFlipRealtime);
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
    realtime->addAction(resetImgRealtime);

    snapshot->setEnabled(false);
    saveSnapshot->setEnabled(false);
    pushCommand->setEnabled(false);
}

//Init Actions
void MainWindow::createActions(){
    fprintf(stderr, "!!\n");
    /*Server*/
    pushCommand = new QAction(tr("&Send a command"), this);
    pushCommand->setStatusTip(tr("Send a command"));
    connect(pushCommand, SIGNAL(triggered()), this, SLOT(setTangoCommand()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Finish working"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    addNewDevice = new QAction(tr("&Start new device"), this);
    addNewDevice->setStatusTip(tr("Start new device"));
    connect(addNewDevice, SIGNAL(triggered()), this, SLOT(setNewTangoDevice()));

    setDevice = new QAction(tr("&Set device"), this);
    setDevice->setStatusTip(tr("Set device"));
    connect(setDevice, SIGNAL(triggered()), this, SLOT(setTangoDevice()));

    /*Snapshot*/
    makeSnapshot = new QAction(tr("&Make a snapshot"), this);
    makeSnapshot->setStatusTip(tr("Create a snapshot"));

    saveSnapshot = new QAction(tr("&Save a snapshot"), this);
    saveSnapshot->setStatusTip(tr("Save a snapshot"));
    QObject::connect(saveSnapshot, SIGNAL(triggered()), this, SLOT(saveImg()));

    scaleSnapshot = new QAction(tr("&Scale Snapshot"), this);
    scaleSnapshot->setStatusTip(tr("Scale Snapshot"));
    QObject::connect(scaleSnapshot, SIGNAL(triggered()), this, SLOT(settingScaleSnapshot()));

    horFlipSnapshot = new QAction(QIcon(":/icons/false.png"), tr("&Horizontal Fliping"), this);
    horFlipSnapshot->setStatusTip(tr("Horizontal Fliping"));
    QObject::connect(horFlipSnapshot, SIGNAL(triggered()), this, SLOT(setFlipHor()));

    verFlipSnapshot = new QAction(QIcon(":/icons/false.png"), tr("&Vertical Fliping"), this);
    verFlipSnapshot->setStatusTip(tr("Vertical Fliping"));
    QObject::connect(verFlipSnapshot, SIGNAL(triggered()), this, SLOT(setFlipVer()));

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

    resetImgSnapshot =  new QAction(tr("&Reset Image"), this);
    resetImgSnapshot->setStatusTip(tr("Set Rotation"));
    QObject::connect(resetImgSnapshot, SIGNAL(triggered()), this, SLOT(setResetImgSnapshot()));

    /*Realtime*/
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

    horFlipRealtime = new QAction(QIcon(":/icons/false.png"), tr("&Horizontal Fliping"), this);
    horFlipRealtime->setStatusTip(tr("Horizontal Fliping"));
    QObject::connect(horFlipRealtime, SIGNAL(triggered()), this, SLOT(changeFlipHorRealtime()));

    verFlipRealtime = new QAction(QIcon(":/icons/false.png"), tr("&Vertical Fliping"), this);
    verFlipRealtime->setStatusTip(tr("Vertical Fliping"));
    QObject::connect(verFlipRealtime, SIGNAL(triggered()), this, SLOT(changeFlipVerRealtime()));

    resetImgRealtime = new QAction(tr("&Reset Image"), this);
    resetImgRealtime->setStatusTip(tr("Reset Image"));
    QObject::connect(resetImgRealtime, SIGNAL(triggered()), this, SLOT(setResetImgRealtime()));

   /* setImageFormatRealtime = new QAction(tr("&Set Image Format"), this);
    setImageFormatRealtime->setStatusTip(tr("Set Image Format"));;
    */
    setImageFormatIndex8 = new QAction(tr("&Index8"), this);
    setImageFormatIndex8->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatIndex8, SIGNAL(triggered()), this, SLOT(setIndex8()));

    setImageFormatRGB32 = new QAction(tr("&RGB32"), this);
    setImageFormatRGB32->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatRGB32, SIGNAL(triggered()), this, SLOT(setRGB32()));

    setImageFormatARGB32 = new QAction(tr("&ARGB32"), this);
    setImageFormatARGB32->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatARGB32, SIGNAL(triggered()), this, SLOT(setARGB32()));

    setImageFormatARGB32Pre = new QAction(tr("&ARGB32Pre"), this);
    setImageFormatARGB32Pre->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatARGB32Pre, SIGNAL(triggered()), this, SLOT(setARGB32Pre()));

    setImageFormatRGB16 = new QAction(tr("&RGB16"), this);
    setImageFormatRGB16->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatRGB16, SIGNAL(triggered()), this, SLOT(setRGB32()));

    setImageFormatARGB8565Pre = new QAction(tr("&ARGB8565Pre"), this);
    setImageFormatARGB8565Pre->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatARGB8565Pre, SIGNAL(triggered()), this, SLOT(setRGB16()));

    setImageFormatRGB666 = new QAction(tr("&RGB666"), this);
    setImageFormatRGB666->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatRGB666, SIGNAL(triggered()), this, SLOT(setRGB666()));

    setImageFormatARGB6666Pre = new QAction(tr("&ARGB666Pre"), this);
    setImageFormatARGB6666Pre->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatARGB6666Pre, SIGNAL(triggered()), this, SLOT(setARGB6666Pre()));

    setImageFormatRGB555 = new QAction(tr("&RGB555"), this);
    setImageFormatRGB555->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatRGB555, SIGNAL(triggered()), this, SLOT(setRGB555()));

    setImageFormatARGB8555Pre = new QAction(tr("&ARGB8555Pre"), this);
    setImageFormatARGB8555Pre->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatARGB8555Pre, SIGNAL(triggered()), this, SLOT(setARGB8555Pre()));

    setImageFormatRGB888 = new QAction(tr("&RGB888"), this);
    setImageFormatRGB888->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatRGB888, SIGNAL(triggered()), this, SLOT(setRGB888()));

    setImageFormatRGB444 = new QAction(tr("&RGB444"), this);
    setImageFormatRGB444->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatRGB444, SIGNAL(triggered()), this, SLOT(setRGB444()));

    setImageFormatARGB4444Pre = new QAction(tr("&ARGB4444Pre"), this);
    setImageFormatARGB4444Pre->setStatusTip(tr("Set Image Format"));
    QObject::connect(setImageFormatARGB4444Pre, SIGNAL(triggered()), this, SLOT(setARGB4444Pre()));
}

