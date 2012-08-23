#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRgb>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Image Client");
    bt = NULL; /*new QPushButton(ui->centralWidget);
           bt->setObjectName(QString::fromUtf8("bt"));
           bt->setGeometry(QRect(0, 0, 125, 24));
           bt->setText(QApplication::translate("Image Client 0.8", "Manipulator/Histogram ", 0, QApplication::UnicodeUTF8));
           QObject::connect(bt, SIGNAL(clicked()),this, SLOT(setManipulator()));
*/
           btMkSnap = NULL;/* = new QPushButton(ui->centralWidget);
           btMkSnap->setObjectName(QString::fromUtf8("btMkSnap"));
           btMkSnap->setGeometry(QRect(80, 0, 155, 24));
           btMkSnap->setText(QApplication::translate("MainWindow", "InVisiable Histogram", 0, QApplication::UnicodeUTF8));
           QObject::connect(btMkSnap, SIGNAL(clicked()), this, SLOT(InVisHistogram()));
*/
           bt16bit = NULL;// new QPushButton(ui->centralWidget);
           /*bt16bit->setObjectName(QString::fromUtf8("bt"));
           bt16bit->setGeometry(QRect(250, 0, 150, 24));
           bt16bit->setText(QApplication::translate("MainWindow", "Set 16BIT GREY MODE", 0, QApplication::UnicodeUTF8));
           QObject::connect(bt16bit, SIGNAL(clicked()),this, SLOT(SetImageMode()));//(initStartTangoWin()));
            */
    commandMenu = new MenuTab(this);
    area = new QMdiArea(this);
    area->move(0,50);
    area->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    curRealtimeInt = -1;
    realtimeIntLast = -1;
    curSnapshotInt = -1;
    startWithParams = false;
    startImageMode = NULL;
    startImageFormat = NULL;
    readSettings();


    lbMouseX = new QLabel(ui->centralWidget);
    lbMouseX->setObjectName(QString::fromUtf8("lbMouseX"));
    lbMouseX->setGeometry(QRect(0, 0, 75, 24));
    lbMouseY = new QLabel(ui->centralWidget);
    lbMouseY->setObjectName(QString::fromUtf8("lbMouseY"));
    lbMouseY->setGeometry(QRect(50, 0, 75, 24));
    lbPixVal = new QLabel(ui->centralWidget);
    lbPixVal->setObjectName(QString::fromUtf8("lbPixVal"));
    lbPixVal->setGeometry(QRect(150, 0, 175, 24));
    lbMarker = new QLabel(ui->centralWidget);
    lbMarker->setObjectName(QString::fromUtf8("lbarker"));
    lbMarker->setGeometry(QRect(290, 0, 175, 24));

    slider = NULL;
    manip_wgt = NULL;
    marker = NULL;
    histogramManip = false;
}

void MainWindow::setManipulator(){
    if (!histogramManip){
        deleteManipulatorWGT();
    }
    else{
        deletePropertyValues();
    }
    histogramManip = !histogramManip;
}

void MainWindow::setLeftBorder(unsigned short val){
    if (curRealtimeInt != -1){
        listReal.at(curRealtimeInt)->wgt->picMode->setLBorder(val);
    }
}

void MainWindow::setRightBorder(unsigned short val){
    if (curRealtimeInt != -1){
        listReal.at(curRealtimeInt)->wgt->picMode->setRBorder(val);
    }
}

void MainWindow::setLeftBorderSnp(unsigned short val){
    if (curSnapshotInt != -1){
        listSnap.at(curSnapshotInt)->wgt->picMode->setLBorder(val);
        listSnap.at(curSnapshotInt)->wgt->calcGreyImg();
    }
}

void MainWindow::setRightBorderSnp(unsigned short val){
    if (curSnapshotInt != -1){
        listSnap.at(curSnapshotInt)->wgt->picMode->setRBorder(val);
        listSnap.at(curSnapshotInt)->wgt->calcGreyImg();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete commandMenu;
    delete area;
    delete btMkSnap;
    delete bt;
    delete bt16bit;
    delete lbMouseX;
    delete lbMouseY;
    delete lbPixVal;
    delete lbMarker;


    delete slider;
    slider = NULL;
    delete manip_wgt;
    manip_wgt =NULL;
}

void MainWindow::deleteAllSnap(){
    if (listSnap.count() !=0 ){
        int i;
        for (i=0; i<listSnap.count(); i++){
            qDebug("Close MAinWin : close Snapshot");
            curSnapshotInt = -1;
            delete listSnap[i];
        }
    }
}

void MainWindow::deleteAllReal(){
    if  (listReal.count() != 0){
        int i;
        for (i=0; i<listReal.count(); i++){
            qDebug("Close MAinWin : close realtime");
            listReal.at(i)->work = false;
            threads.at(i)->exit();
            realtimeIntLast = -1;
            listReal[i]->deleteLater();
        }
      }
}

void MainWindow::closeEvent ( QCloseEvent * closeEvent){
    qDebug("CLOSE MAIN_WIN");
    deleteAllSnap();
    deleteAllReal();
    delMarkerWin();

    delete slider;
    slider = NULL;
    delete manip_wgt;
    manip_wgt =NULL;
    writeSettings();
    QMainWindow::closeEvent(closeEvent);
}

int MainWindow::getBGCPL_WGT_MODE(int mode){
    if (mode == IS_8BITIMG_COLOR || mode == IS_RGBIMG_COLOR || IS_16BITIMG_RGB){  /*IS_16BITIMG_RGB temparary here*/
        mode = IS_COLOR_MODE;
    }
    else if(mode == IS_8BITIMG_GREY || mode == IS_RGBIMG_GREY){
        mode = IS_8BITGREY_MODE;
    }
    else{
        mode = IS_16BITGREY_MODE;
    }
    return mode;
}
void MainWindow::deleteManipulatorWGT(){
    manip_wgt->deleteLater();
    manip_wgt = NULL;
}

void MainWindow::setManipulatorWGT(SubWindow *subW){
    ImageWidget *wgt = subW->wgt;
    int mode = getBGCPL_WGT_MODE(wgt->picMode->getPictureMode());
    manip_wgt = new Manipulator(mode, wgt->manip->listProp, wgt->picMode);//, this);
    setManipConnects(subW, mode);
    connect(manip_wgt, SIGNAL(showhistogram()), this, SLOT(setManipulator()));
    manip_wgt->setWindowModality(Qt::WindowModal);
    manip_wgt->show();
}

void MainWindow::setMarkerPos(){
    marker = new SetMarker();
    connect(marker, SIGNAL(setMarker(int,int)), this, SLOT(createMarker(int,int)));
    marker->setWindowModality(Qt::WindowModal);
    //marker->setAttribute(Qt::WA_DeleteOnClose);
    connect(marker, SIGNAL(cancel()), this, SLOT(delMarkerWin()));
    marker->show();
}

void MainWindow::delMarkerWin(){
   // marker->close();
    delete marker;
    marker = NULL;
}


void MainWindow::createMarker(int X,int Y){
    listReal.at(realtimeIntLast)->wgt->convertPosFromImageSize(X, Y);
    listReal.at(realtimeIntLast)->wgt->_curMouseX = floor(X * listReal.at(realtimeIntLast)->wgt->manip->listProp.at(SCALE)->getValue().toDouble());
    listReal.at(realtimeIntLast)->wgt->_curMouseY = floor(Y * listReal.at(realtimeIntLast)->wgt->manip->listProp.at(SCALE)->getValue().toDouble());
    listReal.at(realtimeIntLast)->wgt->allowNewMarker();
}

void MainWindow::connectPropertyValues(SubWindow* subW){
    ImageWidget *wgt = subW->wgt;
    int mode = getBGCPL_WGT_MODE(wgt->picMode->getPictureMode());
    slider = new SliderManip(mode, wgt->manip->listProp, wgt->picMode, wgt->img, wgt->valUSh);//, this);
    setSliderConnects(subW, mode);
    connect(slider, SIGNAL(hidehistogram()), this, SLOT(setManipulator()));
    slider->setWindowModality(Qt::WindowModal);
    slider->show();
}

void MainWindow::deletePropertyValues(){
    slider->deleteLater();
    slider = NULL;
}

void MainWindow::setManipConnects(SubWindow *subW, int mode){
    ImgManipulation *manip = subW->wgt->manip;
    if (mode != IS_COLOR_MODE){
        connect(manip_wgt->bgcpl, SIGNAL(setLBorder(unsigned short)), this, SLOT(setLeftBorder(unsigned short)));
        connect(manip_wgt->bgcpl, SIGNAL(setRBorder(unsigned short)), this, SLOT(setRightBorder(unsigned short)));
    }
    connect(manip_wgt->bgcpl, SIGNAL(setGm(QVariant)), manip->listProp.at(GAMMA), SLOT(setValue(QVariant)));
    connect(manip_wgt->bgcpl, SIGNAL(setBr(QVariant)), manip->listProp.at(BRIGHTNESS), SLOT(setValue(QVariant)));
    connect(manip_wgt->bgcpl, SIGNAL(setCon(QVariant)), manip->listProp.at(CONTRAST), SLOT(setValue(QVariant)));
    connect(manip_wgt->rsfl, SIGNAL(sendHorFlipVal(QVariant)), manip->listProp.at(HOR_FLIP), SLOT(setValue(QVariant)));
    connect(manip_wgt->rsfl, SIGNAL(sendVerFlipVal(QVariant)), manip->listProp.at(VER_FLIP), SLOT(setValue(QVariant)));
    connect(manip_wgt->rsfl->scale, SIGNAL(sendVal(QVariant)), manip->listProp.at(SCALE), SLOT(setValue(QVariant)));
    connect(manip_wgt->rsfl, SIGNAL(sendRotationVal(QVariant)), manip->listProp.at(ROTATION), SLOT(setValue(QVariant)));

    connect(subW->wgt, SIGNAL(sendScale (QVariant)), manip_wgt->rsfl->scale, SLOT(receiveVal(QVariant)));
}

void MainWindow::setSliderConnects(SubWindow*subW, int mode){
    ImgManipulation *manip = subW->wgt->manip;
    connect(subW, SIGNAL(newPicture()), slider, SLOT(recalcHistogram()));
    connect(subW, SIGNAL(send16BitData(vector<unsigned short>)), slider, SLOT(recalcHistogram16Bit(vector<unsigned short>)));
    connect(subW, SIGNAL(send16BitDataDirect(vector<unsigned short>)), slider, SLOT(get16BitData(vector<unsigned short>)));
    connect(slider, SIGNAL(get16Bit()), subW, SLOT(send16BitDataSlot()));
    if (mode != IS_COLOR_MODE){
        connect(slider->bgcpl, SIGNAL(setLBorder(unsigned short)), this, SLOT(setLeftBorder(unsigned short)));
        connect(slider->bgcpl, SIGNAL(setRBorder(unsigned short)), this, SLOT(setRightBorder(unsigned short)));
    }
    connect(slider->bgcpl, SIGNAL(setGm(QVariant)), manip->listProp.at(GAMMA), SLOT(setValue(QVariant)));
    connect(slider->bgcpl, SIGNAL(setBr(QVariant)), manip->listProp.at(BRIGHTNESS), SLOT(setValue(QVariant)));
    connect(slider->bgcpl, SIGNAL(setCon(QVariant)), manip->listProp.at(CONTRAST), SLOT(setValue(QVariant)));
    connect(slider->rsfl, SIGNAL(sendHorFlipVal(QVariant)), manip->listProp.at(HOR_FLIP), SLOT(setValue(QVariant)));
    connect(slider->rsfl, SIGNAL(sendVerFlipVal(QVariant)), manip->listProp.at(VER_FLIP), SLOT(setValue(QVariant)));
    connect(slider->rsfl->scale, SIGNAL(sendVal(QVariant)), manip->listProp.at(SCALE), SLOT(setValue(QVariant)));
    connect(slider->rsfl, SIGNAL(sendRotationVal(QVariant)), manip->listProp.at(ROTATION), SLOT(setValue(QVariant)));

    connect(subW->wgt, SIGNAL(sendScale (QVariant)), slider->rsfl->scale, SLOT(receiveVal(QVariant)));
}
void MainWindow::reSetMarkerPos(SubWindow *subWin){  //////set into imagewidget
    if (subWin->wgt->isMarked){
        int X = subWin->wgt->_clickedMouseX, Y=subWin->wgt->_clickedMouseY;
        QString str = QString("Marker: X=" + QString().number(int(X)) + ";Y=" + QString().number(int(Y)));
        setMarker(str);
    }
    else {
        setMarker("");
    }
}
void MainWindow::setSlider(SubWindow* subW){
    int mode = getBGCPL_WGT_MODE(subW->wgt->picMode->getPictureMode());
    if (!slider)
        connectPropertyValues(subW); //curRealtimeInt can be -1 becouse was open only manipulator
    else{
        slider->changeDevice(mode, subW->wgt->manip->listProp, subW->wgt->picMode, subW->wgt->img, subW->wgt->valUSh);
        setSliderConnects(subW, mode);
    }
}

void MainWindow::setManip_wgt(SubWindow* subW){
    int mode = getBGCPL_WGT_MODE(subW->wgt->picMode->getPictureMode());
    if (!manip_wgt)
        setManipulatorWGT(subW);
    else{
        manip_wgt->changeDevice(mode, subW->wgt->manip->listProp, subW->wgt->picMode);
        setManipConnects(subW,mode);
    }
}

void MainWindow::setManipulatorReal(){
    chManipulator(listReal.at(realtimeIntLast));
}

void MainWindow::setManipulatorSnap(){
    chManipulator(listSnap.at(curSnapshotInt));
}

void MainWindow::chManipulator(SubWindow* subW){
    if (histogramManip){
        setSlider(subW);
    }
    else{
        setManip_wgt(subW);
    }
}

void MainWindow::realtimeChanged(SubWindowRealtime* curRealtimeWin){
    qDebug("MainWindow::realtimeChanged");
    if(curRealtimeWin){             //if realtimewindow active
        QList<SubWindowRealtime*>::iterator iter;
        int  i = 0;
        for (iter = listReal.begin(); iter < listReal.end(); ++iter){
            if(curRealtimeWin == *iter){                             /*Find current window in list of realtime windows*/
                qDebug("MainWindow::realtimeChanged!!!!");
                curRealtimeInt = listReal.indexOf(curRealtimeWin);
                realtimeIntLast = curRealtimeInt;
                commandMenu->setRealTimeEnable(true);
                commandMenu->setRealtimeProp(curRealtimeWin);

                listReal.at(curRealtimeInt)->myDev->pingTimer.stop();
                qDebug("Attention, realtimeChanged pingTimer STOPED");
                listReal.at(curRealtimeInt)->setPause(false);  //to allow realTime
                listReal.at(curRealtimeInt)->sendingPing();     //Start timer

                chManipulator(listReal.at(realtimeIntLast));
                reSetMarkerPos(listReal.at(realtimeIntLast));
                break;
                }
            i++;
        }
    }
    else{
        if (curRealtimeInt != -1){
            listReal.at(curRealtimeInt)->myDev->startWorkWithTime();
            qDebug("Attention, realtimeChanged pingTimer STARTED");
            listReal.at(curRealtimeInt)->setPause(true);
            curRealtimeInt = -1;
            commandMenu->setRealTimeEnable(false);
        }
        else{
            qDebug("Error, don't understandabl error MainWindow::realtimeChanged");
        }
    }
}

void MainWindow::SnapshotChanged(SubWindowSnapshot* curSnapWin){
    qDebug("MainWindow::SnapshotChanged");
    if(curSnapWin){
        QList<SubWindowSnapshot*>::iterator iter;
        int  i = 0;
        for (iter = listSnap.begin(); iter < listSnap.end(); ++iter){
            if(curSnapWin == *iter){                            /*Find current window in list of snapshot windows*/
                qDebug("MainWindow::SnapshotChanged!!!!");
                curSnapshotInt = listSnap.indexOf(curSnapWin);
                curSnapshotIntLast = curSnapshotInt;
                commandMenu->snapshot->setEnabled(true);
                commandMenu->setSnapshotProp(curSnapWin);

                if (realtimeIntLast != -1){
                    if (listReal.at(realtimeIntLast)->myDev){
                        listReal.at(realtimeIntLast)->myDev->pingTimer.stop();
                        qDebug("Attention, SnapshotChanged pingTimer STOPED");
                    }
                    else {
                        qDebug("Error, MainWindow::SnapshotChanged listReal.at(realtimeIntLast)->myDev = NULL");
                    }
                    listReal.at(realtimeIntLast)->setPause(false);  //to allow realTime
                    listReal.at(realtimeIntLast)->sendingPing();
                }
                chManipulator(listSnap.at(curSnapshotIntLast));
                reSetMarkerPos(listSnap.at(curSnapshotIntLast));
                break;
            }
            i++;
        }
    }
    else{
        curSnapshotInt = -1;
        commandMenu->snapshot->setEnabled(false);
    }
}

void MainWindow::resizeEvent(QResizeEvent *e ){
    QSize s = e->size();
    area->resize(s.width(), s.height()-70);   //-120 to statusTip
}

void MainWindow::settingBrightness(){
    initTangoSettingWin(BRIGHTNESS);
}
void MainWindow::settingContrast(){
    initTangoSettingWin(CONTRAST);
}
void MainWindow::settingGamma(){
    initTangoSettingWin(GAMMA);
}
void MainWindow::settingRotation(){
    initTangoSettingWin(ROTATION);
}
void MainWindow::settingScale(){
    initTangoSettingWin(SCALE);
}
void MainWindow::chBrightnessOn(){
    initTangoSettingWin(BRIGHTNESS_CH_ON);
}
void MainWindow::chContrastOn(){
    initTangoSettingWin(CONTRAST_CH_ON);
}
void MainWindow::chGammaOn(){
    initTangoSettingWin(GAMMA_CH_ON);
}
void MainWindow::chRotationOn(){
    initTangoSettingWin(ROTATION_CH_ON);
}
void MainWindow::chScaleOn(){
    initTangoSettingWin(SCALE_CH_ON);
}
void MainWindow::settingHorFlip(){
    initTangoSettingWin(HOR_FLIP);
}
void MainWindow::settingVerFlip(){
    initTangoSettingWin(VER_FLIP);
}
void MainWindow::sendingTangoCommand(){
    initTangoSettingWin(TANGO_COM);
}

void MainWindow::settingTimeOut(){
    initTangoSettingWin(REALTIMETIMEOUT);
}

QString MainWindow::setTitlePrefix(int &curSubwindow){
    QString text = "";
    if(curRealtimeInt == -1){
        text = " Snapshot";
        curSubwindow = curSnapshotInt;
    }
    else{
        curSubwindow = curRealtimeInt;  //set index of Subwindow
        if (listReal.at(curRealtimeInt)->serverOperation)
            text = " RealTime (server)";
        else
            text = " RealTime (client)";
    }
    return text;
}

void MainWindow::connectManipulation(int opt){
    if (tangoDevSet && slider){
        switch(opt){
            case ROTATION:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->rsfl->rotation, SLOT(receiveVal(QVariant)));
            break;
            case SCALE:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->rsfl->scale, SLOT(receiveVal(QVariant)));
            break;
            case BRIGHTNESS:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->bgcpl, SLOT(receiveBr(QVariant)));
            break;
            case GAMMA:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->bgcpl, SLOT(receiveGm(QVariant)));
            break;
            case CONTRAST:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->bgcpl, SLOT(receiveCon(QVariant)));
            break;
            case HOR_FLIP:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->rsfl->hFl, SLOT(receiveVal(QVariant)));
            break;
            case VER_FLIP:
                QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), slider->rsfl->vFl, SLOT(receiveVal(QVariant)));
            break;
        }
    }
}
void MainWindow::initTangoSettingWin(int param){
    QString title = "????";
    QString prefix;
    int curSubwindow;
    prefix = setTitlePrefix(curSubwindow); //set index of Subwindow
    if (param == TANGO_COM){
        if (curRealtimeInt == -1){ //Snapshot
            qDebug("Error, Incorrect curRealtimeInt Value in tango Command");
        }
        else{
            title ="Send Tango Command " + prefix;
            tangoDevSet = new TangoSettingsWin(param, title, "Command", "Command");
            QObject::connect(tangoDevSet, SIGNAL(settingChangedS(QString)), listReal.at(curSubwindow), SLOT(sendTangoCommand(QString)));
        }
    }
    else if (param == REALTIMETIMEOUT){
        if (curRealtimeInt != -1){ //Realtime
            title = "Set Delay for Realtime";
            tangoDevSet = new TangoSettingsWin(param, title, "Timeout", 50);
            QObject::connect(tangoDevSet, SIGNAL(settingChangedI(int)), listReal.at(curRealtimeInt), SLOT(setTimeOutVal(int)));
        }
        else{
            qDebug("Erorr, REALTIMETIMEOUT curRealtimeInt shouldn't be -1");
        }
    }
    else{
        int opt = param;
        if(param >= BRIGHTNESS && param<=VER_FLIP)
            title = "Set " + listReal.at(curSubwindow)->wgt->manip->listProp.at(opt)->getPropName() +   prefix;
        else{
            opt = param-BRIGHTNESS_CH_ON;
            title = "Change " + listReal.at(curSubwindow)->wgt->manip->listProp.at(opt)->getPropName() +   prefix + " On";
        }
        tangoDevSet = new TangoSettingsWin(param, title, listReal.at(curSubwindow)->wgt->manip->listProp.at(opt)->getPropName(),
                                                  listReal.at(curSubwindow)->wgt->manip->listProp.at(param)->getValue());
        if (!listReal.at(curSubwindow)->serverOperation)
            QObject::connect(tangoDevSet, SIGNAL(settingChanged(QVariant)), listReal.at(curSubwindow)->wgt->manip->listProp.at(opt), SLOT(setValue(QVariant)));
        else{
            switch(opt){
                case BRIGHTNESS: QObject::connect(tangoDevSet, SIGNAL(settingChangedI(int)), listReal.at(curSubwindow), SLOT(setBrightness(int))); break;
                case CONTRAST: QObject::connect(tangoDevSet, SIGNAL(settingChangedI(int)), listReal.at(curSubwindow), SLOT(setContrast(int))); break;
                case GAMMA: QObject::connect(tangoDevSet, SIGNAL(settingChangedI(int)), listReal.at(curSubwindow), SLOT(setGamma(int))); break;
                case ROTATION: QObject::connect(tangoDevSet, SIGNAL(settingChangedD(double)), listReal.at(curSubwindow), SLOT(setRotation(double))); break;
                case SCALE: QObject::connect(tangoDevSet, SIGNAL(settingChangedD(double)), listReal.at(curSubwindow), SLOT(setScale(double))); break;
                case HOR_FLIP: QObject::connect(tangoDevSet, SIGNAL(settingChangedS(QString)), listReal.at(curSubwindow), SLOT(setHorFlipValue(QString))); break;
                case VER_FLIP: QObject::connect(tangoDevSet, SIGNAL(settingChangedS(QString)), listReal.at(curSubwindow), SLOT(setVerFlipValue(QString))); break;
            }
        }
        if(slider){
            connectManipulation(opt);
        }
    }
    tangoDevSet->setWindowModality(Qt::ApplicationModal);
    tangoDevSet->setAttribute(Qt::WA_DeleteOnClose);  //!!!!!!!!! use upper IF to delete object!!!!!!!!!!!!!!!!!!!!!!!!!
    QObject::connect(tangoDevSet, SIGNAL(cancel()), this, SLOT(delTangoSettingWin()));
    tangoDevSet->show();
}

void MainWindow::delTangoSettingWin(){
    tangoDevSet->close();
    delete tangoDevSet;
    tangoDevSet = NULL;
}

void MainWindow::setStartImgModeAndFormat(){
    if(startWithParams){
        if(startImageMode && *startImageMode != -1){
            switch(*startImageMode){
                case 0: set16BitGreyImageMode(); break;
                case 1: setRGBGreyImageMode();  break;
                case 2: setRGB_ARGBImageMode(); break;
                case 3: set8BitGreyImageMode(); break;
                case 4: set8BitColorImageMode(); break;
                case 5: set16BitRGBImageMode(); break;
            }
        }
        if(startImageFormat && *startImageFormat != -1){
            switch(*startImageFormat){
                case 3: setIndex8(); break;
                case 4: setRGB32(); break;
                case 5: setARGB32(); break;
                case 6: setARGB32Pre(); break;
                case 7: setRGB16(); break;
                case 8: setARGB8565Pre(); break;
                case 9: setRGB666(); break;
                case 10: setARGB6666Pre(); break;
                case 11: setRGB555(); break;
                case 12: setARGB8555Pre(); break;
                case 13: setRGB888(); break;
                case 14: setRGB444(); break;
                case 15: setARGB4444Pre(); break;
            }
        }
        startWithParams = false;
        delete startImageMode;
        delete startImageFormat;
    }
}

void MainWindow::delStartTangoWin(){
    setStartImgModeAndFormat();
    tangoDev->close();
    delete tangoDev;
    tangoDev = NULL;
}


void MainWindow::initStartTangoWin(){
    tangoDev = new StartTangoWin(this);
    tangoDev->setWindowModality(Qt::ApplicationModal);
    tangoDev->setAttribute(Qt::WA_DeleteOnClose);  //!!!!!!!!! use upper IF to delete object!!!!!!!!!!!!!!!!!!!!!!!!!
    QObject::connect(tangoDev, SIGNAL(cancel()), this, SLOT(delStartTangoWin()));
    QObject::connect(tangoDev, SIGNAL(correctDev(QString, QString)), this, SLOT(mkRealtime( QString, QString )));
    tangoDev->show();
}

void MainWindow::initTangoNamesWin(){
    tangoVar = new TangoVariables(this);
    tangoVar->setWindowModality(Qt::ApplicationModal);
    tangoVar->setAttribute(Qt::WA_DeleteOnClose);  //!!!!!!!!! use upper IF to delete object!!!!!!!!!!!!!!!!!!!!!!!!!
    QObject::connect(tangoVar, SIGNAL(cancel()), this, SLOT(delTangoNamesWin()));
    QObject::connect(tangoVar, SIGNAL(setVar(QStringList)), this, SLOT(setTangoVar(QStringList)));
    tangoVar->show();
}
void MainWindow::delTangoNamesWin(){
    tangoVar->close();
    delete tangoVar;
    tangoVar = NULL;
}

void MainWindow::setTangoVar(QStringList ls){
    if (curRealtimeInt != -1){
        listReal.at(curRealtimeInt)->myDev->setAttrNames(ls);
    }
    else
        qDebug("Error, MainWindow::setTangoVar");
}

QList<QAction*>  MainWindow::realtimeMenu(){
    QList<QAction*> ls;
    ls.push_back(commandMenu->fullPictureMode);
    ls.push_back(QMenu().addMenu(commandMenu->setImageMode));
    ls.push_back(QMenu().addMenu(commandMenu->setValRealtime));
    return ls;
}

void MainWindow::mkRealtime( QString servName, QString imgAtr ){
    area->hide();
   // delStartTangoWin();
    SubWindowRealtime *  curRealtimePointer = new SubWindowRealtime(servName, imgAtr);

    curRealtimePointer->setActionMenu(realtimeMenu());
    curRealtimePointer->resize(800,area->height()-25);
    QObject::connect(curRealtimePointer, SIGNAL(closeRealtime(SubWindowRealtime*)), this, SLOT(onCloseRaltime(SubWindowRealtime*)));
  //  QObject::connect(curRealtimePointer->wgt, SIGNAL(mkSnapshotRealtime(ImageWidget*)), this, SLOT(mkSnapshot(ImageWidget*)));
    QObject::connect(curRealtimePointer, SIGNAL(realtimeWinChanged(SubWindowRealtime*)), this, SLOT(realtimeChanged(SubWindowRealtime*)));
    listReal<<curRealtimePointer;
    curRealtimeInt = 0;
    delStartTangoWin();
    QObject::connect(curRealtimePointer, SIGNAL(DisplayModeChanged()), this, SLOT(setManipulatorReal()));
    area->addSubWindow(curRealtimePointer);

    MyThread *thr = new MyThread();
    QObject::connect(thr, SIGNAL(paint()), curRealtimePointer, SLOT(sendingPing()), Qt::QueuedConnection);
    QObject::connect(curRealtimePointer, SIGNAL(ping()), thr, SLOT(doTheWork()));

    QObject::connect(curRealtimePointer, SIGNAL(isUShortData()), this, SLOT(set16BitGreyImageMode()));
    QObject::connect(curRealtimePointer, SIGNAL(isUCharData()), this, SLOT(setRGB_ARGBImageMode()));

    connectSubwindowSignals(curRealtimePointer);
    QObject::connect(curRealtimePointer, SIGNAL(fullPictureModeChanged(SubWindow*)), this, SLOT(connectSubwindowSignals(SubWindow*)));

    thr->start();
    threads<<thr;
    commandMenu->realtime->setEnabled(true);
    area->show();
}

QList<QAction*>  MainWindow::snapshotMenu(){
    QList<QAction*> ls;
    ls.push_back(QMenu().addMenu(commandMenu->setValSnapshot));
    ls.push_back(commandMenu->saveSnapshot);
    ls.push_back(commandMenu->printSnapshot);
    ls.push_back(commandMenu->fullPictureModeSnap);
    return ls;
}

void MainWindow::mkSnapshot(ImageWidget* image, double difHW){
    qDebug("in making new SubWindowSnapshot throw ImageWidget*");
    SubWindowSnapshot *curSnapshotPointer = new SubWindowSnapshot(image->img, image->manip, difHW, image->manip->listProp.at(SCALE)->getValue().toDouble());
    QObject::connect(curSnapshotPointer, SIGNAL(SnapshotWinChanged(SubWindowSnapshot*)), this, SLOT(SnapshotChanged(SubWindowSnapshot*)));
    QObject::connect(curSnapshotPointer, SIGNAL(closeSnap(SubWindowSnapshot*)), this, SLOT(onCloseSnapshot(SubWindowSnapshot*)));
    curSnapshotPointer->setImageMode(image->imgType);
    listSnap<<curSnapshotPointer;
    curSnapshotPointer->setActionMenu(snapshotMenu());    
    QObject::connect(curSnapshotPointer, SIGNAL(DisplayModeChanged()), this, SLOT(setManipulatorSnap()));
    area->hide();
    area->addSubWindow(curSnapshotPointer);
    area->show();
    if (image->valUSh.size() !=0)
        for (int i = 0; i< image->valUSh.size(); i++){
            curSnapshotPointer->wgt->valUSh.push_back(image->valUSh[i]);
        }
   curSnapshotPointer->wgt->setPicSize(image->ImgDimX, image->ImgDimY);
   curSnapshotPointer->wgt->setPicSetings(image->img->width(), image->img->height());
   curSnapshotPointer->wgt->scaled = image->manip->listProp.at(SCALE)->getValue().toDouble();
   // curSnapshotPointer->wgt->imgType = image->imgType;  //not commented if setImageMode not work correct

    if (image->imgType == IS_16BITIMG_GREY){
        commandMenu->setBGCEnable(false);
    }
    else{
        commandMenu->setBGCEnable(true);
    }
    connectSubwindowSignals(curSnapshotPointer);
    QObject::connect(curSnapshotPointer, SIGNAL(fullPictureModeChanged(SubWindow*)), this, SLOT(connectSubwindowSignals(SubWindow*)));
}

void MainWindow::connectSubwindowSignals(SubWindow *subWin){
    QObject::connect(subWin->wgt, SIGNAL(mousePosition(int,int)), this, SLOT(setMousePos(int,int)));
    QObject::connect(subWin->wgt, SIGNAL(mousePositionVal(int,int)), this, SLOT(setGreylbVal(int,int)));
    QObject::connect(subWin->wgt, SIGNAL(mousePositionVal(int)), this, SLOT(setGreylbVal(int)));
    QObject::connect(subWin->wgt, SIGNAL(mousePositionVal(int,int,int)), this, SLOT(setRGBlbVal(int,int,int)));

    QObject::connect(subWin->wgt, SIGNAL(sendMarker(QString)), this, SLOT(setMarker(QString)));
}

double MainWindow::isFullPicReal(){
    if (listReal.at(curRealtimeInt)->difLevelPers)
        return *listReal.at(curRealtimeInt)->difLevelPers;
    else
        return 0;
}

void MainWindow::mkSnapshot(){
    qDebug() << "mksnapshot: " << QThread::currentThread();
    if (curRealtimeInt != -1){
        qDebug("in calling new SubWindowSnapshot");
         mkSnapshot(listReal.at(curRealtimeInt)->wgt, isFullPicReal() );
         commandMenu->setSnapshotEnable(true);
    }
    else{
        qDebug("Error, curRealtime not inited for making Snapshot");
    }
}

void MainWindow::onCloseRaltime(SubWindowRealtime *pointer){
    qDebug("ERase Realsubwin");
    QList<SubWindowRealtime*>::iterator iter;
    for (iter = listReal.begin(); iter < listReal.end(); ++iter){
         if(pointer == *iter){
            threads.at(listReal.indexOf(pointer))->exit();
            listReal.erase(iter);
            break;
        }
    }
    if (listReal.count() == 0){
        commandMenu->setRealTimeEnable(false);
        curRealtimeInt = -1;
        realtimeIntLast = -1;
    }
}
void MainWindow::onCloseSnapshot(SubWindowSnapshot *pointer){
    qDebug("ERase Snapsubwin");
    QList<SubWindowSnapshot*>::iterator iter;
    for (iter = listSnap.begin(); iter < listSnap.end(); ++iter){
         if(pointer == *iter){
            listSnap.erase(iter);
            break;
        }
    }
    if (listSnap.count() == 0){
        commandMenu->snapshot->setEnabled(false);
        curSnapshotInt = -1;
    }
}

void MainWindow::saveImg(){
    if (curSnapshotInt != -1)
        listSnap.at(curSnapshotInt)->wgt->saveImg();
    else{
        qDebug("Error, Incorect value of snapshot while saveImg");
    }
}

void MainWindow::printSnap(){
    if (curSnapshotInt != -1)
        listSnap.at(curSnapshotInt)->wgt->printImg();
    else{
        qDebug("Error, Incorect value of snapshot while saveImg");
    }
}

void MainWindow::chServerManipulation(){
    if (curRealtimeInt != -1){
        listReal.at(curRealtimeInt)->chServerOperation();
        commandMenu->setRealtimeProp(listReal.at(curRealtimeInt));
    }
    else{
        qDebug("Error, Incorect value of Realtime while chServerManipulation");
    }
}

void MainWindow::resetImg(){
    if (curRealtimeInt != -1)
        listReal.at(curRealtimeInt)->resetImg();
    else{
        listSnap.at(curSnapshotInt)->resetImg();
    }
}

void MainWindow::changeColorFormat(int val){
    if (curRealtimeInt != -1)
        listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(val);
    else{
        qDebug("Error, Incorect value of Realtime while changeColorFormat");
    }
}

void MainWindow::setRGBlbVal(int r=0, int g=0, int b=0){
    lbPixVal->setText("R("+ QString::number(r)+")G("+ QString::number(g)+")B("+ QString::number(b)+")");
}
void MainWindow::setGreylbVal(int RGB, int val){
    lbPixVal->setText("RGB("+QString::number(RGB)+")Grey("+QString::number(val)+")");
}
void MainWindow::setGreylbVal(int RGB){
    lbPixVal->setText("RGB("+QString::number(RGB)+")");
}
void MainWindow::setMouseXlbVal(int x){
    lbMouseX->setText("X="+QString::number(x));
}
void MainWindow::setMouseYlbVal(int y){
    lbMouseY->setText("Y="+QString::number(y));
}
void MainWindow::setMousePos(int x, int y){
    setMouseXlbVal(x);
    setMouseYlbVal(y);
}

void MainWindow::setImageMode(int mode){
    if (curRealtimeInt != -1){
        listReal.at(curRealtimeInt)->setImageMode(mode);
        commandMenu->chImageMode(mode);
        chManipulator(listReal.at(curRealtimeInt));
    }
}
void MainWindow::set16BitGreyImageMode(){
    setImageMode(IS_16BITIMG_GREY);
}
void MainWindow::set16BitRGBImageMode(){
    setImageMode(IS_16BITIMG_RGB);
}
void MainWindow::set8BitGreyImageMode(){
    setImageMode(IS_8BITIMG_GREY);
}
void MainWindow::set8BitColorImageMode(){
    setImageMode(IS_8BITIMG_COLOR);
}

void MainWindow::setRGB_ARGBImageMode(){
    setImageMode(IS_RGBIMG_COLOR);
}

void MainWindow::setRGBGreyImageMode(){
    int delim = listReal.at(curRealtimeInt)->wgt->picMode->getDelimitr();
    setImageMode(IS_RGBIMG_GREY);
    listReal.at(curRealtimeInt)->wgt->picMode->lastDelimetr = delim;
}

void MainWindow::setFullPictureMode(SubWindow* subW){
    if(subW->fullPictureMode){
        subW->setFullPictureMode(false);
        commandMenu->setChFullPictureMode(false);
    }
    else{
        subW->setFullPictureMode(true);
        commandMenu->setChFullPictureMode(true);
    }
}

void MainWindow::setFullPictureMode(){
    if (curRealtimeInt != -1 && listReal.at(curRealtimeInt)->isCanBeClosed()){
        setFullPictureMode(listReal.at(curRealtimeInt));
    }
}

void MainWindow::setFullPictureModeSnap(){
    if (curSnapshotInt != -1){
        setFullPictureMode(listSnap.at(curSnapshotInt));
    }
}

void MainWindow::setRealtimePause(){
    if (curRealtimeInt != -1){
        if(listReal.at(curRealtimeInt)->isTimeout){
            listReal.at(curRealtimeInt)->setTimeOut(false);
            commandMenu->setRealtimePause(false);
        }
        else{
            listReal.at(curRealtimeInt)->setTimeOut(true);
            commandMenu->setRealtimePause(true);
        }
    }
}

void MainWindow::readSettings(){
    QSettings settings("Vasil","imageClient");
    QSize winSize = settings.value("MainWinSize", QSize(800,500)).toSize();
    resize(winSize);
}

void MainWindow::writeSettings(){
    QSettings settings("Vasil","imageClient");
    settings.setValue("MainWinSize", QSize(width(), height()));
}



void MainWindow::setIndex8(){
     listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_Indexed8);
}

void MainWindow::setRGB32(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_RGB32);
}

void MainWindow::setARGB32(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_ARGB32);
}

void MainWindow::setARGB32Pre(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_ARGB32_Premultiplied);
}
void MainWindow::setRGB16(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_RGB16);
}
void MainWindow::setARGB8565Pre(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_ARGB8565_Premultiplied);
}
void MainWindow::setRGB666(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_RGB666);
}
void MainWindow::setARGB6666Pre(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_ARGB6666_Premultiplied);
}
void MainWindow::setRGB555(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_RGB555);
}
void MainWindow::setARGB8555Pre(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_ARGB8555_Premultiplied);
}
void MainWindow::setRGB888(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_RGB888);
}
void MainWindow::setRGB444(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_RGB444);
}
void MainWindow::setARGB4444Pre(){
    listReal.at(curRealtimeInt)->wgt->picMode->changeColorFormat(QImage::Format_ARGB4444_Premultiplied);
}

void MainWindow::setMarker(QString str){
    lbMarker->setText(str);
    lbMarker->setStatusTip("Value can be near if image scaled");
}
