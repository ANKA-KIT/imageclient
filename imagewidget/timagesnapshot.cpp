#include "timagesnapshot.h"

//My_Code
void TImageSnapshot::resizeEvent(QResizeEvent * ){
    setImage(wgt->image);
}
TImageSnapshot::TImageSnapshot(QWidget *p):EImageBase(p)//,QTangoWidgetCommon(wgt)
{
    setAttribute(Qt::WA_AlwaysShowToolTips);
    setProperty("forceNoUnit", false);
    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

}

TImageSnapshot::TImageSnapshot(QImage img, int x, int y, int pm, QWidget *p ):EImageBase(img,x,y,pm,p){//,QTangoWidgetCommon(wgt){
    connect(this,SIGNAL(imgChanged(QImage)),SLOT(setImage(QImage)));
    connect(wgt,SIGNAL(imgTransformed(QImage)),SLOT(setImage(QImage)));
}
TImageSnapshot::TImageSnapshot(QVector<unsigned short > vector, int x, int y, int pm, QWidget *p):EImageBase(vector,x,y,pm,p){//,QTangoWidgetCommon(wgt){
        connect(this,SIGNAL(imgChanged(QImage)),SLOT(setImage(QImage)));
        connect(wgt,SIGNAL(imgTransformed(QImage)),SLOT(setImage(QImage)));
}


void TImageSnapshot::setImage(QImage img ){
    if (picMode->_colorMapChanged && val16.size() !=0){
            val.clear();
            picMode->convert16BitData(val16,val);
        img = picMode->setImage(dimX,dimY,val);
        wgt->image = img;
    }
//    horizontalScrollBar()->setMaximum(wgt->image.width());
//    verticalScrollBar()->setMaximum(wgt->image.height());
    wgt->widthScrBar->setMaximum(wgt->image.width());
    wgt->heightScrBar->setMaximum(wgt->image.height());
     img = setPropertiesOnImg(img);
     drawing(img);
 }

void TImageSnapshot::showParams(){
    QImage tempImg = wgt->image;
    if (manipulatorIsClosed){
    manip = new ImageManipulator(QList<QVariant>()
                                 <<imageParams.brightness<<imageParams.contrast<<wgt->imageTransform.rotate+serverValues[0]<<imageParams.gamma<<picMode->getLBorder()
                                 <<picMode->getRBorder()<<wgt->imageTransform.horFlip<<wgt->imageTransform.verFlip<<wgt->imageTransform.imageScale
                                 <<picMode->_maxContrast<<_timer<<picMode->getPictureMode()
                                 <<wgt->imageTransform.fullPictureMode<<wgt->moveX<<wgt->moveY<<dimX/picMode->getDelimitr()<<dimY,
                                 val16, tempImg);
    manip->setAttribute(Qt::WA_DeleteOnClose);//, Qt::WindowModal);
    manipulatorIsClosed = false;
    manip->setModal(true);

    connect(manip, SIGNAL(destroyed()), this, SLOT(manipDestroed()));
    connect(manip, SIGNAL(setBr(QVariant)), this, SLOT(setBrightness(QVariant)));
    connect(manip, SIGNAL(setCon(QVariant)), this, SLOT(setContrast(QVariant)));
    connect(manip, SIGNAL(setGm(QVariant)), this, SLOT(setGamma(QVariant)));
    connect(manip, SIGNAL(setLBorder(unsigned short)), this, SLOT(setLBorder(unsigned short)));
    connect(manip, SIGNAL(setRBorder(unsigned short)), this, SLOT(setRBorder(unsigned short)));
    connect(manip, SIGNAL(sendRotationVal(QVariant)), this, SLOT(setRotate(QVariant)));
    connect(manip, SIGNAL(sendHorFlipVal(QVariant)), this, SLOT(setHFlip(QVariant)));
    connect(manip, SIGNAL(sendVerFlipVal(QVariant)), this, SLOT(setVFlip(QVariant)));
    //connect(manip, SIGNAL(changeFormatOfColor(int)), this, SLOT(setImageType(int)));
    connect(manip, SIGNAL(changePictureModeSignal(int)), this, SLOT(setImageType(int)));
    connect(manip, SIGNAL(setTime(int)), this, SLOT(sendTimer(int)));
    connect(manip, SIGNAL(setScaleSignal(double)), this, SLOT(setScale(double)));
    connect(manip, SIGNAL(fullScreenMode(bool)), this, SLOT(setFullscreenMode(bool)));
    connect(manip, SIGNAL(getDataHistogram()), this, SLOT(drawHistogram()));

    connect(manip, SIGNAL(chPicX(int)), wgt, SLOT(setMoveX(int)));
    connect(manip, SIGNAL(chPicY(int)), wgt, SLOT(setMoveY(int)));
    connect(wgt, SIGNAL(showPictureSize(int,int,int,int)), manip, SLOT(setShowPicSize(int,int,int,int)));
    setImage(wgt->image);
    manip->show();
    }
}

//My_Code_End
