#include "eimagebase.h"

#include <QDebug>
#include "imagemarker.h"
#include "eimagescreen.h"

void EImageBase::init()
{
    for (int iter = 0; iter < 7; iter++) {
        serverValues[iter]=0;
    }
    manipulatorIsClosed = true;
    QWidget *w = new QWidget(this);
    wgt = new EImageScreen(w);

    QHBoxLayout *h= new QHBoxLayout;
    QVBoxLayout *wBox= new QVBoxLayout;
    wBox->addLayout(h);
    h->setMargin(0);
    h->addWidget(w);
    viewport()->setLayout(wBox);
    setWidget(w);

    setParamsAction = new QAction(tr("Set Params"), this);
    setParamsAction->setStatusTip(tr("Set image parameters"));
    QObject::connect(setParamsAction, SIGNAL(triggered()), this, SLOT(showParams()));
    setMarkerAction = new QAction(tr("Set Marker"), this);
    setMarkerAction->setStatusTip(tr("Set Marker on current point"));
    connect(setMarkerAction, SIGNAL(triggered()), this, SLOT(initMarker()));

    QMenu *saveMenu = new QMenu(tr("Save Image"), this);
    saveWholePic = new QMenu(tr("Save Whole Image"), this);
    saveWholePic->setStatusTip(tr("Save whole image"));
    saveCatPic = new QMenu(tr("Save Displayed Image"), this);
    saveCatPic->setStatusTip(tr("Save visiable part of image"));
    saveMenu->addMenu(saveWholePic);
    saveMenu->addMenu(saveCatPic);

    QAction *actS = new QAction(tr("Save Without Markers"), this);
    actS->setStatusTip(tr("Save image, markers will be invisiable on image"));
    QAction *actSave = new QAction(tr("Save With Markers"), this);
    actSave->setStatusTip(tr("Save image, markers will be visiable on image"));
    saveWholePic->addActions(QList<QAction *>()<<actS<<actSave);
    connect(actS,SIGNAL(triggered()),this,SLOT(saveWhole()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(saveWholeMarked()));

    QAction *catS = new QAction(tr("Save Without Markers"), this);
    catS->setStatusTip(tr("Save image, markers will be invisiable on image"));
    QAction *catSave = new QAction(tr("Save With Markers"), this);
    catSave->setStatusTip(tr("Save image, markers will be visiable on image"));
    saveCatPic->addActions(QList<QAction *>()<<catS<<catSave);

    connect(catS,SIGNAL(triggered()),this,SLOT(saveCat()));
    connect(catSave,SIGNAL(triggered()),this,SLOT(saveCatMarked()));

    wgt->setActionMenu(QList<QAction *>() << setParamsAction << setMarkerAction);
    wgt->contextMenu->addMenu(saveMenu);

    wBox->setMargin(0);
    h->addWidget(wgt->heightScrBar);
    wBox->addWidget(wgt->widthScrBar);

    imageParams.contrast = 100;
    imageParams.gamma = 100;
    imageParams.brightness = 0;

    _timer = 0;
    setFullscreenMode(wgt->imageTransform.fullPictureMode);
    connect(wgt, SIGNAL(mousePosition(QPoint)), this, SLOT(onScreenReapinting(QPoint)));
    connect(wgt, SIGNAL(newMarker(ImageMarker*)), this, SLOT(onNewMarker(ImageMarker*)));
}

EImageBase::EImageBase(QWidget *p): QScrollArea(p)
{
    init();
}

EImageBase::EImageBase(QImage img, int x, int y, int pm, QWidget *p): QScrollArea(p)
{
    init();
    dimX = x, dimY = y;
    picMode = new Is24RGB();
    resize(dimX, dimY);
    chImageMode(pm);
    wgt->image  = img.copy();
    if (picMode->getPictureMode() == ImagePictureMode::IS_RGBGRAY) {
        wgt->setPicWH(dimX / picMode->lastDelimetr, dimY);
    } else {
        wgt->setPicWH(dimX / picMode->getDelimitr(), dimY);
    }
}

EImageBase::EImageBase(QVector<unsigned short > vector, int x, int y, int pm, QWidget *p): QScrollArea(p)
{
    init();
    dimX = x, dimY = y;
    picMode = new Is24RGB();
    resize(dimX, dimY);
    chImageMode(pm);

    if (vector.size() != 0){
        val16.clear();
        for(int i=0; i<vector.size();i++)
            val16.push_back(vector.at(i));
        picMode->convert16BitData(val16, val);
        wgt->image = picMode->setImage(x,y,val);
    }
    else{
        wgt->image = errorImage();
    }
    if(picMode->getPictureMode() == ImagePictureMode::IS_RGBGRAY)
        wgt->setPicWH(dimX/picMode->lastDelimetr,dimY);
    else
        wgt->setPicWH(dimX/picMode->getDelimitr(),dimY);
}


void EImageBase::chImageMode(int mode){
    int del = picMode->getDelimitr();
    delete picMode;
    picMode = NULL;
    switch (mode) {
    case ImagePictureMode::IS_RGBA:
        val16.clear();
        picMode = new Is32RGB();
        break;
    case ImagePictureMode::IS_RGB:
        val16.clear();
        picMode = new Is24RGB();
        break;
    case ImagePictureMode::IS_16BITGRAY:
        picMode = new Is16BitGrey();;
        break;
    case ImagePictureMode::IS_48BIT:
        picMode = new Is48BitRGB();
        break;
    case ImagePictureMode::IS_RGBGRAY:
        val16.clear();
        picMode = new IsRGBGGrey();
        if (del != 1)
            picMode->lastDelimetr = del;
        else
            picMode->lastDelimetr = 4; //may be 3
        break;
    case ImagePictureMode::IS_8BIT:
        val16.clear();
        picMode = new Is8BitGrey();
        break;
    }
}

void  EImageBase::setScale(double val){
    wgt->setScale(val);
    emit scaleValue(wgt->imageTransform.imageScale);
}

QVector<unsigned char> EImageBase::getImageVector(QImage &img, int w, int h){
    QVector<unsigned char> val;
    unsigned char* line = NULL;
     for (int i = 0; i<h; i++){
         line = img.scanLine( i );
         for( int x = 0;  x < w;  ++x ){
             val.push_back(line[x]);
         }
     }
     return val;
}

void EImageBase::saveImg(QImage img){
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
              this,
              tr("Save Snapshot"),
              QDir::currentPath(),
                  tr("JPG(*.jpg);;TIFF(*.tiff);;BMP(*.bmp);;PNG(*.png);;JPEG(*jpeg);;"
                                "XBM(*.xbm);;XPM(*.xpm);;PPM(*.ppm)"),
                 &selectedFilter);
    if (filename != "") {

        qDebug( "save Format %s\n",  selectedFilter.split("(").takeFirst().toLower().toAscii().constData());

        if (val16.size() !=0){
            // no implementation yet!
        }
        img.save(filename+QString(".") + selectedFilter.split("(").takeFirst().toLower());
        //}
        qDebug("Save an Image\n");
    }
    else
        qDebug( "Saving an Image is canceled\n");
}

void EImageBase::saveImgWithMarkers(QImage img){
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
              this,
              tr("Save Snapshot"),
              QDir::currentPath(),
                  tr("JPG(*.jpg);;TIFF(*.tiff);;BMP(*.bmp);;PNG(*.png);;JPEG(*jpeg);;"
                                "XBM(*.xbm);;XPM(*.xpm);;PPM(*.ppm)"),
                 &selectedFilter);
    if(filename != ""){

        qDebug( "save Format %s\n",  selectedFilter.split("(").takeFirst().toLower().toAscii().constData());
        if(val16.size() !=0){
        ///////////////////
        }
        wgt->setMarkersOnPic(true, img);
        img.save(filename+QString(".") + selectedFilter.split("(").takeFirst().toLower());
        qDebug("Save an Image\n");

    }
    else
        qDebug( "Saving an Image is canceled\n");
}

void EImageBase::saveCatImgWithMarkers(QImage img){
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
              this,
              tr("Save Snapshot"),
              QDir::currentPath(),
                  tr("JPG(*.jpg);;TIFF(*.tiff);;BMP(*.bmp);;PNG(*.png);;JPEG(*jpeg);;"
                                "XBM(*.xbm);;XPM(*.xpm);;PPM(*.ppm)"),
                 &selectedFilter);
    if (filename != "") {
        qDebug( "save Format %s\n",  selectedFilter.split("(").takeFirst().toLower().toAscii().constData());
        wgt->setMarkersOnPic(false, img);
        img.save(filename+QString(".") + selectedFilter.split("(").takeFirst().toLower());
        qDebug("Save an Image\n");
    } else {
        qDebug( "Saving an Image is canceled\n");
    }
}



void EImageBase::fastSave(){
    QDate date = QDate::currentDate();
    QTime t = QTime::currentTime();
    QString filename =  QDir::currentPath();
            filename+= QString().number(date.month()) + "." +
                    QString().number(date.day())  + "." +
                    QString().number(t.hour())  + "." +
                    QString().number(t.minute())  + "." +
                    QString().number(t.second())  + "." +
                    QString().number(t.msec())  + ".tiff";
            wgt->image.save(filename);
}

void EImageBase::saveWhole(){
    QImage img;
    if (val.size()!=0){
        img = picMode->setImage(dimX, dimY, val);
        img = setVisualPropertiesOnImg(img);
    }
    else {img = wgt->image;}
    saveImg(img);
}
void EImageBase::saveWholeMarked(){
    QImage img;
    if (val.size()!=0){
        img = picMode->setImage(dimX, dimY, val);
        img = setVisualPropertiesOnImg(img);
    }
else {img = wgt->image;}
    saveImgWithMarkers(img);
}

void EImageBase::saveCatMarked()
{
    QImage img;
    if (val.size()!=0){
        img = picMode->setImage(dimX, dimY, val);
    }
    else {img = wgt->image;}
    saveCatImgWithMarkers(setPropertiesOnImg(img));
}

void EImageBase::saveCat()
{
    QImage img;
    if (val.size() != 0) {
        img = picMode->setImage(dimX, dimY, val);
    } else {
        img = wgt->image;
    }
    saveImg(setPropertiesOnImg(img));
}

void EImageBase::initMarker()
{
    wgt->initMarker();
    setMarkerAction->setEnabled(false);
}

QPoint EImageBase::convertToImagePoint(int x, int y)
{
    return wgt->convertToImagePoint(x,y);
}

void EImageBase::setBrightness(QVariant val)
{
    if (__serverMode == WRITE){
        valuesForWrite[2] = val.toInt();

        //valuesForWrite[0] = getRotate()+serverValues[0];
        valuesForWrite[0] = getRotate();
        valuesForWrite[1] = getGamma();
        //valuesForWrite[2] = getBrightness();
        valuesForWrite[3] = getContrast();
        valuesForWrite[4] = getVFlip();
        valuesForWrite[5] = getHFlip();
    }
    imageParams.brightness = val.toInt();

    emit imgChanged(wgt->image);
    emit brightnessValue(imageParams.brightness);
}

void EImageBase::setContrast(QVariant val){
    if (__serverMode == WRITE){
        valuesForWrite[3] = val.toInt();

        //valuesForWrite[0] = getRotate()+serverValues[0];
        valuesForWrite[0] = getRotate();
        valuesForWrite[1] = getGamma();
        valuesForWrite[2] = getBrightness();
        //valuesForWrite[3] = getContrast();
        valuesForWrite[4] = getVFlip();
        valuesForWrite[5] = getHFlip();
    }
    imageParams.contrast = val.toInt();

    emit imgChanged(wgt->image);
    emit contrastValue(imageParams.contrast);
}
void EImageBase::setGamma(QVariant val){
    if (__serverMode == WRITE){
        valuesForWrite[1] = val.toInt();

        //valuesForWrite[0] = getRotate()+serverValues[0];
        valuesForWrite[0] = getRotate();
        //valuesForWrite[1] = getGamma();
        valuesForWrite[2] = getBrightness();
        valuesForWrite[3] = getContrast();
        valuesForWrite[4] = getVFlip();
        valuesForWrite[5] = getHFlip();
    }
    imageParams.gamma = val.toInt();

    emit imgChanged(wgt->image);
    emit gammaValue(imageParams.gamma);
}
void EImageBase::setLBorder(unsigned short val){
    picMode->setLBorder(val);
    picMode->_colorMapChanged = true;
    emit imgChanged(wgt->image);
}
void EImageBase::setRBorder(unsigned short val){
    picMode->setRBorder(val);
    picMode->_colorMapChanged = true;
    emit imgChanged(wgt->image);
}

void EImageBase::setRotate(QVariant val){
    if (__serverMode == WRITE){
        valuesForWrite[0] = val.toDouble();
        valuesForWrite[1] = getGamma();
        valuesForWrite[2] = getBrightness();
        valuesForWrite[3] = getContrast();
        valuesForWrite[4] = getVFlip();
        valuesForWrite[5] = getHFlip();
    }
     if (__serverMode == READ_WITH_SERVERTRANSFORMATION){
        wgt->setRotate(val.toDouble()-serverValues[0]);
        emit rotateValue(wgt->imageTransform.rotate+serverValues[0]);
     }
     else{
         if (val.toDouble() != getRotate()){
         wgt->setRotate(val.toDouble());
         emit rotateValue(val.toDouble());
        }
    }

}

void EImageBase::setHFlip(QVariant val){
    if (__serverMode == WRITE){
        valuesForWrite[5] = val.toInt();

        //valuesForWrite[0] = getRotate()+serverValues[0];
        valuesForWrite[0] = getRotate();
        valuesForWrite[1] = getGamma();
        valuesForWrite[2] = getBrightness();
        valuesForWrite[3] = getContrast();
        valuesForWrite[4] = getVFlip();
        //valuesForWrite[5] = getHFlip();
    }
    if (val.toBool() != getHFlip()){
        wgt->setHFlip(val.toBool());
        emit hFlipValue(wgt->imageTransform.horFlip);
    }
}
void EImageBase::setVFlip(QVariant val){
    if (__serverMode == WRITE){
        valuesForWrite[4] = val.toInt();
       // valuesForWrite[0] = getRotate()+serverValues[0];
        valuesForWrite[0] = getRotate();
        valuesForWrite[1] = getGamma();
        valuesForWrite[2] = getBrightness();
        valuesForWrite[3] = getContrast();
        //valuesForWrite[4] = getVFlip();
        valuesForWrite[5] = getHFlip();
    }
    if (val.toBool() != getVFlip()){
        wgt->setVFlip(val.toBool());
        emit vFlipValue(wgt->imageTransform.verFlip);
    }
}


template<class T>
inline const T& kClamp( const T& x, const T& low, const T& high )
{
    if ( x < low )       return low;
    else if ( high < x ) return high;
    else                 return x;
}

inline
int changeBrightness( int value, int brightness )
    {
    return kClamp( value + brightness * 255 / 100, 0, 255 );
    }

inline
int changeContrast( int value, int contrast )
    {
    return kClamp((( value - 127 ) * contrast / 100 ) + 127, 0, 255 );
    }

inline
int changeGamma( int value, int gamma )
    {
    return kClamp( int( pow( value / 255.0, 100.0 / gamma ) * 255 ), 0, 255 );
    }

inline
int changeUsingTable( int value, const int table[] )
    {
    return table[ value ];
    }

template< int operation( int, int ) >
static
QImage changeImage( const QImage& image, int value )
    {
    QImage im = image;
    im.detach();
    if( im.numColors() == 0 ) /* truecolor */
        {
        if( im.format() != QImage::Format_RGB32 ) /* just in case */
            im = im.convertToFormat( QImage::Format_RGB32 );
        int table[ 256 ];
        for( int i = 0;
             i < 256;
             ++i )
            table[ i ] = operation( i, value );
        if( im.hasAlphaChannel() )
            {
            for( int y = 0;
                 y < im.height();
                 ++y )
                {
                QRgb* line = reinterpret_cast< QRgb* >( im.scanLine( y ));
                for( int x = 0;
                     x < im.width();
                     ++x )
                    line[ x ] = qRgba( changeUsingTable( qRed( line[ x ] ), table ),
                        changeUsingTable( qGreen( line[ x ] ), table ),
                        changeUsingTable( qBlue( line[ x ] ), table ),
                        changeUsingTable( qAlpha( line[ x ] ), table ));
                }
            }
        else
            {
            for( int y = 0;
                 y < im.height();
                 ++y )
                {
                QRgb* line = reinterpret_cast< QRgb* >( im.scanLine( y ));
                for( int x = 0;
                     x < im.width();
                     ++x )
                    line[ x ] = qRgb( changeUsingTable( qRed( line[ x ] ), table ),
                        changeUsingTable( qGreen( line[ x ] ), table ),
                        changeUsingTable( qBlue( line[ x ] ), table ));
                }
            }
        }
    else
        {
        QVector<QRgb> colors = im.colorTable();
        for( int i = 0;
             i < im.numColors();
             ++i )
            colors[ i ] = qRgb( operation( qRed( colors[ i ] ), value ),
                operation( qGreen( colors[ i ] ), value ),
                operation( qBlue( colors[ i ] ), value ));
        }
    return im;
    }
//0--------------------------------------//
// brightness is multiplied by 100 in order to avoid floating point numbers
QImage changeBrightness( const QImage& tempImage, int brightness )
    {
    if( brightness == 0 ) // no change
        return tempImage;
    return changeImage< changeBrightness >( tempImage, brightness );
    }

// contrast is multiplied by 100 in order to avoid floating point numbers
QImage changeContrast( const QImage& tempImage, int contrast )
    {
    if( contrast == 100 ) // no change
        return tempImage;
    return changeImage< changeContrast >( tempImage, contrast );
    }

// gamma is multiplied by 100 in order to avoid floating point numbers
QImage changeGamma( const QImage& tempImage, int gamma )
    {
    if( gamma == 100 ) // no change
        return tempImage;
    return changeImage< changeGamma >(tempImage, gamma );
    }
//---------------------------------------//

QImage EImageBase::changeGammaImg( const QImage& tempImage, int gamma ){
    return changeGamma(tempImage, gamma);
}
QImage EImageBase::changeBrightnessImg( const QImage& tempImage, int gamma ){
    return changeBrightness(tempImage, gamma);
}
QImage EImageBase::changeContrastImg(const QImage& tempImage, int gamma ){
    return changeContrast(tempImage, gamma);
}



void EImageBase::setImageType(int type){
    chImageMode(type);
}

void EImageBase::manipDestroed(){
    manipulatorIsClosed = true;
}

void EImageBase::setFullscreenMode(bool val){
    emit fullscreenMode(val);
    if (val){
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        wgt->widthScrBar->setVisible(false);
        wgt->heightScrBar->setVisible(false);
       // saveWholePic->setEnabled(true);
       // saveCatPic->setEnabled(false);
    }
    else{
       //// setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
       //// setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        wgt->widthScrBar->setVisible(true);
        wgt->heightScrBar->setVisible(true);
      //  saveWholePic->setEnabled(false);
     //   saveCatPic->setEnabled(true);
    }
    wgt->setFullscreenMode(val);
    setScale(1);
}


void  EImageBase::sendTimer(int time){
    _timer = time;
    emit timerSignal(time);
}

double EImageBase::imageWidth(){
    if (picMode->getPictureMode() == ImagePictureMode::IS_RGBGRAY)
        return dimX/picMode->lastDelimetr;

    return dimX/picMode->getDelimitr();
}

double EImageBase::imageHeight(){
    return dimY;
}

QImage EImageBase::errorImage(){
    QString errText = "ERROR!";
    QImage tempImage(500, 500, QImage::Format_ARGB32);
    QPainter painter(&tempImage);
    painter.drawText(25, 25, errText);
    painter.end();
    return tempImage;
}

QImage EImageBase::setImageByFullScreenMode(QImage img){
    return wgt->setImageByFullScreenMode(img);
}

void EImageBase::drawing(QImage& img){
    wgt->drawing(img);
}

QImage EImageBase::setPropertiesOnImg(QImage img){
    img = setImageByFullScreenMode(img);
    img = setVisualPropertiesOnImg(img);
    return img;
}

QImage EImageBase::setPropertiesOnImg(QImage img, QVariant* p){
    img = setImageByFullScreenMode(img);
    if (ImagePictureMode::IS_48BIT || ImagePictureMode::IS_8BIT || ImagePictureMode::IS_RGB){
        img = changeContrastImg(img, p[3].toInt());
        img = changeGammaImg(img, p[1].toInt());
        img = changeBrightnessImg(img, p[2].toInt());
    }
    if (p[0].toInt() != 0)
        img = wgt->changeRotateImg(img, p[0].toInt());
    if (__serverMode == READ_WITH_SERVERTRANSFORMATION){

    if ((!p[5].toBool() && getHFlip()) || (p[5].toBool() && !getHFlip()))
          img = wgt->chHorFlip(img);
    if ((p[4].toBool() && !serverValues[4]) || (!p[4].toBool() && serverValues[4]))
          img = wgt->chVerFlip(img);
    } else {
        if (getHFlip())
              img = wgt->chHorFlip(img);
        if (getVFlip())//
              img = wgt->chVerFlip(img);
    }
    return img;
}

QImage EImageBase::setVisualPropertiesOnImg(QImage img){
    if (ImagePictureMode::IS_48BIT || ImagePictureMode::IS_8BIT || ImagePictureMode::IS_RGB){
        img = changeContrastImg(img, imageParams.contrast);
        img = changeGammaImg(img, imageParams.gamma);
        img = changeBrightnessImg(img, imageParams.brightness);
    }
    img = wgt->setTransformPropertiesOnImg(img);
    return img;
}


void EImageBase::drawHistogram(){
    if (!manipulatorIsClosed){
        if (picMode->getPictureMode() == ImagePictureMode::IS_16BITGRAY){
            if (val16.size() !=0)
                manip->histogram->drawHistogram(val16);
            else
                qDebug("EImage::drawHistogram: val16 is Empty");
        }
        else{
            if (val.size() != 0)
                manip->histogram->drawHistogram(wgt->image);
        else
                qDebug("EImage::drawHistogram: val is Empty");
        }
    }
    else{
       // qDebug("Manipulator is not inited");
    }

}

double EImageBase::getRotate() {return wgt->imageTransform.rotate;}
bool EImageBase::getHFlip(){return wgt->imageTransform.horFlip;}
bool EImageBase::getVFlip(){return wgt->imageTransform.verFlip;}
double EImageBase::getScale(){return wgt->imageTransform.imageScale;}
int EImageBase::getBrightness(){return imageParams.brightness;}
int EImageBase::getGamma(){return imageParams.gamma;}
int EImageBase::getContrast(){return imageParams.contrast;}

void EImageBase::onScreenReapinting(QPoint p)
{
    if (p.x() > wgt->picW) {
        p.setX(wgt->picW);
    }
    if (p.y() > wgt->picH) {
        p.setY(wgt->picH);
    }
    if (p.x() < 0) {
        p.setX(0);
    }
    if (p.y() < 0) {
        p.setY(0);
    }
    emit mousePosition(p);
    int r = p.x() + dimX * p.y();
    int rgb = 3 * p.x() + dimX * p.y();
    if (rgb < 0) {
        r = 0;
        rgb = 0;
    }
    if (val.size() == 0) {
        QRgb pointColor = wgt->image.pixel(p);
        emit rgbImageColor(qRed(pointColor), qGreen(pointColor), qBlue(pointColor));
        return;
    }
    switch (picMode->getPictureMode()) {
    case ImagePictureMode::IS_16BITGRAY:
        if (val16.size()>r && val16.size() !=0) emit greyscaleImageColor(val16.at(r));
        break;
    case ImagePictureMode::IS_RGBGRAY :
        if(val.size() < rgb+2){
            emit greyscaleImageColor(0);
        } else if (val.size()>rgb  && val.size() !=0) {
            emit greyscaleImageColor(0.2126 * val.at(rgb) + 0.7152 * val.at(rgb+1) + 0.0722 * val.at(rgb+2));
        } else {
            emit greyscaleImageColor(0);
        }
        break;
    case ImagePictureMode::IS_8BIT :
        if (val.size()>r  && val.size() !=0) emit greyscaleImageColor(val.at(r));
        else emit greyscaleImageColor(0);
        break;
    case ImagePictureMode::IS_RGB:
    {
        if (val.size() < rgb + 2) {
            emit rgbImageColor(0,0,0);
        } else if (val.size() > rgb && val.size() != 0) {
            emit rgbImageColor(val.at(rgb), val.at(rgb + 1), val.at(rgb + 2));
        } else {
            emit rgbImageColor(0,0,0);
        }
        break;
    }
    case ImagePictureMode::IS_48BIT :
        if(val16.size() < rgb+2){
         emit rgbImageColor(0,0,0);}
        else if (val16.size()>rgb  && val16.size() !=0) emit rgbImageColor(val16.at(rgb), val16.at(rgb+1), val16.at(rgb+2));
        else emit rgbImageColor(0,0,0);
    }
}

void EImageBase::onNewMarker(ImageMarker* m){
    QPoint p(m->_x, m->_y);
    emit newMarker(p, m->_clr);
}

void EImageBase::setMarker(QPoint p, QRgb col){
    wgt->initMarker(QPoint(-1000,-1000));
    wgt->marker.last()->_xOnPic = p.x();
    wgt->marker.last()->_yOnPic = p.y();
    wgt->marker.last()->setMarkerColor(col);
    wgt->marker.last()->menuAction()->setText("Marker["+QString().number(p.x())+";"+QString().number(p.y())+"]");
    wgt->recalcMarkerPos();
}
