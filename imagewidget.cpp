#include "imagewidget.h"
#include <QFileDialog>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

void ImageWidget::init(){
    move(0,30);
    manip = new ImgManipulation();
    setAutoFillBackground(true);
    setMouseTracking(true);
    qDebug("In ImageWidget constructor");
    imgType = IS_RGBIMG_COLOR;
    picMode = new IsRGB();
    isMarked = false;

    marker = new QAction(tr("&Set Marker"), this);
    marker->setStatusTip(tr("Set Marker"));
    QObject::connect(marker, SIGNAL(triggered()), this, SLOT(allowNewMarker()));
    contextMenuSetMarker.addAction(marker);
}

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent)
{
    _originSnap = NULL;
    img  = new QImage();
    _OriginImg = NULL;
    init();

}

ImageWidget::ImageWidget(QImage* image, QWidget *parent) : QWidget(parent){
    qDebug("In ImageWidget constructor2");
    img  = new QImage();
    *img = *image;
    _OriginImg = new QImage();
    *_OriginImg = *img;
    _originSnap= new QImage();
    *_originSnap = *img;
    resizeWgt(img->width(), img->height());
    qDebug("In ImageWidget constructor2");
    init();
}

ImageWidget::~ImageWidget(){
    qDebug("In ImageWidget destructor");
    delete manip;
    delete img;
    delete _OriginImg;
    delete picMode;

    delete _originSnap;
    delete marker;
}

void ImageWidget::resizeWgt(int x, int y){
    resize(x, y);
    paintImg(*img);
}

void ImageWidget::paintImg(QImage& img){
    hide();
    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(img));
    setPalette(pal);
    show();
}

void ImageWidget::makeSnpFromWgt(){
   // emit mkSnapshotRealtime(this);
}

void ImageWidget::makeSnpFromImg(){
   // emit mkSnapshotRealtime(img, manip);
}

/*void ImageWidget::changeImg(int param){
    switch(param){
        case BRIGHTNESS:{
            *img = manip->chBrightness(*img, manip->getBrightnessVal());
        }
        break;
        case SCALE:{
            QImage tempSclImg;
            tempSclImg = manip->chScale(*img, manip->getScaleVal());
            if (!tempSclImg.isNull()){
                *img = tempSclImg;
            }
            else{
                qDebug("Error, changeImg::Scaled Failed!!!!");
            }
        }
        break;
        case GAMMA:{
            *img = manip->chGamma(*img, manip->getGammaVal());
        }
        break;
        case CONTRAST:{
            *img = manip->chContrast(*img, manip->getContrastVal());
        }
        break;
        case ROTATION:{
            *img = manip->chRotate(*img, manip->getRotationVal());
        }
        break;
        case VER_FLIP:{
            *img = manip->chVerFlip(*img, manip->getVerFlipVal());
        }
        break;
        case HOR_FLIP:{
            *img = manip->chHorFlip(*img, manip->getHorFlipVal());
        }
        break;
    }
    resizeWgt(img->width(), img->height());emit resizeImgWgt(img->width(), img->height());
}
*/

void ImageWidget::setClientValues(){
    QImage tempImg;
    tempImg = *img;
    if (img->format() != QImage::Format_Indexed8){
        if (manip->getContrastVal() !=100){
            tempImg = manip->chContrast(tempImg, manip->getContrastVal());
        }
        if (manip->getGammaVal() !=100){
            tempImg = manip->chGamma(tempImg, manip->getGammaVal());
        }
        if (manip->getBrightnessVal() != 0){
            tempImg = manip->chBrightness(tempImg, manip->getBrightnessVal());
        }
    }
    if (manip->getScaleVal() != 1.0){
        QImage tempSclImg;
        tempSclImg = manip->chScale(tempImg, manip->getScaleVal());
        if (!tempSclImg.isNull()){
            tempImg = tempSclImg;
        }
        else{
            qDebug("Error, setClientValues :: Scaled Failed!!!!");
        }
    }
    if (manip->getRotationVal() != 0){
        tempImg = manip->chRotate(tempImg, manip->getRotationVal());
    }
    if (manip->getVerFlipVal()){
        tempImg = manip->chVerFlip(tempImg, manip->getVerFlipVal());
    }
    if (manip->getHorFlipVal()){
        tempImg = manip->chHorFlip(tempImg, manip->getHorFlipVal());
    }
    *img = tempImg.copy();
    //img->invertPixels(QImage::InvertRgb);

  //  resizeWgt(img->width(), img->height());
    emit resizeImgWgt(img->width(), img->height());

}

void ImageWidget::setAllValues(int ){
    QImage tempImg;
    tempImg = *_OriginImg;
    if (tempImg.format() != QImage::Format_Indexed8){
        if (manip->getContrastVal() !=100){
            tempImg = manip->chContrast(tempImg, manip->getContrastVal());
        }
        if (manip->getGammaVal() !=100){
            tempImg = manip->chGamma(tempImg, manip->getGammaVal());
        }
        if (manip->getBrightnessVal() != 0){
            tempImg = manip->chBrightness(tempImg, manip->getBrightnessVal());
        }
    }
    if (manip->getScaleVal() != 1.0){
        QImage tempSclImg;
        tempSclImg = manip->chScale(tempImg, manip->getScaleVal());
        if (!tempSclImg.isNull()){
            tempImg = tempSclImg.copy();
        }
        else{
            qDebug("Error, setAllValues :: Scaled Failed!!!!");
        }
    }
    if (manip->getRotationVal() != 0){
        tempImg = manip->chRotate(tempImg, manip->getRotationVal());
    }
    if (manip->getVerFlipVal()){
        tempImg = manip->chVerFlip(tempImg, manip->getVerFlipVal());
    }
    if (manip->getHorFlipVal()){
        tempImg = manip->chHorFlip(tempImg, manip->getHorFlipVal());
    }
    *img = tempImg;
    resizeWgt(tempImg.width(), tempImg.height());
    emit resizeImgWgt(tempImg.width(), tempImg.height());
}

void ImageWidget::saveImg(){
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
        if (imgType != IS_16BITIMG_GREY){
            img->save(filename);
            //cv::Mat image( ImgDimY,  ImgDimX, CV_8UC4,  &valUSh.front());  // read from value in realtime->makeimg, set correct CV_8UC!!
        }
        else{
            QString f = (QString)filename.split(".").takeFirst() +    "_16Bit" +
                    QString(".") + selectedFilter.split("(").takeFirst().toLower();
            bool s = this->img->save(f);
            //cv::Mat img(ImgDimY, ImgDimX, CV_16UC1,  &valUSh.front());
            cv::Mat img( originHeight,  originWidth, CV_16UC1,  &valUSh.front());
            cv::imwrite(filename.toAscii().constData(), img);
        }
        qDebug("Save an Image\n");
    }
    else
        qDebug( "Saving an Image is canceled\n");
}

void ImageWidget::printImg(){
    qDebug( "Warring, Here IMG mus be printed!!!!!!!\n");
}

//on mouse press event at picture widget
void ImageWidget::mousePressEvent ( QMouseEvent * e){
    if (e->button() == Qt::LeftButton ){
        setMarker(e->pos());
        qDebug("ImageWidget::mousePressEvent\n");
    }
}

void ImageWidget::rescreen(){
    repaint();
}

////on mouse move event at picture widget
void ImageWidget::mouseMoveEvent ( QMouseEvent * e){
    _curMouseX = e->x();
    _curMouseY = e->y();
    emit repainting();
    int X=_curMouseX, Y=_curMouseY;
    calcRealPosition(X,Y);
    //recalcPosition(X,Y);

    emit mousePosition(X/manip->listProp.at(SCALE)->getValue().toDouble(), Y/manip->listProp.at(SCALE)->getValue().toDouble());
    if (!img->isNull() && img->valid(_curMouseX,_curMouseY)){
        if (imgType == IS_16BITIMG_GREY ){
       //     if (manip->getScaleVal() == 1){  //temperary if-else!!!!!!
                    emit mousePositionVal(qRed(img->pixel(_curMouseX,_curMouseY)), valUSh[X*Y+X] );
         //   }
        //    else
         //      emit mousePositionVal(qRed(img->pixel(_curMouseX,_curMouseY)), 99999 );
        }
        else if (imgType == IS_RGBIMG_GREY || imgType == IS_8BITIMG_GREY || imgType == IS_8BITIMG_COLOR){
            emit mousePositionVal(qRed(img->pixel(_curMouseX, _curMouseY)));
        }
        else{
            emit mousePositionVal(qRed(img->pixel(_curMouseX,_curMouseY)), qGreen(img->pixel(_curMouseX,_curMouseY)), qBlue(img->pixel(_curMouseX,_curMouseY)));
        }
        qDebug("ImageWidget::mouseMoveEvent\n");
    }
    else{qDebug("ImageWidget::mouseMoveEvent  BAD\n");}
}

void ImageWidget::recalcPosition(int &X, int &Y){
    if (manip->getRotationVal() == 90 || manip->getRotationVal() == -270){
        int A = X;
        X=img->width()-Y;
        Y=A;
    }
    if (manip->getRotationVal() == 270 || manip->getRotationVal() == -90){
         int A = X;
        X = Y;
        Y = img->height()-A;
    }
    if (manip->getVerFlipVal()){
        Y = img->height()-Y;
    }
    if (manip->getHorFlipVal()){
        X = img->width()-X;
    }
    if (manip->getRotationVal() == 180 || manip->getRotationVal() == -180){
        Y = img->height()-Y;
        X = img->width()-X;
    }
}


//on paint event
void ImageWidget::paintEvent( QPaintEvent * e){
    QPainter p(this);
    p.setPen(QPen(Qt::yellow, 2));
    p.drawLine(0, _curMouseY, this->width(), _curMouseY);
    p.drawLine(_curMouseX, 0, _curMouseX, this->height());
    qDebug( "ImageWidget::paintEvent\n");
    if (isMarked){
        p.setPen(QPen(Qt::red, 1));
        int Y = _clickedMouseY*manip->listProp.at(SCALE)->getValue().toDouble();
        int X = _clickedMouseX*manip->listProp.at(SCALE)->getValue().toDouble();
        recalcPosition(X, Y);
        p.drawLine(0, Y, this->width(), Y);
        p.drawLine(X, 0, X, this->height());
    }
}

void ImageWidget::setImgType(int type){
    imgType  = type;
}

void ImageWidget::set16BitImgGreyMode(){
    imgType = IS_16BITIMG_GREY;
    picMode = new Is16BitGrey();
}
void ImageWidget::setRGBImgGreyMode(){
    imgType = IS_RGBIMG_GREY;
    valUSh.erase(valUSh.begin(), valUSh.end());
    picMode = new IsRGBGGrey();
}
void ImageWidget::setRGBImgColorMode(){
    imgType = IS_RGBIMG_COLOR;
    valUSh.erase(valUSh.begin(), valUSh.end());
    picMode = new IsRGB();
}

void ImageWidget::set8BitImgGreyMode(){
    imgType = IS_8BITIMG_GREY;
    valUSh.erase(valUSh.begin(), valUSh.end());
    picMode = new Is8BitGrey();
}
void ImageWidget::set8BitImgColorMode(){
    imgType = IS_8BITIMG_COLOR;
    valUSh.erase(valUSh.begin(), valUSh.end());
    picMode = new Is8BitColor();
}

void ImageWidget::setPicSize(int x, int y){
    originWidth = x;
    originHeight = y;
}

void ImageWidget::setPicSetings(int x, int y){
    ImgDimX = x;
    ImgDimY = y;
}

void ImageWidget::recalcGreyImg(vector <unsigned char> &valData, int X, int Y){
    vector<unsigned char> valDataRecalced;
    picMode->recalcColors(valData, valDataRecalced);
    if (valDataRecalced.size() == 0)
        *img = picMode->recalcGreyImg(X, Y, valData);
    else
        *img = picMode->recalcGreyImg(X, Y, valDataRecalced);
}

void ImageWidget::recalcGreyImg16Bit(){
    vector<unsigned char> valData;
    picMode->Convert16BitData(valUSh, valData);
   *img = picMode->recalcGreyImg(ImgDimX, ImgDimX, valData);
}

void ImageWidget::setOriginImg(){
    manip->chScale(*img, manip->listProp.at(SCALE)->getValue().toDouble());
    *_OriginImg = *img;
}


void ImageWidget::calcGreyImg(){
        if (imgType == IS_16BITIMG_GREY){
            recalcGreyImg16Bit();
        }
        else{
            int X,Y;
            vector<unsigned char> valData;
            X = _originSnap->width();
            Y = _originSnap->height();
            getImageVector(valData, X, Y);
            recalcGreyImg(valData, X, Y);
        }
        setOriginImg();
}

void ImageWidget::getImageVector(vector<unsigned char>& val, int w, int h){
     unsigned char* line = NULL;
     for (int i = 0; i<h; i++){
         line = _originSnap->scanLine( i );
         for( int x = 0;  x < w;  ++x ){
             val.push_back(line[x]);
         }
     }
}

void ImageWidget::setScaleSnap( double val){
    QImage tempImg;
    tempImg = manip->chScale(*_originSnap, _originSnap->width()*val, _originSnap->height()*val);
    if (!tempImg.isNull()){
       *img = tempImg;
       manip->listProp.at(SCALE)->setValue(val);
       resizeWgt(img->width(), img->height());
    }
    else{
        qDebug("Error in Scaling Snap");
    }
}

void ImageWidget::resetClientSideVal(){
    *img = *_originSnap;
    manip->resetParam(*img);
}

void ImageWidget::calcFullPictureScale(int width, int height, int space){
    int minSide;
    if (img->height() != height || img->width() != width){
        double coef = 1.0;
        minSide = (double)height-space;
        coef = minSide/(double)ImgDimY;
        manip->listProp.at(SCALE)->setValue(coef);
        emit sendScale(coef);
    }
}


void ImageWidget::setMarker(QPoint pos){
    QPoint globalPos = this->mapToGlobal(pos);
    contextMenuSetMarker.popup(globalPos);
}

void ImageWidget::allowNewMarker(){
    int X = _curMouseX, Y=_curMouseY;
    calcRealPosition(X,Y);
    QString str = QString("Marker: X=" + QString().number(int(X/manip->listProp.at(SCALE)->getValue().toDouble())) + ";Y=" + QString().number(int(Y/manip->listProp.at(SCALE)->getValue().toDouble())));
    emit sendMarker(str);

      X = _curMouseX;
      Y = _curMouseY;
             if (manip->getRotationVal() == 90 || manip->getRotationVal() == -270){
                 int A = X;
                 X = Y;
                 Y=  img->width() - A;
             }
             if (manip->getRotationVal() == 270 || manip->getRotationVal() == -90){
                 int A = X;
                 X = img->height()-Y;
                 Y = A;
             }

             if (manip->getRotationVal() == 180 || manip->getRotationVal() == -180 ){
                 Y = img->height()-Y;
                 X = img->width()-X;
             }
             if (manip->getVerFlipVal() && (manip->getRotationVal() == 180 || manip->getRotationVal() == -180 )){
                 Y = img->height()-Y;
             }
             else if (manip->getVerFlipVal() && manip->getRotationVal() == 0){
                 Y = img->height()-Y;
             }
             else if(manip->getVerFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
                 X = img->height() - X;
             }
             else if(manip->getVerFlipVal() && (manip->getRotationVal() == 90 || manip->getRotationVal() == -270)){
                 X = img->height()-X;
                 Y = Y;;
             }


             if (manip->getHorFlipVal() && (manip->getRotationVal() == 180 || manip->getRotationVal() == -180)){
                 X = img->width()-X;
             }
             else if (manip->getHorFlipVal() && manip->getRotationVal() == 0){
                 X = img->width()-X;
             }
             else if(manip->getHorFlipVal() && (manip->getRotationVal() == 90 || manip->getRotationVal() == -270)){
                 X = X;
                 Y = img->width()-Y;
             }
             else if(manip->getHorFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
                 X = X;
                 Y = img->width()-Y;
             }

    _clickedMouseX = X/manip->listProp.at(SCALE)->getValue().toDouble();
    _clickedMouseY = Y/manip->listProp.at(SCALE)->getValue().toDouble();

    isMarked = true;
}









void ImageWidget::calcRealPosition(int &X, int &Y){
    int diff = (ImgDimX-ImgDimY)*manip->listProp.at(SCALE)->getValue().toDouble();
    ////////////////////////////////////////////////
    if (manip->getRotationVal() == 90 || manip->getRotationVal() == -270){
        int A = X;
        X=Y;
        Y=img->height()-A-diff;
    }
    if (manip->getRotationVal() == 270 || manip->getRotationVal() == -90){
         int A = X;
        X = img->width()-Y + diff;
        Y = A;
    }
    if (manip->getRotationVal() == 180 || manip->getRotationVal() == -180){
        Y = img->height()-Y;
        X = img->width()-X;
    }
    ////////////////////////////////////////////////
    if (manip->getVerFlipVal() && (manip->getRotationVal() == 90 || manip->getRotationVal() == -270)){
        X = img->height()-X;
    }
    else if (manip->getVerFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
       Y = Y;
       X = img->width()-X + diff;
    }
    else if (manip->getVerFlipVal()){
        Y = img->height()-Y;
    }
    ////////////////////////////////////////////////
    if (manip->getHorFlipVal() && (manip->getRotationVal() == 90 || manip->getRotationVal() == -270)){
        Y = img->height() - Y - diff;
    }
    else if (manip->getHorFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
        Y = img->height() - Y - diff;
    }
    else if (manip->getHorFlipVal()){
        X = img->width()-X;
    }

}






void ImageWidget::convertPosFromImageSize(int &X, int &Y){
    if (manip->getRotationVal() == 90 || manip->getRotationVal() == -270){
            int A = X;
            X=ImgDimY-Y;
            Y=A;
        }


    if (manip->getVerFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
            int temp = X;
            X = Y;
            Y = temp;

            int A = X;
            X = Y;
            Y = ImgDimX-A;
    }
    else if (manip->getHorFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
        int A = X;
        X = Y;
        Y = ImgDimX-A;
    }
     else   if (manip->getRotationVal() == 270 || manip->getRotationVal() == -90){
            int A = X;
            X = Y;
            Y = ImgDimX-A;
        }


        if (manip->getRotationVal() == 180 || manip->getRotationVal() == -180){
            Y = ImgDimY-Y;
            X = ImgDimX-X;
        }


        /////////////////////////////////////
        if(manip->getVerFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
                int A = X;
                X = Y;
                Y = ImgDimX -A;

                X = ImgDimX - X;
                Y = A;
        }
        else if(manip->getVerFlipVal() && (manip->getRotationVal() == 90 || manip->getRotationVal() == -270)){
                Y = ImgDimX-Y;
        }
        else if (manip->getVerFlipVal()){
              Y = ImgDimY-Y;
        }

//////////////////////////////////
        if(manip->getHorFlipVal() && (manip->getRotationVal() == 270 || manip->getRotationVal() == -90)){
            X = ImgDimY - X;
        }
        else if(manip->getHorFlipVal() && (manip->getRotationVal() == 90 || manip->getRotationVal() == -270)){
                 X = ImgDimY-X;
        }
        else if (manip->getHorFlipVal()){
            X = ImgDimX-X;
        }
}

