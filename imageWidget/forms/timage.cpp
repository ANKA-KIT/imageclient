#include "timage.h"
#include <QVariant>
//My_Code
TImage::TImage(QWidget *parent, Qt::WFlags ):  EImageBase(parent),TDevice(this)//,QTangoComProxyReader(this), QTangoWidgetCommon(wgt)//,ESimpleLabel(parent)
{
    setAttribute(Qt::WA_AlwaysShowToolTips);
   // setText("No Link");
    setProperty("forceNoUnit", false);
    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    connect(device(), SIGNAL(newTangoData(const TVariant&)), this, SLOT(refresh(const TVariant&)),        Qt::DirectConnection);
    setAutoFillBackground(true);
    viewport()->setAutoFillBackground(true);
iii=0;
    canLoadnewPic = true;
    _timer = tango->period();//10;
    setPeriod(_timer);
 //   setFullscreenMode(true);
    connect(this, SIGNAL(newPicture(QImage,int,int,int)), this, SLOT(draw(QImage)), Qt::DirectConnection);
    connect(this, SIGNAL(timerSignal(int)), this, SLOT(setPeriod(int)), Qt::DirectConnection);
    connect(this, SIGNAL(newPictureDim(int, int)), wgt, SLOT(setPicWH(int,int)), Qt::DirectConnection);

  //  picMode = new Is16BitGrey();
  //  picMode = new Is48BitRGB();
    picMode = new Is24RGB();
    time.start();

    __serverMode = READ;//_WITH_SERVERTRANSFORMATION;
    __serverAttrName = "ServerParameter";//"PictureParameters";
    //setServerMode(true);
}

void TImage::setPause(bool value){
    if(value){
        emit isPaused();
        disconnect(tango, SIGNAL(newData(const TVariant&)), this, SLOT(refresh(const TVariant&)));
    }
    else{
        connect(tango, SIGNAL(newData(const TVariant&)), this, SLOT(refresh(const TVariant&)), Qt::DirectConnection);
    }
}
void TImage::refresh(const TVariant &newVal)
{
    if ( canLoadnewPic){  //if Last picture is displayed
        canLoadnewPic = false;
        timeWorking.start();
        if (newVal.quality() == Tango::ATTR_INVALID)
        {
            qDebug("TImages::refresh: Lose connection with a TANGO server!");
            QImage image = errorImage();
            //emit newPicture(image);
            wgt->image = image.copy();
            emit newPicture(val16,dimX,dimY,picMode->getPictureMode());
            emit newPicture(image,dimX,dimY,picMode->getPictureMode());
            emit newPictureDim(dimX/picMode->getDelimitr(), dimY);
            emit newPicture(image, this);
            return;
        }
        int nTime = time.restart();
        qDebug("Displaying time is %d", nTime);
        emit timeNewPic(nTime);
        bool error = false;
        dimX = newVal.dimX;
        dimY = newVal.dimY;

        if (newVal.is16BitPicture()){
            val16.clear();
            val.clear();
            val16 = newVal.toUShortVector();//get16BitPictureData();
           // QTime ppp;
           // ppp.start();
            picMode->convert16BitData(val16, val);
         //   qDebug("time CONVERT is %d",ppp.restart());
            if (val.size() == 0){
                qDebug("TImages::refresh: val vector is Empty. Do not Use uchar mode for dealing with ushort data");
                QImage image = errorImage();
                emit newPicture(val16,dimX,dimY,picMode->getPictureMode());
                emit newPicture(image,dimX,dimY,picMode->getPictureMode());
                emit newPictureDim(dimX/picMode->getDelimitr(), dimY);
                emit newPicture(image, this);
                 wgt->image = image.copy();
                error = true;
            }
        }
        else{
            val.clear();
            val = newVal.toUCharVector();//getPictureData();
        }
        QCoreApplication::processEvents(QEventLoop::AllEvents);
        if (!error){

        QImage img = picMode->setImage(dimX, dimY, val);
/*        wgt->image = img.copy();
        if(picMode->getPictureMode() == ImagePictureMode::IS_RGBGRAY)
            emit newPictureDim(dimX/picMode->lastDelimetr, dimY);
        else
            emit newPictureDim(dimX/picMode->getDelimitr(), dimY);
//*/
        emit newPicture(val16,dimX,dimY,picMode->getPictureMode());
        emit newPicture(img,dimX,dimY,picMode->getPictureMode());
        emit newPicture(img, this);
        iii++;
        QString ttt = "New pic " + QString().number(iii);
        qDebug(ttt.toAscii().constData());


        }
    }
    else{
        qDebug("TImages::refresh: Cannot load picture!");
    }
}

void TImage::draw(QImage img){
    wgt->image = img.copy();
            if(picMode->getPictureMode() == ImagePictureMode::IS_RGBGRAY){
                emit newPictureDim(dimX/picMode->lastDelimetr, dimY);
                wgt->picW  = dimX/picMode->lastDelimetr;
                wgt->picH  = dimY;
            }
            else{
                emit newPictureDim(dimX/picMode->getDelimitr(), dimY);
                wgt->picW  = dimX/picMode->getDelimitr();
                wgt->picH  = dimY;
            }
    img = setPropertiesOnImg(img);
    drawing(img);
    canLoadnewPic = true;
    int wTime = timeWorking.restart();
    qDebug("Working  time is %d",wTime);
    emit timePicDisplaying(wTime);
}

/*void TImage::drawInServerMode(QImage img){
    img = setImageByFullScreenMode(img);
    if (!serverParams.brightness){img = changeBrightnessImg(img, imageParams.brightness);  }
    if(!serverParams.gamma){img = changeGammaImg(img, imageParams.gamma);}
    if(!serverParams.contrast){img = changeContrastImg(img, imageParams.contrast);}
    if(!serverParams.rotate){
        if (wgt->imageTransform.rotate != 0)
            img = wgt->changeRotateImg(img, wgt->imageTransform.rotate);
    }
    if(!serverParams.hFlip){
        if (wgt->imageTransform.horFlip)
              img = wgt->chHorFlip(img);
    }
    if(!serverParams.vFlip){
        if (wgt->imageTransform.verFlip)
              img = wgt->chVerFlip(img);
    }
    drawing(img);
    canLoadnewPic = true;
    int wTime = timeWorking.restart();
    qDebug("Working  time is %d",wTime);
    emit timePicDisplaying(wTime);
}
*/

void TImage::drawInServerMode(QImage img){


    QVector <double> serVar;
    serVar = getDoubleVector(__serverAttrName);

  /////  serVar[0] = 180;
//    serVar[5] = 1;
    serverValues[6] =0;
    if(picMode->getPictureMode() == ImagePictureMode::IS_RGBGRAY){
   //     emit newPictureDim(dimX/picMode->lastDelimetr, dimY);
        wgt->picW  = dimX/picMode->lastDelimetr;
        wgt->picH  = dimY;
    }
    else{
    //    emit newPictureDim(dimX/picMode->getDelimitr(), dimY);
        wgt->picW  = dimX/picMode->getDelimitr();
        wgt->picH  = dimY;
    }
    //double parameters[6];
    QVariant* parameters = new QVariant[6];
    bool picTranformedByServer = false;
    QRect ROI;
    if (serVar.size() == 0){
        serVar.push_back(0);             //rotate
        serVar.push_back(100);           //gamma
                                    //brightness
        if(picMode->getPictureMode() == ImagePictureMode::IS_48BIT || picMode->getPictureMode() == ImagePictureMode::IS_RGB)
            serVar.push_back(0);
        else{
            serVar.push_back(picMode->_maxBrightness);
        }
        serVar.push_back(100);           //contrast
        serVar.push_back(0);             //VFlip
        serVar.push_back(0);             //HFlip

        serVar.push_back(0);             //ROIx1
        serVar.push_back(wgt->picW);     //ROIx2
        serVar.push_back(0);             //ROIy1
        serVar.push_back(wgt->picH);     //ROIy2
    }
    bool p2=false;//true;


    serVar[4] = serVar[4] <= 0 ? 0:1;
    serVar[5] = serVar[5] <= 0 ? 0:1;



    if (__serverMode == READ_WITH_SERVERTRANSFORMATION || __serverMode == WRITE_WITH_SERVERTRANSFORMATION){
        if (serVar[0] != serverValues[0]){
            picTranformedByServer = true;}
        if (serVar[4] != serverValues[4]){picTranformedByServer = true;}
        if (serVar[5] != serverValues[5]){picTranformedByServer = true;}


        if (serVar[0] != serverValues[0] && serVar[0] >= -360 && serVar[0] <= 360)
            serverValues[0] = serVar[0];
        if (serVar[4] != serverValues[4]){serverValues[4] = serVar[4];}
        if (serVar[5] != serverValues[5]){serverValues[5] = serVar[5];}
        if (serVar[0] >= -360 && serVar[0] <= 360)
            parameters[0] = -serVar[0]+serverValues[0]+getRotate();
        else
            parameters[0] = getRotate();
        if (serverValues[0] == 0 || serverValues[0] == 180 || serverValues[0] == -180){
            p2 = false;
        }

        if (serVar[1] >= -1 && serVar[1] <= 66000){
            parameters[1] = serVar[1];//getGamma();//serVar[1]-100;//getGamma() - serVar[1]-getGamma();
            setGamma(serVar[1]);
        }
        else
            parameters[1] = 0;//serVar[1];
        if(serVar[2] >= -66000 && serVar[2] <= 66000){
            parameters[2] = serVar[2];//getBrightness();//serVar[2]//getBrightness() - serVar[2]-getBrightness();
            setBrightness(serVar[2]);
        }
        else
            parameters[2] = 100;//serVar[2];
        if(serVar[3] >= -66000 && serVar[3] <= 66000){
            parameters[3] = serVar[3];//getContrast();//getContrast() - serVar[3]-getContrast();
            setContrast(serVar[3]);
        }
        else
            parameters[3] = 100;//serVar[3];
            bool value;
        value = serVar[4] <= 0 ? false:true;
      //  parameters[4] = (value & getVFlip()) | getVFlip();
        parameters[4] = p2 ? serVar[5]:serVar[4];//getHFlip():getVFlip();//((value & getVFlip()) | getVFlip()):((value & getHFlip()) | getHFlip());//getHFlip():getVFlip();
        value = serVar[5] <= 0 ? false:true;
        //parameters[5] = (value & getHFlip()) | getHFlip();
        parameters[5] = p2 ? serVar[4]:serVar[5];//getVFlip():getHFlip();//((value & getHFlip()) | getHFlip()):((value & getVFlip()) | getVFlip());//getVFlip():getHFlip();

        if (__serverMode == READ_WITH_SERVERTRANSFORMATION || __serverMode == WRITE_WITH_SERVERTRANSFORMATION&& picTranformedByServer){
            serverValues[6] = 1;
            //*
            if (serVar[0] ==90 || serVar[0] ==-90 || serVar[0] == 270 || serVar[0] ==-270){//  && serVar[0] != 180 && serVar[0] != -180){
                if(wgt->picH < wgt->picW){
                    int ttt  =  wgt->picH;
                    wgt->picH = wgt->picW;//:wgt->picH;
                    wgt->picW = ttt;// < wgt->picW? ttt:wgt->picW;
                }
            }//*/
            setRotate(serVar[0]);
            setVFlip(serVar[4]);
            setHFlip(serVar[5]);
            wgt->serverPicTrans.rotate = serVar[0];//getRotate();//serVar[0];
            wgt->serverPicTrans.vFlip = serVar[4];//serVar[4];
            wgt->serverPicTrans.hFlip = serVar[5];//serverValues;


            for (int rrr=0; rrr<wgt->marker.count(); rrr++)
            {
                QPoint point = wgt->convertToImagePointServer(wgt->marker.at(rrr)->_xOnPic,wgt->marker.at(rrr)->_xOnPic);
                wgt->marker.at(rrr)->_x = point.x();
                wgt->marker.at(rrr)->_y = point.y();
            }


            wgt->recalcMarkerPos();
        }

}
    else{ //if (__serverMode == READ){
    if (serverValues[0] == serVar[0] && serVar[0] >= -360 && serVar[0] <= 360)
        parameters[0] = getRotate();//-serVar[0];
    else if (serVar[0] >= -360 && serVar[0] <= 360){
        parameters[0] = serverValues[0] = serVar[0];
        setRotate(serVar[0]);
    }
    else{
        parameters[0] = getRotate();
        //parameters[0] = serverValues[0] = 0;
        qDebug("Incorrect rotation value not in [-360;360]");
    }
    if (parameters[0] == 0 || parameters[0] == 180 || parameters[0] == -180){
        p2 = false;
    }
    if (getRotate()== 0 || getRotate() == 180 || getRotate() == -180){
    p2 = false;
    }
    if (serverValues[1] == serVar[1] && serVar[1] >= -1 && serVar[1] <= 66000)
        parameters[1] = getGamma();//serVar[1]-100;//getGamma() - serVar[1]-getGamma();
    else if(serVar[1] >= -1 && serVar[1] <= 66000){
         parameters[1] =serverValues[1] =serVar[1];
         setGamma(serVar[1]);
    }
    else{
        parameters[1] = getGamma();
        qDebug("Incorrect gamma value not in [-1;66000]");
    }
    if(serverValues[2] == serVar[2] && serVar[2] >= -66000 && serVar[2] <= 66000)
        parameters[2] = getBrightness();//serVar[2]//getBrightness() - serVar[2]-getBrightness();
    else if(serVar[2] >= -66000 && serVar[2] <= 66000){
         parameters[2] = serverValues[2] =serVar[2];
         setBrightness(serVar[2]);
    }
    else{
        parameters[2] = getBrightness();
        qDebug("Incorrect brightness value not in [-66000;66000]");
    }
    if(serverValues[3] == serVar[3] && serVar[3] >= -66000 && serVar[3] <= 66000)
        parameters[3] = getContrast();//getContrast() - serVar[3]-getContrast();
    else if (serVar[3] >= -66000 && serVar[3] <= 66000){
        parameters[3] =serverValues[3] =  serVar[3];
        setContrast(serVar[3]);
    }
    else{
        parameters[3] = getContrast();
        qDebug("Incorrect contrast value not in [-66000;66000]");
    }
        bool value;
    value = serVar[4] <= 0 ? false:true;
    if (serverValues[4] == serVar[4])
        ;
    else{
        serverValues[4] = serVar[4];
        //*
        if (p2)
            setVFlip(value);
        else
            setHFlip(value);
        //*/
    }
    //parameters[4] = getVFlip();            //(value & getVFlip()) | getVFlip();
    parameters[4] = p2 ? getVFlip():getHFlip();//getHFlip():getVFlip();
    value = serVar[5] <= 0 ? false:true;
    //parameters[5] = getHFlip();//(value & getHFlip()) | getHFlip();
    if (serverValues[5] == serVar[5])
        ;
    else{
        serverValues[5] = serVar[5];
        //*
         if (p2)
            setHFlip(value);
        else
            setVFlip(value);
        //*/
    }
    parameters[5] = p2 ? getHFlip():getVFlip();//getVFlip():getHFlip();//getHFlip();//

    }
    int x1, x2, y1,y2;



    int roiCount = serVar[6];
    int m = 7;
    int index;
    bool finded;
    if(roiCount != roiList.count()){
        roiList.clear();
        for (int i=0; i<roiCount; i++){
            index =m+i*4;
            serVar[index] < 0 ? 0:serVar[index];
            serVar[index+1] <= 0 ? wgt->picW:serVar[index+3];
            serVar[index+2] < 0 ? 0:serVar[index+2];
            serVar[index+3] <= 0 ? wgt->picH:serVar[index+3];
            roiList<<QRect(serVar[index],serVar[index+2],serVar[index+1]-serVar[index],serVar[index+3]-serVar[index+2]);
        }
    }
    else{
        for (int i=0; i<roiCount; i++){
            index =m+i*4;
            finded = false;
            serVar[index] < 0 ? 0:serVar[index];
            serVar[index+1] <= 0 ? wgt->picW:serVar[index+3];
            serVar[index+2] < 0 ? 0:serVar[index+2];
            serVar[index+3] <= 0 ? wgt->picH:serVar[index+3];
            QRect newRect(serVar[index],serVar[index+2],serVar[index+1]-serVar[index],serVar[index+3]-serVar[index+2]);
            for (int j=0; j<roiList.count(); j++){
                if (roiList.at(i) == newRect){
                    finded = true;
                    break;
                }
            }
            if(!finded)
                roiList<<QRect(serVar[index],serVar[index+2],serVar[index+1]-serVar[index],serVar[index+3]-serVar[index+2]);
        }
    }

    index =m+roiCount*4;    //index of marker position


    if(serverMarkerCount != (serVar.count() - index)/5){
        disconnect(this,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(writeMarker(QPoint , QRgb ))); ///!
        disconnect(wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(delMarker(QPoint,QRgb)));
        if(__serverMode == WRITE || __serverMode == WRITE_WITH_SERVERTRANSFORMATION ){
            for (int i=0; i<wgt->marker.count(); i++)
                wgt->marker[i]->deleteLater();
            wgt->marker.clear();
            serverMarkerList.clear();

        }
        else{
            for (int i=0; i<serverMarkerList.count(); i++)
                serverMarkerList.at(i)->del();
            serverMarkerList.clear();
        }
        for (index; index < serVar.count()-1; index+=5){
            ImageMarker* marker = wgt->initMarker(QPoint(serVar[index], (int)serVar[index+1]));
            marker->setMarkerColor(qRgb(serVar[index+2],serVar[index+3],serVar[index+4]));
            if (__serverMode == READ || __serverMode == READ_WITH_SERVERTRANSFORMATION){
                marker->actDel->setEnabled(false);
                marker->actSettings->setEnabled(false);
            }
            serverMarkerList.push_back(marker);
        }
        serverMarkerCount = serverMarkerList.count();//(serVar.count() - index)/5;
        if(__serverMode == WRITE || __serverMode == WRITE_WITH_SERVERTRANSFORMATION ){
            connect(this,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(writeMarker(QPoint , QRgb )));
            connect(wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(delMarker(QPoint,QRgb)));
        }
    }

    if (picTranformedByServer){
        for (int iter=0; iter<wgt->marker.count();iter++){
            QPoint posTrans = wgt->convertToImagePointServer(wgt->marker[iter]->_xOnPic,wgt->marker[iter]->_yOnPic);
            wgt->marker[iter]->_x = posTrans.x();
            wgt->marker[iter]->_y = posTrans.y();
        }
    }

    wgt->image = img.copy();  //*/


    img = setPropertiesOnImg(img, parameters);
    drawing(img);
    canLoadnewPic = true;
    int wTime = timeWorking.restart();
    qDebug("Working  time is %d",wTime);
    emit timePicDisplaying(wTime);
}


TImage::~TImage(){

}

void TImage::setPeriod(int p){
    TDevice::setPeriod(p);
}

TImageSnapshot* TImage::makeSnpImage(QWidget *scr){
    TImageSnapshot *img;
    if(val16.size() != 0 && (picMode->getPictureMode() == ImagePictureMode::IS_16BITGRAY || picMode->getPictureMode() ==ImagePictureMode:: IS_48BIT)){// 8BIT || picMode->getPictureMode() == IS_RGBGRAY)){
        img = new TImageSnapshot(val16,dimX, dimY, picMode->getPictureMode(), scr);
    }
    else{
        img = new TImageSnapshot(wgt->image,dimX, dimY, picMode->getPictureMode(), scr);
    }
    for (int i=0; i<wgt->marker.count(); i++){
        //img->wgt->initMarker(QPoint(wgt->marker.at(i)->_x,wgt->marker.at(i)->_y));
        img->wgt->initMarker(QPoint(wgt->marker.at(i)->_xOnPic,wgt->marker.at(i)->_yOnPic));
        img->wgt->marker.at(i)->setMarkerColor(wgt->marker.at(i)->_clr);
        img->wgt->marker.at(i)->hLineLength = wgt->marker.at(i)->hLineLength;
        img->wgt->marker.at(i)->vLineLength = wgt->marker.at(i)->vLineLength;
    }
    QObject::connect(img->wgt, SIGNAL(repainting()),img->wgt,  SLOT(rescreen()));
    img->imageParams = imageParams;
    img->wgt->imageTransform = wgt->imageTransform;
    img->setImage(img->wgt->image);
    img->setFullscreenMode(true);
 return img;
}

TImageSnapshot* TImage::makeSnpImageCat(QWidget *scr){
    TImageSnapshot *img;
    if(val16.size() != 0 && (picMode->getPictureMode() == ImagePictureMode::IS_16BITGRAY || picMode->getPictureMode() ==ImagePictureMode:: IS_48BIT)){// 8BIT || picMode->getPictureMode() == IS_RGBGRAY)){
        QVector <unsigned short> tempVal16;
        int bytesPerLine = (wgt->limX2 - wgt->limX1)*picMode->getDelimitr();
        int catHeight =  wgt->limY2 - wgt->limY1;
        int limitWidth = wgt->limX1 +bytesPerLine;
        for (int i=wgt->limY1; i<wgt->limY2; i++){
            int line = i*dimX;
            for(int j=wgt->limX1;j<limitWidth;j++){
                tempVal16.push_back(val16.at(line+j));
            }
        }
        img = new TImageSnapshot(tempVal16, bytesPerLine, catHeight, picMode->getPictureMode(), scr);
    }
    else{
        img = new TImageSnapshot(wgt->image.copy(wgt->limX1, wgt->limY1, wgt->limX2 - wgt->limX1,wgt->limY2 - wgt->limY1)
                          ,(wgt->limX2 - wgt->limX1)*picMode->getDelimitr(), wgt->limY2 - wgt->limY1, picMode->getPictureMode(), scr);
    }

    int iterX, iterY,iter=0;
 //*
    for (int m=0; m<wgt->marker.count(); m++){
        iterX=-1, iterY=-1;
        if(wgt->marker.at(m)->visiableXPos >= 0 && wgt->marker.at(m)->visiableXPos <= wgt->limX2){//-wgt->limX1
            iterX  = wgt->marker.at(m)->visiableXPos;
        }
        if(wgt->marker.at(m)->visiableYPos >= 0 && wgt->marker.at(m)->visiableYPos <= wgt->limY2){//-wgt->limY1
            iterY  = wgt->marker.at(m)->visiableYPos;
        }
        if (iterX == -1 || iterY ==-1){}
        else{
            img->wgt->initMarker(QPoint(iterX/wgt->imageTransform.imageScale, iterY/wgt->imageTransform.imageScale));
            img->wgt->marker.at(iter)->setMarkerColor(wgt->marker.at(m)->_clr);
            img->wgt->marker.at(iter)->hLineLength = wgt->marker.at(m)->hLineLength;
            img->wgt->marker.at(iter)->vLineLength = wgt->marker.at(m)->vLineLength;
            iter++;
        }
    }//*/
    QObject::connect(img->wgt, SIGNAL(repainting()),img->wgt,  SLOT(rescreen()));
    img->imageParams = imageParams;
    img->wgt->imageTransform = wgt->imageTransform;
    img->setImage(img->wgt->image);
    img->setFullscreenMode(true);
 return img;
}

TImageSnapshot* TImage::makeSnpImageCat(QRect rec, QWidget *scr){
    TImageSnapshot *img;
    if(val16.size() != 0 && (picMode->getPictureMode() == ImagePictureMode::IS_16BITGRAY || picMode->getPictureMode() ==ImagePictureMode:: IS_48BIT)){// 8BIT || picMode->getPictureMode() == IS_RGBGRAY)){
        QVector <unsigned short> tempVal16;
        int bytesPerLine = (rec.width())*picMode->getDelimitr();
        int catHeight =  rec.height();
        int limitWidth = rec.x() +bytesPerLine;
        for (int i=rec.top(); i<rec.bottom(); i++){
            int line = i*dimX;
            for(int j=rec.x();j<limitWidth;j++){
                tempVal16.push_back(val16.at(line+j));
            }
        }
        img = new TImageSnapshot(tempVal16, bytesPerLine, catHeight, picMode->getPictureMode(), scr);
    }
    else{
        //rec.x(),rec.y(),rec.width(),rec.height();
        int x1 = rec.x(); int y1 = rec.y(); int x2 = rec.width(); int y2 = rec.height();
        img = new TImageSnapshot(wgt->image.copy(x1,y1,x2,y2),(rec.width())*picMode->getDelimitr(), rec.height(), picMode->getPictureMode(), scr);
    }

    int iterX, iterY, iter =0;
    for (int m=0; m<wgt->marker.count(); m++){
        iterX=-1, iterY=-1;
        if(wgt->marker.at(m)->visiableXPos >= 0 && wgt->marker.at(m)->visiableXPos <= wgt->limX2){//-wgt->limX1
            iterX  = wgt->marker.at(m)->visiableXPos;
        }
        if(wgt->marker.at(m)->visiableYPos >= 0 && wgt->marker.at(m)->visiableYPos <= wgt->limY2){//-wgt->limY1
            iterY  = wgt->marker.at(m)->visiableYPos;
        }
        if (iterX == -1 || iterY == -1){}
        else{
            img->wgt->initMarker(QPoint(iterX/wgt->imageTransform.imageScale, iterY/wgt->imageTransform.imageScale));
            img->wgt->marker.at(iter)->setMarkerColor(wgt->marker.at(m)->_clr);
            img->wgt->marker.at(iter)->hLineLength = wgt->marker.at(m)->hLineLength;
            img->wgt->marker.at(iter)->vLineLength = wgt->marker.at(m)->vLineLength;
            iter++;
        }
    }
    QObject::connect(img->wgt, SIGNAL(repainting()),img->wgt,  SLOT(rescreen()));
    img->imageParams = imageParams;
    img->wgt->imageTransform = wgt->imageTransform;
    img->setImage(img->wgt->image);
    img->setFullscreenMode(true);
 return img;
}


QImage TImage::makeSnpImage(){  //should be deleted
    QImage img = QImage(&val[0], dimX/picMode->getDelimitr(), dimY, dimX, (QImage::Format)picMode->getColorFormat());
    img = img.copy();
    return img;
}

void TImage::showParams(){
    QImage tempImg;
    if (val.size() !=0){
        tempImg = QImage(&val[0], dimX/picMode->getDelimitr(), dimY, dimX, (QImage::Format)picMode->getColorFormat());
    }
    if (manipulatorIsClosed){
        bool hf = wgt->imageTransform.horFlip, vf=wgt->imageTransform.verFlip;
        if (!vf){
            vf = serverValues[4];
        }
        if (!hf){
            hf = serverValues[5];
        }
    manip = new ImageManipulator(QList<QVariant>()
                            <<imageParams.brightness<<imageParams.contrast<<wgt->imageTransform.rotate+serverValues[0]<<imageParams.gamma<<picMode->getLBorder()
                            <<picMode->getRBorder()<<hf<<vf<<wgt->imageTransform.imageScale
                            <<picMode->_maxContrast<<_timer<<picMode->getPictureMode()
                            <<wgt->imageTransform.fullPictureMode<<wgt->moveX<<wgt->moveY<<dimX/picMode->getDelimitr()<<dimY,
                            val16, tempImg);
    manip->setAttribute(Qt::WA_DeleteOnClose);//, Qt::WindowModal);
    manipulatorIsClosed = false;
    manip->setModal(true);
    manip->move(400,200);
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
    connect(manip, SIGNAL(autoHistogram(bool)), this, SLOT(autoDrawingHistogram(bool)));

    connect(manip, SIGNAL(chPicX(int)), wgt, SLOT(setMoveX(int)));
    connect(manip, SIGNAL(chPicY(int)), wgt, SLOT(setMoveY(int)));
    connect(this, SIGNAL(newPictureDim(int, int)), manip, SLOT(setDim(int,int)));
    connect(wgt, SIGNAL(showPictureSize(int,int,int,int)), manip, SLOT(setShowPicSize(int,int,int,int)));
    manip->show();
    }
}


void TImage::autoDrawingHistogram(bool val){
    if(val){
        connect(this, SIGNAL(newPicture(QImage,int, int,int)), this, SLOT(drawHistogram()));
    }
    else
        disconnect(this, SIGNAL(newPicture(QImage,int, int,int)), this, SLOT(drawHistogram()));
}


void TImage::setServerMode(bool value){
    _serverMode = value;
    disconnect(this,SIGNAL(imgChanged(QImage)),this,SLOT(writeProperty()));
    disconnect(wgt,SIGNAL(imgChanged(QImage)),this,SLOT(writeProperty()));

    disconnect(this,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(writeMarker(QPoint , QRgb )));
    disconnect(wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(delMarker(QPoint,QRgb)));
    if (value){
        disconnect(this, SIGNAL(newPicture(QImage,int,int,int)), this, SLOT(draw(QImage)));    
        switch(__serverMode){
            case READ:
            case READ_WITH_SERVERTRANSFORMATION:
                break;
            case WRITE:
            case WRITE_WITH_SERVERTRANSFORMATION:
                connect(this,SIGNAL(imgChanged(QImage)),this,SLOT(writeProperty()));
                connect(wgt,SIGNAL(imgChanged(QImage)),this,SLOT(writeProperty()));

                connect(this,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(writeMarker(QPoint , QRgb )));
                connect(wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(delMarker(QPoint,QRgb)));
                break;
        }

        QVector <double> serVar;
        serVar = getDoubleVector(__serverAttrName);
        if (serVar.size() == 0){
            serVar.push_back(0);             //rotate
            serVar.push_back(100);           //gamma
                                        //brightness
            if(picMode->getPictureMode() == ImagePictureMode::IS_48BIT || picMode->getPictureMode() == ImagePictureMode::IS_RGB)
                serVar.push_back(0);
            else{
                serVar.push_back(picMode->_maxBrightness);
            }
            serVar.push_back(100);           //contrast
            serVar.push_back(0);             //VFlip
            serVar.push_back(0);             //HFlip

            serVar.push_back(1);
            serVar.push_back(0);             //ROIx1
            serVar.push_back(wgt->picW);     //ROIx2
            serVar.push_back(0);             //ROIy1
            serVar.push_back(wgt->picH);     //ROIy2
        }

        if (serVar[0] >= -360 && serVar[0] <= 360)
            ;//setRotate(serVar[0]);
        else
            serVar[0]=0;//setRotate(0);
        if(serVar[1] >= -1 && serVar[1] <= 66000)
            ;//setGamma(serVar[1]);
        else
            serVar[0] = 100;//setGamma(100);
        if(serVar[2] >= -66000 && serVar[2] <= 66000)
            ;//setBrightness(serVar[2]);
        else
            serVar[2]=picMode->_maxBrightness;//setBrightness(picMode->_maxBrightness);
        if(serVar[3] >= -66000 && serVar[3] <= 66000)
            ;//setContrast(serVar[3]);
        else
            serVar[3]=picMode->_maxContrast;//setContrast(picMode->_maxContrast);
        bool value;
        value = serVar[4] <= 0 ? false:true;
        setVFlip(value);
        value = serVar[5] <= 0 ? false:true;
        setHFlip(value);

        serverValues[0] = serVar[0];
        serverValues[1] = serVar[1];
        serverValues[2] = serVar[2];
        serverValues[3] = serVar[3];
        serverValues[4] = serVar[4] <= 0 ? 0:1;
        serverValues[5] = serVar[5] <= 0 ? 0:1;

        setRotate(serVar[0]);
        setGamma(serVar[1]);
        setBrightness(serVar[2]);
        setContrast(serVar[3]);


        int roiCount = serVar[6];
        roiList.clear();
        int m = 7;
        int index;
        for (int i=0; i<roiCount; i++){
            index =m+i*4;
            serVar[index] < 0 ? 0:serVar[index];                   //x1
            serVar[index+1] <= 0 ? wgt->picW:serVar[index+3];      //x2
            serVar[index+2] < 0 ? 0:serVar[index+2];               //y1
            serVar[index+3] <= 0 ? wgt->picH:serVar[index+3];      //y2
            roiList<<QRect(serVar[index],serVar[index+2],serVar[index+1]-serVar[index],serVar[index+3]-serVar[index+2]);
        }
     //   serVar[7] < 0 ? 0:serVar[7];
     //   serVar[8] <= 0 ? wgt->picW:serVar[8];
       // serVar[9] < 0 ? 0:serVar[9];
       // serVar[10] <= 0 ? wgt->picH:serVar[10];
        double sclXROI = (width()/(double)(wgt->image.width()))*(double)(wgt->image.width()/(double)(serVar[8]-serVar[7]));
        double sclYROI = (height()/(double)(wgt->image.height()))*(double)(wgt->image.height()/(double)(serVar[10]-serVar[9]));
        double minScl;
        minScl = sclXROI<sclYROI ? sclXROI:sclYROI;
        wgt->setMoveX(serVar[7]);
        wgt->setMoveY(serVar[9]);
        setScale(minScl);
        setFullscreenMode(false);

        index =m+roiCount*4;    //index of marker position
        for (int i=0; i<serverMarkerList.count(); i++)
            serverMarkerList.at(i)->del();
        serverMarkerList.clear();
        QPoint onPicCoord;
        serverMarkerCount = (serVar.count() - index)/5;
        //wgt->limY1 = wgt->limX1 =0; wgt->limX2 = wgt->picW; wgt->limY2 = wgt->picH;


        wgt->serverPicTrans.rotate = 0;
        wgt->serverPicTrans.vFlip = 0;
        wgt->serverPicTrans.hFlip = 0;

        if (__serverMode == READ_WITH_SERVERTRANSFORMATION || __serverMode == WRITE_WITH_SERVERTRANSFORMATION){
            wgt->serverPicTrans.rotate = serverValues[0];//getRotate();//serVar[0];
            wgt->serverPicTrans.vFlip = serverValues[4];//serVar[4];
            wgt->serverPicTrans.hFlip = serverValues[5];//serverValues;
        }


        disconnect(this,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(writeMarker(QPoint , QRgb )));
        disconnect(wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(delMarker(QPoint,QRgb)));
        for (; index < serVar.count()-1; index+=5){
            onPicCoord = QPoint(serVar[index], (int)serVar[index+1]);
          //  onPicCoord = wgt->convertToImagePoint(onPicCoord.x(), onPicCoord.y());

         /*
             int x = serVar[index], y = serVar[index+1];
            int yOld = y, xOld=x;
            int displayPicWidth = wgt->picH;//wgt->limX2 - wgt->limX1;
            int displayPicHeight = wgt->picW;//wgt->limY2 - wgt->limY1;
            switch((int)serVar[0]){
            case -270:
            case 90: y =  xOld; wgt->setPi2Rotated(true); break;
            case 270:
            case -90: y = displayPicWidth - xOld; wgt->setPi2Rotated(true);break;
            case 180:
            case -180: y = displayPicHeight - yOld;wgt->setPi2Rotated(false); break;
            default: wgt->setPi2Rotated(false);
        }

            switch((int)serVar[0]){
            case -270:
            case 90: x =   displayPicHeight -yOld; break;
            case 270:
            case -90: x =  yOld; break;
            case 180:
            case -180: x =   displayPicWidth - xOld; break;
            default: ;
            }


            if (wgt->imageTransform.horFlip && (serVar[0] == -270 || serVar[0] == 90)){
                x = displayPicHeight - x;
            }
            else if (wgt->imageTransform.horFlip && (serVar[0] == 270 || serVar[0] == -90)){
                x = displayPicHeight - x;
            }
            else if (wgt->imageTransform.horFlip){
                x = displayPicWidth - x;
            }



            if (wgt->imageTransform.verFlip && (serVar[0] || serVar[0] == 90)){
                y = displayPicWidth - y;
            }
            else if (wgt->imageTransform.verFlip && (serVar[0]== 270 || serVar[0] == -90)){
                y = displayPicWidth - y;
            }
            else if (wgt->imageTransform.verFlip){
                y = displayPicHeight - y;
            }

            onPicCoord = QPoint(x,y);
//*/




            ImageMarker* marker = wgt->initMarker(onPicCoord);
            marker->setMarkerColor(qRgb(serVar[index+2],serVar[index+3],serVar[index+4]));
            if (__serverMode == READ || __serverMode == READ_WITH_SERVERTRANSFORMATION){
                marker->actDel->setEnabled(false);
                marker->actSettings->setEnabled(false);
            }
            serverMarkerList.push_back(marker);
        }
        if(__serverMode == WRITE || __serverMode == WRITE_WITH_SERVERTRANSFORMATION ){
            connect(this,SIGNAL(newMarker(QPoint,QRgb)),this,SLOT(writeMarker(QPoint , QRgb )));
            connect(wgt,SIGNAL(delMarker(QPoint,QRgb)),this,SLOT(delMarker(QPoint,QRgb)));
        }

        connect(this, SIGNAL(newPicture(QImage,int,int,int)), this, SLOT(drawInServerMode(QImage)), Qt::DirectConnection);
    }
    else{
        __serverMode = SINGLE;
        wgt->serverPicTrans.rotate = 0;
        wgt->serverPicTrans.vFlip = 0;
        wgt->serverPicTrans.hFlip = 0;

        serverValues[0] = 0;//serVar[0];
        serverValues[1] = 0;//serVar[1];
        serverValues[2] = 0;//serVar[2];
        serverValues[3] = 0;//serVar[3];
        serverValues[4] = 0;//serVar[4] <= 0 ? 0:1;
        serverValues[5] = 0;//serVar[5] <= 0 ? 0:1;

        serverValues[6] = 0;

        connect(this, SIGNAL(newPicture(QImage,int,int,int)), this, SLOT(draw(QImage)), Qt::DirectConnection);
        disconnect(this, SIGNAL(newPicture(QImage,int,int,int)), this, SLOT(drawInServerMode(QImage)));
        serverParams.brightness = false;
        serverParams.contrast = false;
        serverParams.gamma = false;
        serverParams.rotate = false;
        serverParams.hFlip = false;
        serverParams.vFlip = false;
        serverParams.scale = false;
        serverParams.marker = false;
    }
}

void TImage::writeProperty(){
    QVector<double> parameters;
    parameters.resize(6);
    for (int i=0;i<6;i++){
        parameters[i]=valuesForWrite[i];
    }
    writeProperty(parameters);
}

void TImage::writeProperty(QVector<double> parameters){
    sendTangoCommand("writeProperties",parameters);
}

void TImage::writeMarker(QPoint p, QRgb col){
    sendTangoCommand("AddMarker", QVector<double>()<<p.x()<<p.y()<<qRed(col)<<qGreen(col)<<qBlue(col));
}

void TImage::writeROI(QPoint p1,QPoint p2){
    sendTangoCommand("AddROI", QVector<double>()<<p1.x()<<p1.y()<<p2.x()<<p2.y());
}

void TImage::delMarker(QPoint p, QRgb col){
    sendTangoCommand("deleteMarker", QVector<double>()<<p.x()<<p.y()<<qRed(col)<<qGreen(col)<<qBlue(col));
}

void TImage::delROI(QPoint p1,QPoint p2){
    sendTangoCommand("deleteROI", QVector<double>()<<p1.x()<<p1.y()<<p2.x()<<p2.y());
}

