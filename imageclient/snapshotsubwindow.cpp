#include <timage.h>

#include "snapshotsubwindow.h"

SnapshotSubWindow::SnapshotSubWindow(TImage* tim, int type) : SubWindow(SubWindow::SNAPSHOT)
{
    if (type == WHOLE) {
        snp = tim->makeSnpImage(this);
    } else {
        snp = tim->makeSnpImageCat(this);
    }

    vbox->addWidget(snp,100);

    connect(snp,SIGNAL(scaleValue(double)),this,SLOT(setScaleDisplay(double)));
    connect(snp,SIGNAL(brightnessValue(int)),this,SLOT(setBrightnessDisplay(int)));
    connect(snp,SIGNAL(contrastValue(int)),this,SLOT(setContrastDisplay(int)));
    connect(snp,SIGNAL(gammaValue(int)),this,SLOT(setGammaDisplay(int)));
    connect(snp,SIGNAL(rotateValue(double)),this,SLOT(setRotateDisplay(double)));
    connect(snp,SIGNAL(hFlipValue(bool)),this,SLOT(setHFlipDisplay(bool)));
    connect(snp,SIGNAL(vFlipValue(bool)),this,SLOT(setVFlipDisplay(bool)));

    setRotateDisplay(snp->getRotate());
    setGammaDisplay(snp->getGamma());
    setBrightnessDisplay(snp->getBrightness());
    setContrastDisplay(snp->getContrast());
    setHFlipDisplay(snp->getHFlip());
    setVFlipDisplay(snp->getHFlip());
    setScaleDisplay(snp->getScale());
}
