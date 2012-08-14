#include "subwindowsnapshot.h"
void SubWindowSnapshot::initLbSnap(){
    initLb(0);
    setAutoFillBackground(true);
    board->setAutoFillBackground(true);

    QObject::connect(wgt->manip->listProp.at(BRIGHTNESS), SIGNAL(setVal(QVariant)), this, SLOT(setLbBr(QVariant)));
    QObject::connect(wgt->manip->listProp.at(ROTATION), SIGNAL(setVal(QVariant)), this, SLOT(setLbRot(QVariant)));
    QObject::connect(wgt->manip->listProp.at(CONTRAST), SIGNAL(setVal(QVariant)), this, SLOT(setLbCon(QVariant)));
    QObject::connect(wgt->manip->listProp.at(GAMMA), SIGNAL(setVal(QVariant)), this, SLOT(setLbGam(QVariant)));
    QObject::connect(wgt->manip->listProp.at(SCALE), SIGNAL(setVal(QVariant)), this, SLOT(setLbScl(QVariant)));
    QObject::connect(wgt->manip->listProp.at(HOR_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbHFlip(QVariant)));
    QObject::connect(wgt->manip->listProp.at(VER_FLIP), SIGNAL(setVal(QVariant)), this, SLOT(setLbVFlip(QVariant)));
    QObject::connect(wgt, SIGNAL(resizeImgWgt(int,int)), this, SLOT(resizeWgt(int,int)));
}

void SubWindowSnapshot::initPropConnects(){
    QObject::connect(wgt->manip->listProp.at(CONTRAST), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
    QObject::connect(wgt->manip->listProp.at(GAMMA), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
    QObject::connect(wgt->manip->listProp.at(BRIGHTNESS), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
    QObject::connect(wgt->manip->listProp.at(ROTATION), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
    QObject::connect(wgt->manip->listProp.at(SCALE), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
    QObject::connect(wgt->manip->listProp.at(HOR_FLIP), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
    QObject::connect(wgt->manip->listProp.at(VER_FLIP), SIGNAL(repaint(int)), wgt, SLOT(setAllValues(int)));
}

void SubWindowSnapshot::resizeWgt(int x, int y){
    if(!fullPictureMode){
        QResizeEvent e =  QResizeEvent(QSize(width(), height()),QSize(width(), height()));
        resizeEvent(&e);
    }//crashed in fullpicturemode
}

SubWindowSnapshot::SubWindowSnapshot(QImage* img, ImgManipulation* man, double diff, double scale)// :QWidget(parent)
{
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
   // _widgetLayout = new QHBoxLayout();
    scrollArea = new QScrollArea(this);
    board = new QWidget(scrollArea);
    scrollArea->setWidget(board);
    board->resize(img->width(),img->height()+30);
    wgt = new ImageWidget(img, board);
   // _originImg = new QImage();
  //  *_originImg = *img;

    initPropConnects();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    setAutoFillBackground(true);
    qDebug("in SubWindowSnapshot constructor");
    QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),this,
    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
    initLbSnap();

    setLbBr(man->getBrightnessVal());
    setLbRot(man->getRotationVal());
    setLbCon(man->getContrastVal());
    setLbGam(man->getGammaVal());
    setLbScl(man->getScaleVal());
    setLbHFlip(man->getHorFlipVal());
    setLbVFlip(man->getVerFlipVal());

    fullPictureMode = false;
    setWidget(scrollArea);

    QObject::connect(wgt, SIGNAL(repainting()), wgt, SLOT(rescreen()));
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));

    scl = scale;
    difLevelPers = diff;
    _space = 40;
}

SubWindowSnapshot::~SubWindowSnapshot(){
     qDebug("in SubWindowSnapshot Destructor");
   //  delete _originImg;

   //  delete _widgetLayout;
}

 void SubWindowSnapshot::handleWindowStateChanged(Qt::WindowStates oldWSt, Qt::WindowStates newWSt){
     qDebug("SnapshotWIN  %d OLD %d NEW %d\n", this, (int)oldWSt, (int)newWSt);
     if(newWSt == Qt::WindowActive && oldWSt == Qt::WindowNoState){
         qDebug("curSnap handleWindowStateChanged");
         emit SnapshotWinChanged(this);
     }
     if(oldWSt == Qt::WindowActive &&  newWSt == Qt::WindowNoState){
         qDebug("curSnap handleWindowStateChanged");
         emit SnapshotWinChanged(NULL);
     }
 }

 void SubWindowSnapshot::chContrastOn(int val){
      wgt->manip->listProp.at(ROTATION)->setValue(wgt->manip->getContrastVal() + val);
 }

 void SubWindowSnapshot::chGammaOn(int val){
         wgt->manip->listProp.at(GAMMA)->setValue(wgt->manip->getGammaVal() + val);
 }

 void SubWindowSnapshot::chBrightnessOn(int val){
         wgt->manip->listProp.at(BRIGHTNESS)->setValue(wgt->manip->getBrightnessVal() + val);
 }

 void SubWindowSnapshot::chRotationOn(double val){
         wgt->manip->listProp.at(ROTATION)->setValue(wgt->manip->getRotationVal() + val);
 }

 void SubWindowSnapshot::chScaleOn(double val){
        wgt->manip->listProp.at(SCALE)->setValue(wgt->manip->getScaleVal() * val);
 }

 void SubWindowSnapshot::setScale(double val){
     setLbScl(val);
     //wgt->setScaleSnap(*_originImg, val);
     wgt->setScaleSnap(val);
 }

 void SubWindowSnapshot::setContrast(int val){
      wgt->manip->listProp.at(CONTRAST)->setValue(val);
 }

 void SubWindowSnapshot::setGamma(int val){
      wgt->manip->listProp.at(GAMMA)->setValue(val);
 }

 void SubWindowSnapshot::setBrightness(int val){
      wgt->manip->listProp.at(BRIGHTNESS)->setValue(val);
 }

 void SubWindowSnapshot::setRotation(double val){
      wgt->manip->listProp.at(ROTATION)->setValue(val);
 }

 void SubWindowSnapshot::setVerFlipValue(QString val){
      wgt->manip->listProp.at(VER_FLIP)->setValue(val);
 }

 void SubWindowSnapshot::setHorFlipValue(QString val){
      wgt->manip->listProp.at(HOR_FLIP)->setValue(val);
 }

 void SubWindowSnapshot::resetImg(){
     //wgt->resetClientSideVal(*_originImg);
     wgt->resetClientSideVal();
 }

void SubWindowSnapshot::setImageMode(int mode){
    chImageMode(mode);
}

void SubWindowSnapshot::resizeEvent ( QResizeEvent * event ){
    board->resize(wgt->img->width(),wgt->img->height()+30);
    int W = event->size().width(), H = event->size().height();
    int w = board->width();

    if (!fullPictureMode){
        if (board->width() < event->size().width()-_space){
            W = board->width()+30;
        }
        if (board->height() < event->size().height()-60){
            H = board->height()+50;
        }
        resize(W,H);
        emit QMdiSubWindow::resizeEvent(event);
    }
    else{
            int newW;
            double degree = 0;
            degree = wgt->manip->listProp.at(ROTATION)->getValue().toDouble();
            if (degree == 0 || degree == -180 || degree == 180){
                    newW = event->size().height() + ceil(difLevelPers * event->size().height());
                    *event = QResizeEvent(QSize(newW, event->size().height()-25),event->oldSize());
                       W = newW;
                       H = event->size().height();
            }
            else {
                newW = event->size().height();
                *event = QResizeEvent(QSize(newW, event->size().width()),event->oldSize());
                W = newW;
                H = event->size().height();
            }
            emit QMdiSubWindow::resizeEvent(event);
          //  _space = 35;
        calcFullPictureScale(W, H);


 /*       int xxx= wgt->width();
        if(xxx<W && (degree == 0 || degree == -180 || degree == 180)){
            //event->size() xxx+10,board->height()+30);
            //*event = QResizeEvent(QSize(xxx, event->size().height()),event->oldSize());
            event->ignore();
           // repaint();
        }
        else if(xxx>W && (degree == 0 || degree == -180 || degree == 180)){
            //*event = QResizeEvent(QSize(xxx, event->size().height()),event->oldSize());
             event->ignore();
        }
        else if (xxx<W&& (degree == 90 ||degree == -90|| degree == -270 || degree == 270)){
           *event = QResizeEvent(QSize(xxx+10, event->size().height()),event->oldSize());
        }

        else if (xxx>W&& (degree == 90 ||degree == -90|| degree == -270 || degree == 270)){
          *event = QResizeEvent(QSize(xxx+10, event->size().height()),event->oldSize());
        }
        // emit QMdiSubWindow::resizeEvent(event);
        */
    }
}

void SubWindowSnapshot::closeEvent (QCloseEvent *e){
    emit closeSnap(this);
}

void SubWindowSnapshot::setFullPictureMode(bool val){
    fullPictureMode = val;
        QList <QVariant> listProp;
        wgt->manip->getParams(listProp);
        QImage img = *wgt->img;
       // int imgX = wgt->ImgDimX;
       // int imgY = wgt->ImgDimY;
        int imgX = wgt->_originSnap->width();
        int imgY = wgt->_originSnap->height();
        if (val){
            delete scrollArea;
            scrollArea = NULL;
            initFullPicMode(img);
        }
        else{
            delete board;
            initSizableMode(img);
            wgt->manip->listProp.at(SCALE)->setValue(1.0);
        }
        QResizeEvent e =  QResizeEvent(QSize(width(), height()),QSize(width(), height()));
        resizeEvent(&e);
        QObject::connect(wgt, SIGNAL(repainting()), wgt, SLOT(rescreen()));
        wgt->manip->setParams(listProp);
        wgt->setPicSetings(imgX, imgY);
        chImageMode(wgt->picMode->getPictureMode());
        setAutoFillBackground(true);
        board->setAutoFillBackground(true);
        wgt->setAutoFillBackground(true);
        initPropConnects();
        emit DisplayModeChanged();
        emit fullPictureModeChanged(this);
}

void SubWindowSnapshot::initSizableMode(QImage &img){
    scrollArea = new QScrollArea(this);
    board = new QWidget(scrollArea);
    scrollArea->setWidget(board);
    wgt = new ImageWidget(&img, board);
    QObject::connect(wgt, SIGNAL(resizeImgWgt(int,int)), this, SLOT(resizeWgt(int,int)));
    scrollArea->setAutoFillBackground(true);
    initLbSnap();
    setWidget(scrollArea);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void SubWindowSnapshot::initFullPicMode(QImage &img){
    board = new QWidget(this);
    wgt = new ImageWidget(&img, board);
    board->resize(wgt->img->width(),wgt->img->height()+30);
    QObject::connect(wgt, SIGNAL(resizeImgWgt(int,int)), this, SLOT(resizeWgt(int,int)));
    initLbSnap();
    setWidget(board);
}
