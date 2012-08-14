#include "subwindowrealtime.h"
#include <QTime>
#include <QDebug>
#include <QThread>
#include <QCloseEvent>

SubWindowRealtime::SubWindowRealtime(QString serv, QString attr){
 //  _widgetLayout = new QHBoxLayout();
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    _canBeClosed = true;
    set1 = NULL;
    set2 = NULL;
    set3 = NULL;
    set4 = NULL;
    set5 = NULL;
    fullPictureMode = true;

    dimX = dimY = 0;
    difLevelPers = NULL;
    isResized= true;

    initMyDev(serv, attr);
    initFullPicMode();
    setAutoFillBackground(true);
    board->setAutoFillBackground(true);
    serverOperation = false;
    qDebug("in SubWindowRealtime constructor");


    setClientSideConnects();
    setServerSideConnects();

    setPause(false);
    setTimeOut(false);
    setTimeOutVal(50);
    _space = 35;

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));

      QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                       this,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

void SubWindowRealtime::setServerSideConnects(){
    //BRIGHTNESS = 0, CONTRAST = 1, GAMMA = 2, ROTATION = 3, SCALE = 4, HOR_FLIP = 5, VER_FLIP = 6,
    QObject::connect(myDev->listPropServ.at(BRIGHTNESS), SIGNAL(setVal(QVariant)), this, SLOT(setLbBr(QVariant)));
    QObject::connect(myDev->listPropServ.at(ROTATION), SIGNAL(setVal(QVariant)), this, SLOT(setLbRot(QVariant)));
    QObject::connect(myDev->listPropServ.at(CONTRAST), SIGNAL(setVal(QVariant)), this, SLOT(setLbCon(QVariant)));
    QObject::connect(myDev->listPropServ.at(GAMMA), SIGNAL(setVal(QVariant)), this, SLOT(setLbGam(QVariant)));
   // QObject::connect(myDev->listPropServ.at(SCALE), SIGNAL(setVal(QVariant)), this, SLOT(setLbScl(QVariant)));
    QObject::connect(myDev->listPropServ.at(HOR_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbHFlip(QVariant)));
    QObject::connect(myDev->listPropServ.at(VER_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbVFlip(QVariant)));
}
void SubWindowRealtime::setClientSideConnects(){
     //BRIGHTNESS = 0, CONTRAST = 1, GAMMA = 2, ROTATION = 3, SCALE = 4, HOR_FLIP = 5, VER_FLIP = 6,
    QObject::connect(wgt->manip->listProp.at(BRIGHTNESS), SIGNAL(setVal(QVariant)), this, SLOT(setLbBr(QVariant)));
    QObject::connect(wgt->manip->listProp.at(ROTATION), SIGNAL(setVal(QVariant)), this, SLOT(setLbRot(QVariant)));
    QObject::connect(wgt->manip->listProp.at(CONTRAST), SIGNAL(setVal(QVariant)), this, SLOT(setLbCon(QVariant)));
    QObject::connect(wgt->manip->listProp.at(GAMMA), SIGNAL(setVal(QVariant)), this, SLOT(setLbGam(QVariant)));
    QObject::connect(wgt->manip->listProp.at(SCALE), SIGNAL(setVal(QVariant)), this, SLOT(setLbScl(QVariant)));
    QObject::connect(wgt->manip->listProp.at(HOR_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbHFlip(QVariant)));
    QObject::connect(wgt->manip->listProp.at(VER_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbVFlip(QVariant)));
}

void SubWindowRealtime::setClientSideDisconnects(){
    QObject::disconnect(wgt->manip->listProp.at(BRIGHTNESS), SIGNAL(setVal(QVariant)), this, SLOT(setLbBr(QVariant)));
    QObject::disconnect(wgt->manip->listProp.at(ROTATION), SIGNAL(setVal(QVariant)), this, SLOT(setLbRot(QVariant)));
    QObject::disconnect(wgt->manip->listProp.at(CONTRAST), SIGNAL(setVal(QVariant)), this, SLOT(setLbCon(QVariant)));
    QObject::disconnect(wgt->manip->listProp.at(GAMMA), SIGNAL(setVal(QVariant)), this, SLOT(setLbGam(QVariant)));
    QObject::disconnect(wgt->manip->listProp.at(SCALE), SIGNAL(setVal(QVariant)), this, SLOT(setLbScl(QVariant)));
    QObject::disconnect(wgt->manip->listProp.at(HOR_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbHFlip(QVariant)));
    QObject::disconnect(wgt->manip->listProp.at(VER_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbVFlip(QVariant)));
}

void SubWindowRealtime::initMyDev(QString serv, QString attr){
    myDev = new my_Device();
    work = true;
    myDev->_serverName = serv;
    myDev->attrImg = attr;

    QObject::connect(myDev, SIGNAL(sendError(QString)), this, SLOT(testOnError(QString)));
    QObject::connect(myDev, SIGNAL(goodConnection()), this, SLOT(testOnOk()));
    myDev->setDevice(serv);
}
void SubWindowRealtime::initFullPicMode(){
    board = new QWidget(this);
    wgt = new ImageWidget(board);
    QObject::connect(wgt, SIGNAL(resizeImgWgt(int,int)), this, SLOT(resizeWgt(int,int)));
    initLb(50);
    initTimeLb();
    calcStat();
    this->setWidget(board);
}
void SubWindowRealtime::initSizableMode(){
    scrollArea = new QScrollArea(this);
    board = new QWidget(scrollArea);
    scrollArea->setWidget(board);
    wgt = new ImageWidget(board);
    QObject::connect(wgt, SIGNAL(resizeImgWgt(int,int)), this, SLOT(resizeWgt(int,int)));
    scrollArea->setAutoFillBackground(true);
    initLb(50);
    initTimeLb();
    calcStat();
    this->setWidget(scrollArea);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void SubWindowRealtime::initTimeLb(){
    displayTime = new QLabel(board);
    displayTime->setObjectName(QString::fromUtf8("displayTime"));
    displayTime->setGeometry(QRect(5, 3, 50, 27));
    displayTime->setWordWrap(true);
}

void SubWindowRealtime::setStat(QLabel *lb, double val, int iter){
    lb = new QLabel(board);
    lb->setGeometry(QRect(410 + 50*iter, 3, 50, 27));
    lb->setWordWrap(true);
    lb->setText("Set" + QString().number(iter+1) +"\n" + QString().number(val));
}

void SubWindowRealtime::setStatVal(vector<double> val){
    int i;
    QList <QLabel*> ls;
    ls<<set1<<set2<<set3<<set4<<set5;
    for (i=0; i<val.size(); i++){
        setStat(ls.at(i), val.at(i), i);
    }
}

void SubWindowRealtime::calcStat(){
    Tango::DeviceAttribute attr;
    delete set1;
    set1 = NULL;
    delete set2;
    set2 = NULL;
    delete set3;
    set3 = NULL;
    delete set4;
    set4 = NULL;
    delete set5;
    set5 = NULL;
    if (myDev->setTangoAttr(CALC_STAT, attr)){
        bool isStatistic = false;
        if(myDev->setBoolVal(attr, isStatistic)){
            if(isStatistic){
                if (myDev->setTangoAttr(STAT, attr)){
                    vector<double> statVal;
                    if(myDev->setDoubleVal(attr, statVal)){
                        setStatVal(statVal);
                    }
                }
                else{
                    qDebug("SET CORRECT STATISTIC ATTR VALUE");
                }
            }
        }
    }
    else{
        qDebug("TANGO SERVER HASN'T STATISTIC or SET CORRECT CALCSTATISTIC ATTR VALUE");
    }
}

double SubWindowRealtime::getDegree(){
    return wgt->manip->listProp.at(ROTATION)->getValue().toDouble();
}

void SubWindowRealtime::resizeEvent ( QResizeEvent * event ){
    if (difLevelPers){
        int newW;
        double degree = getDegree();
        if (degree == 0 || degree == -180 || degree == 180){
                newW = event->size().height() + ceil(*difLevelPers * event->size().height());
                *event = QResizeEvent(QSize(newW, event->size().height()-25),event->oldSize());
                   dimX = newW;
                   dimY = event->size().height();
        }
        else {
            newW = event->size().height();
            *event = QResizeEvent(QSize(newW, event->size().width()),event->oldSize());
            dimX = newW;
            dimY = event->size().height();
        }
        isResized = true;
        emit QMdiSubWindow::resizeEvent(event);
    }
    else{
        dimX =  event->size().width();
        dimY =  event->size().height();
        isResized = true;
        emit QMdiSubWindow::resizeEvent(event);
    }
}

SubWindowRealtime::~SubWindowRealtime(){
    qDebug("in SubWindowRealtime destructor");
    delete myDev;
    myDev = NULL;
    delete difLevelPers;
    delete set1;
    delete set2;
    delete set3;
    delete set4;
    delete set5;
    delete displayTime;
 //   delete _widgetLayout;
}

void SubWindowRealtime::closeEvent (QCloseEvent *e){
    qDebug("Colose event REaltim_subwin");
    if (_canBeClosed){
        this->deleteLater();
        work = false;
        myDev->pingTimer.stop();
        qDebug("Attention, in SubWindowRealtime::closeEvent pingTimer STOPED");
        emit closeRealtime(this);
    }
    else{
        qDebug("Warring(Error), Right now I cannot close Realtime!!!!!");
        e->ignore();
    }
}

void SubWindowRealtime::handleWindowStateChanged(Qt::WindowStates oldWSt, Qt::WindowStates newWSt){
    qDebug("WIN  %d OLD %d NEW %d\n", this, (int)oldWSt, (int)newWSt);
    if(newWSt == Qt::WindowActive && oldWSt == Qt::WindowNoState){
        qDebug("curRealtime handleWindowStateChanged");
        emit realtimeWinChanged(this);
    }
    if(oldWSt == Qt::WindowActive &&  newWSt == Qt::WindowNoState){
        qDebug("curRealtime handleWindowStateChanged");
        emit realtimeWinChanged(NULL);
    }
}

void SubWindowRealtime::testOnError(QString str){
   // lb->setText(str);
    setWindowTitle(str);
    myDev->pingTimer.start();
    qDebug("Attention, in SubWindowRealtime::testOnError pingTimer STOPED");
}

bool SubWindowRealtime::readServerPropertyVal(int param){
    return myDev->readServerPropertyVal(param);
}

void SubWindowRealtime::serverSide(){
    if(!readServerPropertyVal(ROTATION))  {setLbRot("Err");}
    if(!readServerPropertyVal(BRIGHTNESS)){setLbBr("Err");}
    if(!readServerPropertyVal(CONTRAST))  {setLbCon("Err");}
    if(!readServerPropertyVal(SCALE))     {setLbScl("Err");}
    if(!readServerPropertyVal(GAMMA))     {setLbGam("Err");}
    if(!readServerPropertyVal(VER_FLIP))  {setLbVFlip("Err");}
    if(!readServerPropertyVal(HOR_FLIP))  {setLbHFlip("Err");}
}

bool SubWindowRealtime::makeImg(){
   Tango::DeviceAttribute attr;
   if (myDev->setTangoAttr(IMAGE, attr)){
       vector <unsigned char> val;
       //wgt->curDataFormat = attr.get_type();
       //switch (wgt->curDataFormat){
       switch (attr.get_type()){
           case IS_UCHAR_DATA:
               if(myDev->setUCharVal(attr, val)){
                   if (wgt->imgType  == IS_16BITIMG_GREY){ emit isUCharData();  return false;}
               }
               else{
                   qDebug("Error, UCHAR DATA WASN'T READ");
                   return false;
               }
           break;
           case IS_USHORT_DATA:
               if (myDev->setUShortVal(attr, wgt->valUSh)){
                  if (wgt->imgType  != IS_16BITIMG_GREY){emit isUShortData(); return false;}
                  wgt->picMode->Convert16BitData(wgt->valUSh, val);
                  emit send16BitData(wgt->valUSh);
               }
               else{
                   qDebug("Error, Set correct attr16BitImgData");
                   return false;
               }
           break;
           default:
               qDebug("Error, Incorrect input DataType");
               return false;
               break;
       }
       *wgt->img = wgt->picMode->setImage(attr.get_dim_x(), attr.get_dim_y(), val);
       wgt->setPicSetings(wgt->img->width(), wgt->img->height());
       return true;
    }
    else{
       setWindowTitle("Incorrect Image Attr name!!!");
        qDebug("\n~~~~ERORR in setting Tango Img variable!!!~~~~~~\n");
        return false;
    }
}

void SubWindowRealtime::testOnOk(){
    qDebug() << "testOnOk: " << QThread::currentThread();
    _canBeClosed = false;
    QCoreApplication::processEvents(QEventLoop::AllEvents);
    qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAa";
    if (work){
        QTime time;
        time.start();
        if (myDev &&myDev->device){
            int curTime = 0;
            qDebug("~~~~~~~~~~");
            setWindowTitle(myDev->_serverName);
            if (makeImg()){
                    if (serverOperation){
                        qDebug("~~~~~Server side~~~~~");
                        serverSide();
                    }
                    else{
                        qDebug("~~~~~Client side~~~~~");
                    }
                    if (fullPictureMode && isResized ){
                        calcFullPictureScale(dimX, dimY);
                        isResized = false;
                    }
                    wgt->setClientValues();
                    emit newPicture();
                }
            else{
                 qDebug("Error SubWindowRealtime::testOnOk()");
            }
            curTime = time.restart();
            displayTime->setText("Time\n" + QString().number(curTime));
            qDebug("Time for Displaying picture is %d", curTime);
            _canBeClosed = true;
            QCoreApplication::processEvents(QEventLoop::AllEvents);
            if (work && myDev){
                emit ping();
            }
       }
       qDebug("PingSended");
    }
}

void SubWindowRealtime::sendingPing(){
    if (myDev){
        if (!isTimeout && !pause && myDev->device){
            testOnOk();
        }
        else{
            myDev->pingTimer.start();
            qDebug("Attention, in SubWindowRealtime::sendingPing pingTimer STARTED");
        }
    }
}

void SubWindowRealtime::scaledPictureModeResize(int x, int y){
    if (scrollArea){
        if(x<scrollArea->width()){
           scrollArea->resize(x+2, scrollArea->height());
           resize(x+2,scrollArea->height()+32);
       }
       if (y<scrollArea->height()){
           scrollArea->resize(scrollArea->width(), y);
           resize(x+2,scrollArea->height()+32);
        }
        wgt->resizeWgt(x,y);
    }
    else{
        return;}
}
void SubWindowRealtime::fullPictureModeResize(int x, int y){
    if (!difLevelPers){
        difLevelPers = new double;
        *difLevelPers = (double)x/(double)y;
        QResizeEvent e = QResizeEvent(QSize(width(), height()),QSize(width(), height()));
        resizeEvent(&e);
    }
    else {
        int www = this->width();//+40;
        int hhh = this->height();//+40;
        double degree = 0;
        degree  = getDegree();
        if(x<www && (degree == 0 || degree == -180 || degree == 180)){
            resize(x+10,board->height()+30);
            wgt->resizeWgt(x,y); ///coef
            return;
        }
        else if(x>www && (degree == 0 || degree == -180 || degree == 180)){
            resize(x+10,board->height()+30);
            wgt->resizeWgt(www,y);
            return;
        }
        else if (x<www&& (degree == 90 ||degree == -90|| degree == -270 || degree == 270)){
            resize(x+_space,board->height()+30);
            wgt->resizeWgt(www,y);
            repaint();
            return;
        }

        else if (x>www&& (degree == 90 ||degree == -90|| degree == -270 || degree == 270)){
            resize(x+_space,board->height()+30);
            wgt->resizeWgt(x,hhh);
            repaint();
            return;
        }
        else return; //you mustnot be here
    }
}
///////////////////////////////////////////////////////////////
void SubWindowRealtime::resizeWgt(int x, int y){
    board->resize(x, y+30);
    if(fullPictureMode){
        fullPictureModeResize(x, y);
    }
    else{
        scaledPictureModeResize(x,y);
    }

}

void SubWindowRealtime::setLocalNumericVal(int param, double val){ //should be hard checked in next version
    if (!myDev->propertyIsNULL(param)){
        wgt->manip->listProp.at(param)->setValue(val);//*myDev->_contrastServer
    }
    else{
        qDebug("Warring _contrastServer NOT INITED");
        wgt->manip->listProp.at(param)->setValue(val);
    }
}

void SubWindowRealtime::chContrastOn(int val){
    int con = wgt->manip->listProp.at(CONTRAST)->getValue().toInt();
    if (serverOperation){
        myDev->setContrastDeviceValCommand(con + val);
    }
    else{
        setLocalNumericVal(CONTRAST, con + val);
    }
}

void SubWindowRealtime::chGammaOn(int val){
    MyDevProperty *gamma = wgt->manip->listProp.at(GAMMA);
    int gm = gamma->getValue().toInt();
    if (serverOperation){
        myDev->setGammaDeviceValCommand(gm + val);
    }
    else{
        setLocalNumericVal(GAMMA, gm + val);
    }
}

void SubWindowRealtime::chBrightnessOn(int val){
    MyDevProperty *brightness = wgt->manip->listProp.at(BRIGHTNESS);
    int br = brightness->getValue().toInt();
    if (serverOperation){
        myDev->setBrightnessDeviceValCommand(br + val);
    }
    else{
        setLocalNumericVal(BRIGHTNESS, br + val);
    }
}

void SubWindowRealtime::chRotationOn(double val){
    MyDevProperty *rotation = wgt->manip->listProp.at(ROTATION);
    double rot = rotation->getValue().toDouble();
    if (serverOperation){
        myDev->setRotationDeviceValCommand(rot + val);
    }
    else{
        setLocalNumericVal(ROTATION, rot + val);
    }
}

void SubWindowRealtime::chScaleOn(double val){
    MyDevProperty *scale = wgt->manip->listProp.at(SCALE);
    double scl = scale->getValue().toDouble();
    if (serverOperation){
        myDev->setScaleDeviceValCommand(scl* val);
    }
    else{
        setLocalNumericVal(SCALE, scl* val);
    }
}

void SubWindowRealtime::setLocalPropertyValOnServerDifVal(int param, double dif){
    if (dif < 0){
        wgt->manip->listProp.at(param)->setValue(myDev->listPropServ.at(param)->getValue().toDouble() - dif);
    }
    else{
        wgt->manip->listProp.at(param)->setValue(myDev->listPropServ.at(param)->getValue().toDouble() + dif);
    }
}

void SubWindowRealtime::setClientSideNumericVal(int param, double val){
    if (!myDev->propertyIsNULL(param)){
        setLocalPropertyValOnServerDifVal(param, myDev->listPropServ.at(param)->getValue().toInt()- val);
    }
    else{
        qDebug("Warring Dev_attr NOT INITED");
        wgt->manip->listProp.at(param)->setValue(val);
    }
}
void SubWindowRealtime::setContrast(int val){
    if (serverOperation){
        myDev->setContrastDeviceValCommand(val);
    }
    else{
        setClientSideNumericVal(CONTRAST, val);
    }
}

void SubWindowRealtime::setGamma(int val){
    if (serverOperation){
        myDev->setGammaDeviceValCommand(val);
    }
    else{
        setClientSideNumericVal(GAMMA, val);
    }
}

void SubWindowRealtime::setBrightness(int val){
    if (serverOperation){
        myDev->setBrightnessDeviceValCommand(val);
    }
    else{
        setClientSideNumericVal(BRIGHTNESS, val);
    }
}

void SubWindowRealtime::setRotation(double val){
    if (serverOperation){
        myDev->setRotationDeviceValCommand(val);
    }
    else{
        setClientSideNumericVal(ROTATION, val);
    }
}

void SubWindowRealtime::setScale(double val){
    if (serverOperation){
        myDev->setScaleDeviceValCommand(val);
    }
    else{
        setClientSideNumericVal(SCALE, val);
    }
}

void SubWindowRealtime::setHorFlipValue(QString val){
    if (serverOperation){
        myDev->setHorFlipDeviceValCommand(val);
    }
    else{
        wgt->manip->listProp.at(HOR_FLIP)->setValue(val);
    }
}
void SubWindowRealtime::setVerFlipValue(QString val){
    if (serverOperation){
        myDev->setVerFlipDeviceValCommand(val);
    }
    else{
        wgt->manip->listProp.at(VER_FLIP)->setValue(val);
    }
}

void SubWindowRealtime::resetServerParam(){
    if (!serverOperation){
        setScale(1);
        setRotation(0);
        setBrightness(0);
        setGamma(100);
        setContrast(100);
        setVerFlipValue("false");
        setVerFlipValue("false");
    }
    else{
        qDebug("Warring You cann't reset prop in serverOperation mode!!!");
    }
}

void SubWindowRealtime::resetImg(){
    resetServerParam();
}

void SubWindowRealtime::chConnectsClient(int param){
    if (!myDev->propertyIsNULL(param)){
        wgt->manip->listProp.at(param)->setValue(myDev->listPropServ.at(param)->getValue());
        delete myDev->listPropServ.at(param);
        myDev->listPropServ[param] = NULL;
    }
}

void SubWindowRealtime::chServerOperation(){
    if(serverOperation){
        serverOperation = false;
        setClientSideConnects();

        chConnectsClient(BRIGHTNESS);
        chConnectsClient(GAMMA);
        chConnectsClient(CONTRAST);
        chConnectsClient(ROTATION);
        chConnectsClient(HOR_FLIP);
        chConnectsClient(VER_FLIP);
    }
    else{
        serverOperation = true;
        lbBr->setText("Br:\n n/a");
        lbRot->setText("Rot:\n n/a");
        lbCon->setText("Con:\n n/a");
        lbGam->setText("Gam:\n n/a");
        lbScl->setText("Scl:\n n/a");
        lbHorFl->setText("H_Fl:\n n/a");
        lbVerFl->setText("V_Fl:\n n/a");
        setClientSideDisconnects();
    }
}

void SubWindowRealtime::sendTangoCommand(QString com){
    if (myDev->sendTangoCommand(com)){
        qDebug("Tango command was sended");
    }
    else{
        qDebug("Error Tango command wasn't sended");
    }
}

void SubWindowRealtime::setPause(bool p){
    pause = p;
}

void SubWindowRealtime::setTimeOut(bool p){
    isTimeout = p;
}

void SubWindowRealtime::setImageMode(int mode){
    chImageMode(mode);
    QResizeEvent e = QResizeEvent(QSize(width(), height()),QSize(width(), height()));
    resizeEvent(&e);
}

bool SubWindowRealtime::isCanBeClosed(){
    return _canBeClosed;
}

void SubWindowRealtime::setFullPictureMode(bool val){
    fullPictureMode = val;
    if (_canBeClosed){
        QList <QVariant> listProp;
        wgt->manip->getParams(listProp);
        if (val){
            delete scrollArea;
            scrollArea = NULL;
            initFullPicMode();
            QResizeEvent e =  QResizeEvent(QSize(width(), height()),QSize(width(), height()));
            resizeEvent(&e);
        }
        else{
            delete difLevelPers;
            difLevelPers = NULL;
            delete board;
            initSizableMode();

            wgt->manip->listProp.at(SCALE)->setValue(1.0);
        }
        wgt->manip->setParams(listProp);
        chImageMode(wgt->picMode->getPictureMode());
        board->setAutoFillBackground(true);
        emit DisplayModeChanged();
        emit fullPictureModeChanged(this);
    }
}

void SubWindowRealtime::setTimeOutVal(int val){
    myDev->setTimeoutVal(val);
}

