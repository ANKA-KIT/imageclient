#include "roisubwindow.h"

#include <QMenu>
#include "eimagescreen.h"

RoiSubWindow::RoiSubWindow(QPoint p1,QPoint p2,TImage *tim): SubWindow(SubWindow::SNAPSHOT)
{
    //QRect region(tim->wgt->limX1,tim->wgt->limY1,tim->wgt->limX2-tim->wgt->limX1,tim->wgt->limY2-tim->wgt->limY1);
    QRect region(p1.x(), p1.y(), p2.x()-p1.x(), p2.y()-p1.y());
    roi = new ROIClass(tim, centralWidget, region);

    vbox->addWidget(roi->sample,100);

    _serverName = tim->getServerName();
    _serverAttr = tim->getAttrName();
    connect(roi->sample,SIGNAL(scaleValue(double)),this,SLOT(setScaleDisplay(double)));
    connect(roi->sample,SIGNAL(brightnessValue(int)),this,SLOT(setBrightnessDisplay(int)));
    connect(roi->sample,SIGNAL(contrastValue(int)),this,SLOT(setContrastDisplay(int)));
    connect(roi->sample,SIGNAL(gammaValue(int)),this,SLOT(setGammaDisplay(int)));
    connect(roi->sample,SIGNAL(rotateValue(double)),this,SLOT(setRotateDisplay(double)));
    connect(roi->sample,SIGNAL(hFlipValue(bool)),this,SLOT(setHFlipDisplay(bool)));
    connect(roi->sample,SIGNAL(vFlipValue(bool)),this,SLOT(setVFlipDisplay(bool)));

    setRotateDisplay(roi->sample->getRotate());
    setGammaDisplay(roi->sample->getGamma());
    setBrightnessDisplay(roi->sample->getBrightness());
    setContrastDisplay(roi->sample->getContrast());
    setHFlipDisplay(roi->sample->getHFlip());
    setVFlipDisplay(roi->sample->getVFlip());
    setScaleDisplay(roi->sample->getScale());

    QMenu  *snpMenu = new QMenu(tr("Make Snapshot"), this);
    snpWhole = new QAction(tr("Whole image"),this);
    snpVis = new QAction(tr("Visiable part"), this);
    snpMenu->addAction(snpWhole);
    snpMenu->addAction(snpVis);
    roi->sample->wgt->contextMenu->addMenu(snpMenu);
    setRoi = new QAction(tr("Set ROI"), this);
    connect(setRoi,SIGNAL(triggered()),this,SLOT(changeRoi()));
    roi->sample->wgt->contextMenu->addAction(setRoi);

    setWindowTitle(QString().number(region.x()) + "," + QString().number(region.y())+
                   + " " + QString().number(region.x()+region.width()) + "," + QString().number(region.y()+region.height()) +
                   " " + _serverName);
}

void RoiSubWindow::changeRoi(){
    SetRoiWin *newRoiWin = new SetRoiWin;

    connect(newRoiWin,SIGNAL(region(QPoint,QPoint)),this,SLOT(changeRoi(QPoint,QPoint)));
    newRoiWin->setAttribute(Qt::WA_DeleteOnClose);
    newRoiWin->show();
}

void RoiSubWindow::changeRoi(QPoint p1,QPoint p2){
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

    if (p2.x() > roi->maxWidth){ p2.setX(roi->maxWidth);}
    if (p2.y() > roi->maxHeight){ p2.setY(roi->maxHeight);}

    roi->setRect(p1,p2);
    setWindowTitle(QString().number(p1.x()) + "," + QString().number(p1.y())+
                   + " " + QString().number(p2.x()) + "," + QString().number(p2.y()) +
                   " " + _serverName );
}
