#include "realtimesubwindow.h"

#include "timage.h"

#include "imagemarker.h"
#include "eimagescreen.h"
#include "syncdialog.h"

RealtimeSubWindow::RealtimeSubWindow(QString tangoDev, QString tangoImage) : SubWindow(SubWindow::REALTIME), tim(new TImage(this))
{
    tim->setSource(tangoDev, tangoImage);
    syncDialog = new SyncDialog(tim->tango);
    setWindowTitle(tangoDev);
    vbox->addWidget(tim, 100);

    connect(tim, SIGNAL(scaleValue(double)), this, SLOT(setScaleDisplay(double)));
    connect(tim, SIGNAL(brightnessValue(int)), this, SLOT(setBrightnessDisplay(int)));
    connect(tim, SIGNAL(contrastValue(int)), this, SLOT(setContrastDisplay(int)));
    connect(tim, SIGNAL(gammaValue(int)), this, SLOT(setGammaDisplay(int)));
    connect(tim, SIGNAL(rotateValue(double)), this, SLOT(setRotateDisplay(double)));
    connect(tim, SIGNAL(hFlipValue(bool)), this, SLOT(setHFlipDisplay(bool)));
    connect(tim, SIGNAL(vFlipValue(bool)), this, SLOT(setVFlipDisplay(bool)));
    connect(tim, SIGNAL(timeNewPic(int)), this, SLOT(setTimeDisplay(int)));
    connect(tim->wgt, SIGNAL(newMarker(ImageMarker*)), syncDialog, SLOT(localMarkerSet(ImageMarker*)));
    connect(tim->wgt, SIGNAL(delMarker(QPoint,QRgb)), syncDialog, SLOT(localMarkerRemoved()));

    setRotateDisplay(tim->getRotate());
    setGammaDisplay(tim->getGamma());
    setBrightnessDisplay(tim->getBrightness());
    setContrastDisplay(tim->getContrast());
    setHFlipDisplay(tim->getHFlip());
    setVFlipDisplay(tim->getVFlip());
    setScaleDisplay(tim->getScale());

    QMenu  *snpMenu = new QMenu(tr("Make Snapshot"), this);
    snpWhole = new QAction(tr("Whole image"), this);
    snpVis = new QAction(tr("Visiable part"), this);
    snpVis->setEnabled(false);
    snpMenu->addAction(snpWhole);
    snpMenu->addAction(snpVis);
    tim->wgt->contextMenu->addMenu(snpMenu);

    roiMenu = new QMenu(tr("ROI"), this);
    newRoi = new QAction(tr("Init Roi"), this);
    newRoi->setStatusTip("Init new region of interests in new window");
    connect(newRoi, SIGNAL(triggered()), this, SLOT(initRoi()));
    roiMenu->addAction(newRoi);
    tim->wgt->contextMenu->addMenu(roiMenu);

    QAction* crosshairSyncDialog = new QAction(tr("Marker sync..."), this);
    tim->wgt->contextMenu->addAction(crosshairSyncDialog);

    connect(crosshairSyncDialog, SIGNAL(triggered()), syncDialog, SLOT(show()));

    connect(tim, SIGNAL(addRoi(RoiAction*)), this, SLOT(addRoi(RoiAction*)));
    initRoiFlag = true;

    connect(tim, SIGNAL(fullscreenMode(bool)), this, SLOT(onChangeFullscreen(bool)));
}

void RealtimeSubWindow::setServerVar(QString val){//(ServerVariables val){
    tim->__serverAttrName = val;
}

void RealtimeSubWindow::setServerModeRead(bool val){//(ServerVariables val){
    tim->__serverMode = TImage::READ;
    tim->setServerMode(val);
}

void RealtimeSubWindow::setServerModeWrite(bool val){//(ServerVariables val){
    tim->__serverMode = TImage::WRITE;
    tim->setServerMode(val);
}

void RealtimeSubWindow::setClientSideMode(bool val){
    tim->__serverMode = TImage::SINGLE;
    tim->setServerMode(!val);
}


void RealtimeSubWindow::initRoi(){
    SetRoiWin *newRoiWin = new SetRoiWin;
    initRoiFlag = true;
    connect(newRoiWin,SIGNAL(region(QPoint,QPoint)),this,SLOT(initRoi(QPoint,QPoint)));
    newRoiWin->setAttribute(Qt::WA_DeleteOnClose);
    newRoiWin->show();
}


void RealtimeSubWindow::showRoi(RoiAction* r){
    emit newRoiCreated(r->p1,r->p2, tim);
}

void RealtimeSubWindow::addRoi(RoiAction* r){
    roiMenu->addMenu(r);
    connect(r,SIGNAL(actionClicked(RoiAction*)),this,SLOT(showRoi(RoiAction*)));
}

void RealtimeSubWindow::initRoi(QPoint p1,QPoint p2){
    QPoint temp;
    temp = p1;
    if (p1.x() > p2.x()){
        p1.setX(p2.x());
        p2.setX(temp.x());
    }
    if (p1.y() > p2.y()){
        p1.setY(p2.y());
        p2.setY(temp.y());
    }


    if (p1.x() < 0){ p1.setX(0);}
    if (p1.y() < 0){ p1.setY(0);}

    if (p2.x() > tim->wgt->picW){ p2.setX(tim->wgt->picW);}
    if (p2.y() > tim->wgt->picH){ p2.setY(tim->wgt->picH);}

    RoiAction* r = tim->initRoi(p1,p2);

    connect(r,SIGNAL(actionClicked(RoiAction*)),this,SLOT(showRoi(RoiAction*)));
    if (initRoiFlag){
        roiMenu->addMenu(r);
        //initRoiFlag = false;
    }
    else initRoiFlag = true;
    emit newRoiCreated(p1,p2, tim);
}

void RealtimeSubWindow::onChangeFullscreen(bool val){
    snpVis->setEnabled(!val);
}
