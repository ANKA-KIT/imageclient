#include "eimagescreen.h"

#include <QPainter>
#include <QDebug>
#include "imagemarker.h"

EImageScreen::EImageScreen(QWidget *p) : QWidget(p)
{
    setFullscreenMode(false);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    moveX = moveY = 0;
    imageTransform.imageScale= 1;
    imageTransform.rotate = 0;
    imageTransform.horFlip= imageTransform.verFlip  = false;
    connect(this,SIGNAL(currentPos(int,int)),this,SLOT(setCursorPos(int,int)));
    contextMenu = new QMenu("Image", this);
    lButtonPresed=false;
    curYPos=curXPos=0;
    connect(this, SIGNAL(showPictureSize(int,int,int,int)), SLOT(setLimits(int,int,int,int)));
    connect(this,SIGNAL(imgTransformed(QImage)),SLOT(recalcMarkerPos()));

    heightScrBar = new QScrollBar(this);
    widthScrBar = new QScrollBar(this);
    widthScrBar->setOrientation(Qt::Horizontal);
    connect(widthScrBar, SIGNAL(sliderMoved(int)), this, SLOT(setMoveX(int)));
    connect(heightScrBar, SIGNAL(sliderMoved(int)), this, SLOT(setMoveY(int)));
    connect(heightScrBar, SIGNAL(valueChanged(int)), this, SLOT(setMoveY(int)));
    connect(widthScrBar, SIGNAL(valueChanged(int)), this, SLOT(setMoveX(int)));

}

void EImageScreen::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        double a;
        a = event->delta()/120;
        emit chScaleByWheel(a*0.05);
        emit moveXSignal((event->x() - width()/2)/5);
        emit moveYSignal((event->y() - height()/2)/5);
    }
}

void EImageScreen::mouseMoveEvent(QMouseEvent * event)
{
    int curX = event->x();
    int curY = event->y();
    emit repainting();
    emit currentPos(curX,curY);
}

void EImageScreen::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton) {
        curXPos = e->x();
        curYPos = e->y();
        lButtonPresed = true;
    }
    if (e->button() == Qt::RightButton) {
        contextMenu->popup(e->globalPos());
    }
}

void EImageScreen::mouseReleaseEvent(QMouseEvent * event)
{
  if (event->button() == Qt::LeftButton)
    lButtonPresed = false;
}

void EImageScreen::setRotate(double val)
{
    imageTransform.rotate = val;
    emit imgTransformed(image);
    emit imgChanged(image);
}

void EImageScreen::setHFlip(bool val)
{
    imageTransform.horFlip=val;
    emit imgTransformed(image);
    emit imgChanged(image);
}

void EImageScreen::setVFlip(bool val){
    imageTransform.verFlip= val;
    emit imgTransformed(image);
    emit imgChanged(image);
}

void EImageScreen::setCursorPos( int x, int y){
    _curMouseX = x;
    _curMouseY = y;
}

void EImageScreen::onMarkerDelete(ImageMarker *pointer){
    QList<ImageMarker*>::iterator iter;
    for (iter = marker.begin(); iter < marker.end(); ++iter){
         if (pointer == *iter){
            emit delMarker(QPoint(pointer->_xOnPic,pointer->_yOnPic), pointer->_clr);
            marker.erase(iter);
            // HACK: we know that currently the setMarkerAction is at actions[1]
            contextMenu->actions()[1]->setEnabled(true);
            return;
        }
    }
}

void EImageScreen::rescreen()
{
    repaint();
}

QImage EImageScreen::chScale(QImage &image, double val)
{
    return image.scaled(image.width() * val, image.height() * val);
}

QImage EImageScreen::chScale(QImage &image, double valX, double valY)
{
    QImage tempImg;
    tempImg = image.scaled(image.width() * valX, image.height() * valY);
    return tempImg;
}

QImage EImageScreen::chHorFlip(QImage &image)
{
    QImage tempImg;
    QMatrix mat;
    mat = QMatrix().scale(-1, 1); // make a horizontal flip
    tempImg = image.transformed(mat);
    return tempImg;
}

QImage EImageScreen::chVerFlip(QImage &image)
{
    QImage tempImg;
    QMatrix mat;
    mat = QMatrix().scale(1, -1); // make a vertical flip
    tempImg = image.transformed(mat);
    return tempImg;
}

void EImageScreen::setMarkersOnPic(bool fullPic, QImage &imgPtr){
    int visX, visY, clr;
    for (int m=0; m<marker.count(); m++){
        double scl;
        scl =  imageTransform.fullPictureMode ? 1:imageTransform.imageScale;
        int vLineLength = marker.at(m)->vLineLength *scl;
        int hLineLength = marker.at(m)->hLineLength *scl;

        vLineLength = vLineLength==0 ? 1:vLineLength;
        hLineLength = hLineLength==0 ? 1:hLineLength;
        clr = marker.at(m)->_clr;

        if (!imageTransform.fullPictureMode){
            if (!fullPic){
                visX = marker.at(m)->visiableXPos;
                visY = marker.at(m)->visiableYPos;
            }
            else{
                visX = marker.at(m)->_xOnPic;
                visY = marker.at(m)->_yOnPic;

                switch((int)imageTransform.rotate){
                case 90:
                case -270:
                        visX = picH - marker.at(m)->_yOnPic;
                        visY = marker.at(m)->_xOnPic;
                            break;
                case -90:
                case 270:
                    visX = marker.at(m)->_yOnPic;
                    visY = picW - marker.at(m)->_xOnPic;
                    break;
                case 180:
                case -180:
                    visY = picH - marker.at(m)->_yOnPic;
                    visX  = picW - marker.at(m)->_xOnPic;
                    break;
                default:
                    visX = marker.at(m)->_xOnPic;
                    visY  = marker.at(m)->_yOnPic;
                }
                    if (imageTransform.horFlip  && imageTransform.verFlip ){
                        if (!isPi2rotated){
                            visX = picW - visX;
                            visY = picH - visY;
                        }
                        else{
                            visX = picH - visX;
                            visY = picW - visY;
                        }
                    }
                    else if (imageTransform.horFlip ){
                        if (!isPi2rotated)
                            visX = picW - visX;
                        else
                            visX = picH - visX;
                    }
                    else if (imageTransform.verFlip ){
                        if (!isPi2rotated)
                            visY  = picH - visY;
                        else
                            visY  = picW - visY;
                    }
                }

        }
        else{
            if (!fullPic){
                switch((int) imageTransform.rotate){
                    case 90:
                    case -90:
                    case 270:
                    case -270:
                    visX = marker.at(m)->visiableXPos*sclY;
                    visY = marker.at(m)->visiableYPos*sclX;
                    break;
                default:
                    visX = marker.at(m)->visiableXPos*sclX;
                    visY = marker.at(m)->visiableYPos*sclY;
                }
            }
            else{
                visX = marker.at(m)->visiableXPos;
                visY = marker.at(m)->visiableYPos;
            }
        }
        for (int i=0;i<vLineLength;i++){
            imgPtr.setPixel(visX,visY-i, clr);
            imgPtr.setPixel(visX,visY+i, clr);
        }
        for (int i=0;i<hLineLength;i++){
            imgPtr.setPixel(visX-i, visY, clr);
            imgPtr.setPixel(visX+i, visY, clr);
        }
    }
}

void EImageScreen::paintEvent( QPaintEvent * ){
    QPainter p(this);
    p.setPen(QPen(Qt::yellow, 2));
    p.drawLine(_curMouseX-3, _curMouseY, _curMouseX+3, _curMouseY);
    p.drawLine(_curMouseX, _curMouseY-3, _curMouseX, _curMouseY+3);
    if (!imageTransform.fullPictureMode){
        p.setPen(QPen(Qt::red, 1));
        int xxx = 5;
        int yyy = 5;
        int xxxW = 20;
        int yyyH = 20;
        p.drawRect(xxx, yyy, xxxW, yyyH);
        p.setPen(QPen(Qt::green, 1));
        QPoint p1 = QPoint(limX1,limY1);
        QPoint p2 = QPoint(limX2,limY2);
        int xxxx = xxxW*((double)p1.x()/(double)picW);
        int yyyy = yyyH*((double)p1.y()/(double)picH);
        xxxW = xxxW*((double)p2.x()/(double)picW);
        yyyH = yyyH*((double)p2.y()/(double)picH);
        p.drawRect(xxx + xxxx, yyy + yyyy, xxxW-xxxx, yyyH-yyyy);
    }
    QPoint imageCoordinats = convertToImageCoordinates();
    emit mousePosition(imageCoordinats);
    if (marker.count() > 0) {
        int Y = 0;
        int X = 0;

        int cursorWidth;
        for (int i = 0; i < marker.count(); i++) {
            ImageMarker *m = marker.at(i);
            cursorWidth = m->_width * imageTransform.imageScale < 1 ? 1 : m->_width * imageTransform.imageScale;
            p.setPen(QPen(QColor(m->_clr), cursorWidth));

            if (imageTransform.fullPictureMode) {
                if (!isPi2rotated) {
                    Y = m->yTransformed * parentWidget()->height() / (double) picH;
                    X = m->xTransformed * parentWidget()->width() / (double) picW;
                } else {
                    Y = m->yTransformed * height() / picW;
                    X = m->xTransformed * width() / picH;
                }
            } else {
                int limX1Temp = limX1;
                int limX2Temp = limX2;
                int limY1Temp = limY1;
                int limY2Temp = limY2;

                int markedX = m->_x;
                int markedY = m->_y;

                int signXOnFlip = 1;
                int signYOnFlip = 1;

                int sign = signYOnFlip * signXOnFlip;

                if (!isPi2rotated){
                    if (imageTransform.rotate == 0){
                        if (!imageTransform.horFlip && !imageTransform.verFlip){
                            Y = (markedY-limY1Temp)*imageTransform.imageScale;
                            X =  (markedX-limX1Temp)*imageTransform.imageScale;
                        }
                        if (imageTransform.horFlip  && imageTransform.verFlip ){
                            Y = (limY2Temp-markedY)*imageTransform.imageScale;
                            X =  (limX2Temp-markedX)*imageTransform.imageScale;
                        }
                        else if(imageTransform.horFlip ){
                            Y = (markedY-limY1Temp)*imageTransform.imageScale;
                            X =  (limX2Temp-markedX)*imageTransform.imageScale;
                        }
                        else if(imageTransform.verFlip ){
                            Y = (limY2Temp-markedY)*imageTransform.imageScale;
                            X =  (markedX-limX1Temp)*imageTransform.imageScale;
                        }
                    }
                    else{
                        if (!imageTransform.horFlip  && !imageTransform.verFlip ){

                            Y = (limY2Temp-markedY)*imageTransform.imageScale;
                            X =  (limX2Temp-markedX)*imageTransform.imageScale;
                        }
                        if (imageTransform.horFlip  && imageTransform.verFlip ){

                            Y = (markedY-limY1Temp)*imageTransform.imageScale;
                            X =  (markedX-limX1Temp)*imageTransform.imageScale;
                        }
                        else if(imageTransform.horFlip ){

                            Y = (limY2Temp-markedY)*imageTransform.imageScale;
                            X =  (markedX-limX1Temp)*imageTransform.imageScale;
                        }
                        else if(imageTransform.verFlip ){

                            Y = (markedY-limY1Temp)*imageTransform.imageScale;
                            X =  (limX2Temp-markedX)*imageTransform.imageScale;
                        }
                    }
                }
                else{
                    if (imageTransform.rotate == 90 || imageTransform.rotate == -270){
                        if (!imageTransform.horFlip  && !imageTransform.verFlip ){
                            int picY = markedX;
                            int picX = (limY2Temp-limY1Temp)-markedY;

                            Y = (picY-sign*limX1Temp)*imageTransform.imageScale;
                            X =  (picX+sign*limY1Temp)*imageTransform.imageScale;
                        }
                        if (imageTransform.horFlip  && imageTransform.verFlip ){
                            int picY = (limX2Temp-limX1Temp)- markedX;
                            int picX = markedY;

                            Y = (picY+sign*limX1Temp)*imageTransform.imageScale;
                            X =  (picX-sign*limY1Temp)*imageTransform.imageScale;
                        }
                        else if (imageTransform.horFlip ){
                            int picY =  markedX;
                            int picX =  markedY;

                            Y = (picY-sign*limX1Temp)*imageTransform.imageScale;
                            X =  (picX-sign*limY1Temp)*imageTransform.imageScale;
                        }
                        else if (imageTransform.verFlip ){
                            int picY = limX2Temp- markedX;
                            int picX = ((limY2Temp-limY1Temp)-markedY);

                            Y = (picY)*imageTransform.imageScale;
                            X =  (picX+sign*limY1Temp)*imageTransform.imageScale;
                        }
                    }
                    else{
                        if (!imageTransform.horFlip  && !imageTransform.verFlip ){
                            int picY = (limX2Temp-limX1Temp)- sign*markedX;
                            int picX = sign*markedY;

                            Y = (picY+limX1Temp)*imageTransform.imageScale;
                            X =  (picX-limY1Temp)*imageTransform.imageScale;
                        }
                        if (imageTransform.horFlip  && imageTransform.verFlip ){
                            int picY = sign*markedX;
                            int picX = (limY2Temp-limY1Temp)-sign*markedY;

                            Y = (picY-limX1Temp)*imageTransform.imageScale;
                            X =  (picX+limY1Temp)*imageTransform.imageScale;
                        }
                        else if (imageTransform.horFlip ){
                            int picY = limX2Temp- sign*markedX;
                            int picX = ((limY2Temp-limY1Temp)-sign*markedY);

                            Y = (picY)*imageTransform.imageScale;
                            X =  (picX+limY1Temp)*imageTransform.imageScale;
                        }
                        else if (imageTransform.verFlip ){
                            int picY =  sign*markedX;
                            int picX =  sign*markedY;

                            Y = (picY-limX1Temp)*imageTransform.imageScale;
                            X =  (picX-limY1Temp)*imageTransform.imageScale;
                        }
                    }
                }
            }
            if (!imageTransform.fullPictureMode) {
                m->visiableXPos = X;
                m->visiableYPos = Y;
            } else {
                switch ((int) imageTransform.rotate) {
                case 90:
                case -270:
                    m->visiableXPos = picH - m->_yOnPic;
                    m->visiableYPos = m->_xOnPic;
                    break;
                case -90:
                case 270:
                    m->visiableXPos = m->_yOnPic;
                    m->visiableYPos = picW - m->_xOnPic;
                    break;
                case 180:
                case -180:
                    m->visiableYPos = picH - m->_yOnPic;
                    m->visiableXPos = picW - m->_xOnPic;
                    break;
                default:
                    m->visiableXPos = m->_xOnPic;
                    m->visiableYPos = m->_yOnPic;
                }

                if (imageTransform.horFlip  && imageTransform.verFlip ){
                    if (!isPi2rotated){
                        m->visiableXPos = picW - m->visiableXPos;
                        m->visiableYPos = picH - m->visiableYPos;
                    }
                    else{
                        m->visiableXPos = picH - m->visiableXPos;
                        m->visiableYPos = picW - m->visiableYPos;
                    }
                }
                else if (imageTransform.horFlip ){
                    if (!isPi2rotated)
                        m->visiableXPos = picW - m->visiableXPos;
                    else
                        m->visiableXPos = picH - m->visiableXPos;
                }
                else if (imageTransform.verFlip ){
                    if (!isPi2rotated)
                        m->visiableYPos = picH - m->visiableYPos;
                    else
                        m->visiableYPos = picW - m->visiableYPos;
                }

            }
            int hLine = m->hLineLength;
            int vLine = m->vLineLength;
            hLine = hLine < 1 ? 1: hLine * determineScalingFactor(sclX);
            vLine = vLine < 1 ? 1: vLine * determineScalingFactor(sclY);
            // TODO: extract marker and ROI drawing
            // picture == ROI -> marker centered, no ROI drawing needed
            if (m->roiWidth == picW || m->roiHeight == picH) {
                int centeredMarkerX = picW / 2;
                int centeredMarkerY = picH / 2;
                p.drawLine(centeredMarkerX - vLine, centeredMarkerY, centeredMarkerX + vLine, centeredMarkerY);
                p.drawLine(centeredMarkerX, centeredMarkerY - hLine, centeredMarkerX, centeredMarkerY + hLine);
                return;
            }
            // draw marker ROI if set
            if (m->roiWidth > 0 && m->roiHeight > 0) {
                p.setPen(QPen(m->getColor(), 1));
                int scaledHalfWidth = (m->roiWidth / 2) * determineScalingFactor(sclX);
                int scaledHalfHeight = (m->roiHeight / 2) * determineScalingFactor(sclY);

                p.drawRect(X - scaledHalfWidth, Y - scaledHalfHeight, scaledHalfWidth * 2, scaledHalfHeight * 2);
            }
            // draw the marker
            p.drawLine(X - vLine, Y, X + vLine, Y);
            p.drawLine(X, Y - hLine, X, Y + hLine);
        }
    }
}

ImageMarker* EImageScreen::initMarker(QPoint pos) {
    qDebug("imagescreen initMarker");
    ImageMarker *m1 = new ImageMarker(pos.x(),pos.y(), contextMenu);
    m1->_x = pos.x();
    m1->_y = pos.y();
    m1->_xOnPic = pos.x();
    m1->_yOnPic = pos.y();
    connect(m1, SIGNAL(deleteMarker(ImageMarker*)), this, SLOT(onMarkerDelete(ImageMarker*)));
    connect(m1, SIGNAL(colorChangedMarker(ImageMarker*)), this, SLOT(onMarkerColorChanged(ImageMarker*)));
    connect(m1, SIGNAL(resizedMarker(ImageMarker*)), this, SLOT(onMarkerResized(ImageMarker*)));
    connect(m1, SIGNAL(geometryChangedMarker(ImageMarker*)), this, SLOT(onMarkerGeometryChanged(ImageMarker*)));
    marker.push_back(m1);
    contextMenu->addMenu(m1);
    emit newMarker(m1);
    return m1;
}

void EImageScreen::setLimits(int x1,int y1,int x2,int y2){
    limX1 = x1;
    limX2 = x2;
    limY1 = y1;
    limY2 = y2;
}

void EImageScreen::setPi2Rotated(bool value){
    isPi2rotated = value;
}

void EImageScreen::setPicWH(int w,int h){
    picW = w;
    picH=h;
}

void EImageScreen::ShowContextMenu(const QPoint& pos){
    QPoint globalPos = this->mapToGlobal(pos);
    emit rightClickPos(pos);
    contextMenu->popup(globalPos);
}
void EImageScreen::setActionMenu(QList<QAction *> acts){
   contextMenu->addActions(acts);
}

double EImageScreen::getRotate(){
    return imageTransform.rotate;
}

QImage EImageScreen::setImageByFullScreenMode(QImage img)
{
    int picWidth = picW;
    if (!imageTransform.fullPictureMode) {
        moveX = moveX < 0 ? 0 :moveX;
        moveY = moveY < 0 ? 0 : moveY;
        int X1 = moveX, Y1 = moveY, X2, Y2;

    double picsclX = picW*imageTransform.imageScale, picsclY = picH*imageTransform.imageScale;
    double X2scl, Y2scl;
    if(imageTransform.rotate == 90 || imageTransform.rotate == -90 || imageTransform.rotate == -270 || imageTransform.rotate == 270){
        Y2scl = picsclX/parentWidget()->width(), X2scl = picsclY/parentWidget()->height();
    } else {
        X2scl = picsclX/parentWidget()->width(), Y2scl = picsclY/parentWidget()->height();
    }

        if (X2scl < 1 && Y2scl < 1){
             X2 = picWidth;
             Y2 = picH;
        }
        else{
             X2 = picWidth/X2scl;
             Y2 = picH/Y2scl;
        }

        if (X1 + X2 > picWidth){
            X1 = picWidth - X2;
            if(X1<0)
                X1=0;
            moveX=X1;
        }
        if (Y1 + Y2 > picH){
            Y1 = picH - Y2;
            if (Y1 < 0)
                Y1=0;
            moveY=Y1;
        }
        if (Y2>picH)      Y2=picH;
        if (X2>picWidth)  X2=picWidth;

        if (X2 < 10) X2=10;
        if (Y2 < 10) Y2=10;

        img = img.copy(X1,Y1,X2,Y2);
        emit showPictureSize(X1,Y1,X1+X2,Y1+Y2);
        img = chScale(img, imageTransform.imageScale, imageTransform.imageScale);
        if(imageTransform.rotate == 90 || imageTransform.rotate == -90 || imageTransform.rotate == -270 || imageTransform.rotate == 270){
            resize(img.height(),img.width());
        }
        else{
            resize(img.width(),img.height());
        }
    }
    else{
        emit showPictureSize(0,0,picW,picH);
        if(imageTransform.rotate == 90 || imageTransform.rotate == -90 || imageTransform.rotate == -270 || imageTransform.rotate == 270){
            img = chScale(img, (double)parentWidget()->height()/picW, (double)parentWidget()->width()/picH );
            sclX = (double)parentWidget()->height()/picW;
            sclY = (double)parentWidget()->width()/picH;
            resize(img.height(),img.width());
        }
        else{
            img = chScale(img, (double)parentWidget()->width()/picW, (double)parentWidget()->height()/picH);
            sclX = (double)parentWidget()->width()/picW;
            sclY = (double)parentWidget()->height()/picH;
            resize(img.width(),img.height());
        }

    }
    return img;
}

void EImageScreen::setMoveX(int val){
    if (val<0)
        val=0;
    moveX = val;
    emit imgTransformed(image);
}

void EImageScreen::setMoveY(int val){
    if (val<0)
        val=0;
    moveY = val;
    emit imgTransformed(image);
}

void EImageScreen::chMoveXOn(int val){
    switch((int)imageTransform.rotate){
    case -270:
    case 90:
        if (imageTransform.horFlip){setMoveY(moveY + val); }
        else{setMoveY(moveY - val);} break;
    case 270:
    case -90:
        if (imageTransform.horFlip){setMoveY(moveY - val);}
        else{setMoveY(moveY + val);} break;
    case 180:
    case -180:
        if (imageTransform.horFlip){
            setMoveX(moveX + val);}
        else{setMoveX(moveX - val);} break;
    default:
        if (imageTransform.horFlip){
            setMoveX(moveX - val);}
        else{setMoveX(moveX + val);}
    }
}

void EImageScreen::chMoveYOn(int val)
{
    switch((int)imageTransform.rotate){
    case -270:
    case 90:
        if (imageTransform.verFlip){
            setMoveX(moveX - val);}
            else{setMoveX(moveX + val);} break;
    case 270:
    case -90:
        if (imageTransform.verFlip){
            setMoveX(moveX + val);}
        else{setMoveX(moveX - val);} break;
    case 180:
    case -180:
        if (imageTransform.verFlip){
            setMoveY(moveY + val);}
        else{setMoveY(moveY - val); }break;
    default:
        if (imageTransform.verFlip){
            setMoveY(moveY - val);}
        else{setMoveY(moveY + val);}
    }
}

void EImageScreen::drawing(QImage& img)
{
    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(img));
    setPalette(pal);
}

QImage EImageScreen::changeRotateImg(QImage &tempImage, int val)
{
    QTransform mat;
    mat.rotate(val);
    QImage tempImg;
    tempImg = tempImage.transformed(mat);
    return tempImg;
}

void EImageScreen::setFullscreenMode(bool val)
{
    imageTransform.fullPictureMode = val;
    if (!val){
        connect(this,SIGNAL(moveXSignal(int)), this,SLOT(chMoveXOn(int)));
        connect(this,SIGNAL(moveYSignal(int)), this,SLOT(chMoveYOn(int)));
        connect(this,SIGNAL(chScaleByWheel(double)),this, SLOT(chScaleVal(double)));
    }
    else{

        emit showPictureSize(0,0,picW,picH);

        disconnect(this,SIGNAL(moveXSignal(int)), this,SLOT(chMoveXOn(int)));
        disconnect(this,SIGNAL(moveYSignal(int)), this,SLOT(chMoveYOn(int)));
        disconnect(this,SIGNAL(chScaleByWheel(double)),this, SLOT(chScaleVal(double)));
    }
}

void EImageScreen::chScaleVal(double val)
{
    setScale(imageTransform.imageScale + val);
}

void EImageScreen::setScale(double val)
{
    imageTransform.imageScale = val;
    if (imageTransform.imageScale <= 0)
        imageTransform.imageScale = 0.05;
    emit imgTransformed(image);
    emit imgChanged(image);
}

void EImageScreen::initMarker()
{
    QPoint imagePoint = convertToImageCoordinates();
    initMarker(imagePoint);
    recalcMarkerPos();
}

void EImageScreen::recalcMarkerPos()
{
    if (!imageTransform.fullPictureMode) { // set correct size and limit values before recalc Marker position
        setImageByFullScreenMode(image);
    }
    for (int iter = 0; iter < marker.count(); iter++){
        ImageMarker *markerPtr = marker.at(iter);
        QPoint p = convertToImagePoint(markerPtr->_x, markerPtr->_y);
        markerPtr->xTransformed = p.x();
        markerPtr->yTransformed = p.y();
    }
}

QImage EImageScreen::setTransformPropertiesOnImg(QImage img)
{
    if (imageTransform.rotate != 0)
        img = changeRotateImg(img, imageTransform.rotate);
    if (imageTransform.horFlip)
          img = chHorFlip(img);
    if (imageTransform.verFlip)
          img = chVerFlip(img);
    return img;
}

QPoint EImageScreen::convertToImagePoint(int x, int y)
{
    int picWidth = picW;
    int yOld = y, xOld=x;

    switch ((int) imageTransform.rotate) {
    case -270:
    case 90: y =  xOld; setPi2Rotated(true); break;
    case 270:
    case -90: y = picWidth - xOld; setPi2Rotated(true);break;
    case 180:
    case -180: y = picH - yOld;setPi2Rotated(false); break;
    default: setPi2Rotated(false);;
    }

    switch ((int) imageTransform.rotate) {
    case -270:
    case 90: x =   picH -yOld; break;
    case 270:
    case -90: x =  yOld; break;
    case 180:
    case -180: x = picWidth - xOld; break;
    default: ;
    }

    if (imageTransform.horFlip && (imageTransform.rotate == -270 || imageTransform.rotate == 90)){
        x = picH - x;
    }
    else if (imageTransform.horFlip && (imageTransform.rotate == 270 || imageTransform.rotate == -90)){
        x = picH - x;
    }
    else if (imageTransform.horFlip){
        x = picWidth - x;
    }

    if (imageTransform.verFlip && (imageTransform.rotate == -270 || imageTransform.rotate == 90)){
        y = picWidth - y;
    }
    else if (imageTransform.verFlip && (imageTransform.rotate == 270 || imageTransform.rotate == -90)){
        y = picWidth - y;
    }
    else if (imageTransform.verFlip){
        y = picH - y;
    }
    return QPoint(x,y);
}

QPoint EImageScreen::convertToImageCoordinates(){
    int x=_curMouseX, y=_curMouseY;
    int picWidth = picW;
    if (imageTransform.fullPictureMode){

        double a;
        double b;
        switch((int)imageTransform.rotate){
        case -270:
        case 90:
        case 270:
        case -90:
            a = (double)width()/(double)picH;
            b = (double)height()/picWidth;
            break;
        default:
            a = (double)width()/picWidth;
            b = (double)height()/(double)picH;
        }
        ;

        x = (double)_curMouseX /a;
        y = (double)_curMouseY /b;



         int yOld = y, xOld=x;
         switch((int)imageTransform.rotate){
         case -270:
         case 90:
             y = picH - xOld;
             x = yOld;
             setPi2Rotated(true); break;
         case 270:
         case -90:
             x = picWidth - yOld;
             y =  xOld;
             setPi2Rotated(true);break;
         case 180:
         case -180:
             y = picH - yOld;
             x = picWidth - xOld;
             setPi2Rotated(false); break;
         default: setPi2Rotated(false);;
         }
         if (imageTransform.horFlip && (imageTransform.rotate == 90 || imageTransform.rotate == 270 || imageTransform.rotate == -90 || imageTransform.rotate == -270)){
             y = picH - y;
         }
         else if(imageTransform.horFlip){
             x = picWidth - x;
         }

         if (imageTransform.verFlip && (imageTransform.rotate == 90 || imageTransform.rotate == 270 || imageTransform.rotate == -90 || imageTransform.rotate == -270)){
             x = picWidth - x;
         }
        else if (imageTransform.verFlip ){
           y = picH - y;
         }
    }
    else{
        double dopX1 = limX1;
        double dopY1 = limY1;
        x = dopX1+(_curMouseX)/imageTransform.imageScale;
        y = dopY1+(_curMouseY)/imageTransform.imageScale;

        int yOld = y, xOld=x;
        if (!imageTransform.horFlip && !imageTransform.verFlip){
            switch((int)imageTransform.rotate){
            case -270:
            case 90:
                y = (limY2 - xOld)+dopX1;
                x = yOld+dopX1-dopY1;
                setPi2Rotated(true); break;
            case 270:
            case -90:
                x = limX2 - yOld+dopY1;
                y =  xOld+dopY1-dopX1;
                setPi2Rotated(true);break;
            case 180:
            case -180:
                y =  (limY2) - yOld + dopY1;
                x = (limX2) - xOld + dopX1;
                setPi2Rotated(false); break;
            default: setPi2Rotated(false);;
            }
        }
        else if(imageTransform.horFlip && imageTransform.verFlip){
            switch((int)imageTransform.rotate){
            case -270:
            case 90:
                x = limX2 - yOld+dopY1;
                y =  xOld+dopY1-dopX1;
                setPi2Rotated(true);break;
            case 270:
            case -90:
                y = (limY2 - xOld)+dopX1;
                x = yOld+dopX1-dopY1;
                setPi2Rotated(true); break;
            case 180:
            case -180:
                y =  (limY2) - yOld;
                x = (limX2) - xOld;
                y=(limY2 - y);
                x=(limX2 - x);
                setPi2Rotated(false); break;
            default:
                x=(limX2 - xOld)+dopX1;
                y=(limY2 - yOld)+dopY1;
                setPi2Rotated(false);
            }
        }
        else if(imageTransform.horFlip){
            switch((int)imageTransform.rotate){
            case -270:
            case 90:
                x = yOld-dopY1+dopX1;
                y =  xOld+dopY1-dopX1;
                setPi2Rotated(true);break;
            case 270:
            case -90:
                y = (limY2 - xOld)+dopX1;
                x = yOld-dopY1;;
                x=(limX2 - x);
                setPi2Rotated(true); break;
            case 180:
            case -180:
                y =  (limY2) - yOld + dopY1;
                x = (limX2) - xOld;
                x=(limX2 - x);
                setPi2Rotated(false); break;
            default: x=(limX2 - xOld)+dopX1; setPi2Rotated(false);;
            }
        }
        else if(imageTransform.verFlip){
            switch((int)imageTransform.rotate){
            case -270:
            case 90:
                y = (limY2 - xOld)+dopX1;
                x = yOld-dopY1;
                x=(limX2 - x);
                setPi2Rotated(true); break;
            case 270:
            case -90:
                x = yOld-dopY1+dopX1;
                y =  xOld+dopY1-dopX1;
                setPi2Rotated(true);break;
            case 180:
            case -180:
                y =  (limY2) - yOld;
                x = (limX2) - xOld + dopX1;
                y=(limY2 - y);
                setPi2Rotated(false); break;
            default: y=(limY2 - yOld)+dopY1; setPi2Rotated(false);;
            }
        }
    }
    return QPoint(x,y);
}

void EImageScreen::onMarkerColorChanged(ImageMarker* m)
{
    emit colorChMarker(QPoint(m->_xOnPic, m->_yOnPic), m->_clr);
    emit markerColorChanged(m);
}

void EImageScreen::onMarkerResized(ImageMarker *m)
{
    emit markerResized(m);
}

void EImageScreen::onMarkerGeometryChanged(ImageMarker *m)
{
    recalcMarkerPos();
    emit markerResized(m);
}
