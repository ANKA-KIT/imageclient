#include "imagepicturemode.h"

ImagePictureMode::ImagePictureMode(QObject *parent) :  QObject(parent)
{}


int ImagePictureMode::getPictureMode(){
    return _pictureMode;
}

int ImagePictureMode::getColorFormat(){
    return _colorFormat;
}
int ImagePictureMode::getDelimitr(){
    return _delim;
}
void ImagePictureMode::setColorFormat(int val){
    _colorFormat = val;
}

void ImagePictureMode::setDelimitr(int val){
     _delim = val;
}
void ImagePictureMode::changeColorFormat(int format){
    _colorFormat = format;
    switch(_colorFormat){
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            setDelimitr(4);
        break;
        case QImage::Format_RGB666:
        case QImage::Format_ARGB6666_Premultiplied:
        case QImage::Format_ARGB8555_Premultiplied:
        case QImage::Format_RGB888:
        case QImage::Format_ARGB8565_Premultiplied:
            setDelimitr(3);
        break;
        case QImage::Format_RGB16:
        case QImage::Format_RGB555:
        case QImage::Format_RGB444:
        case QImage::Format_ARGB4444_Premultiplied:
            setDelimitr(2);
        break;
        case QImage::Format_Indexed8:
            setDelimitr(1);
        break;
    }
}

QImage ImagePictureMode::setImageVal(unsigned int width, unsigned int height, QVector <unsigned char>& val){
    QImage image;
    image = QImage(&val[0], width/getDelimitr(),  height, width,
                  (QImage::Format )getColorFormat());
    image = image.copy();
    return image;
}

QImage ImagePictureMode::setImage(int x, int y, QVector <unsigned char>& val){
    return setImageVal(x, y, val);
}
//-----------------------------------------//

GreyImg::GreyImg(){
    changeColorFormat(QImage::Format_Indexed8);
    _colorMapChanged = true;
}

int GreyImg::getRBorder(){
    return _rBorder;
}
int GreyImg::getLBorder(){
    return _lBorder;
}
void GreyImg::setRBorder(int val){
    _colorMapChanged = true;
    _rBorder = val;
}
void GreyImg::setLBorder(int val){
    _colorMapChanged = true;
    _lBorder = val;
}

void GreyImg::recalcColorMap(){
    colorMap.clear();
    int temp = _rBorder - _lBorder;
    int del;
    del= (temp + 255 - (temp%255))/255;
    for (int i = 0; i<_lBorder; i++){
            colorMap.push_back(0);
    }
    int j =0;
    for (int i = _lBorder; i<_rBorder; i++){
            if (i%del == 0)
                j++;
            colorMap.push_back(j);
    }
    for (int i = _rBorder; i<=_maxContrast; i++){
            colorMap.push_back(255);
    }
    _colorMapChanged = false;
}

void GreyImg::setGreyImg(QImage& image){
    for (int i = 0; i < 256; i++)
    {
        image.setColor(i, qRgb(i,i,i));
    }
}

void GreyImg::recalcColors(QVector <unsigned char>& valBefore, QVector <unsigned char>& valAfter){
    if (_colorMapChanged){
        recalcColorMap();
    }
    if (_rBorder != _maxContrast || _lBorder != 0){
        for (unsigned int i=0; i<valBefore.size(); i++){
            valAfter.push_back(colorMap[valBefore[i]]);
        }
    }
}

QImage GreyImg::recalcGreyImg(int x, int y, QVector <unsigned char>& val){
    QImage img = setImageVal(x, y, val);
    setGreyImg(img);
    return img;
}
//-----------------------------------------//

Is16BitGrey::Is16BitGrey(){
    _pictureMode = IS_16BITGRAY;
    _rBorder =_maxBrightness = _maxContrast = 65535;
     _lBorder =_minBrightness =  _minContrast= 0;
}

QImage Is16BitGrey::setImage(int x, int y, QVector <unsigned char>& val){
    QImage tempImg = setImageVal(x,y, val);
    setGreyImg(tempImg);
    return tempImg;
}

//void Is16BitGrey::Convert16BitData(QVector <unsigned short>& val16, QVector <unsigned char>& val8){
void Is16BitGrey::convert16BitData(QVector <unsigned short>& val16, QVector<unsigned char>& val8){
    if (_colorMapChanged){
        recalcColorMap();
    }
    /*for (unsigned int i=0; i<val16.size(); i++){
        val8.push_back(colorMap[val16[i]]);
    }*/
    unsigned short * ptr16;
    unsigned char * ptrCM;
    int count = val16.size();
    ptr16 = &val16[0];
    ptrCM = &colorMap[0];
    val8.resize(count);
    unsigned char *ptrVal8 = &val8[0];
    for (unsigned int i=0; i<count; i++){
         *ptrVal8 = *(ptrCM + *(ptr16+i)); ptrVal8++;//val8.push_back(*(ptrCM+*(ptr16+i)));//colorMap.at(val16[i]);
    }
}



void Is16BitGrey::recalcColors(QVector <unsigned char>& valBefore, QVector <unsigned char>& valAfter){
    if (_colorMapChanged){
        recalcColorMap();
    }
    if (_rBorder != _maxContrast || _lBorder != 0){
        for (unsigned int i=0; i<valBefore.size(); i++){
            valAfter.push_back(colorMap[valBefore[i]]);
        }
    }
}
//-----------------------------------------//
Is8BitGrey::Is8BitGrey(){
    _rBorder = _maxBrightness = _maxContrast = 255;
    _pictureMode = IS_8BIT;
    _lBorder =_minBrightness =  _minContrast = 0;

}

QImage Is8BitGrey::setImage(int x, int y, QVector <unsigned char>& valColor){
    QVector <unsigned char> valGrey;
    recalcColors(valColor, valGrey);
    QImage tempImg;
    if (valGrey.size() == 0){
        tempImg= setImageVal(x, y, valColor);
    }
    else{
         tempImg= setImageVal(x, y, valGrey);
    }
    setGreyImg(tempImg);
    return tempImg;
}

void Is8BitGrey::recalcColors(QVector <unsigned char>& valBefore, QVector <unsigned char>& valAfter){
    if (_colorMapChanged){
        recalcColorMap();
    }
    if (_rBorder != _maxContrast || _lBorder != 0){
        for (unsigned int i=0; i<valBefore.size(); i++){
            valAfter.push_back(colorMap[valBefore[i]]);
        }
    }
}
//-----------------------------------------//
IsRGBGGrey::IsRGBGGrey(){
    _pictureMode = IS_RGBGRAY;
    _lBorder=_minBrightness =  _minContrast = 0;
    _rBorder = _maxBrightness = _maxContrast = 255;

}

QImage IsRGBGGrey::compressImage(QVector<unsigned char>::iterator iter, QVector<unsigned char>::iterator iterEnd, int x, int y){
    QVector <unsigned char> compressedVal;
    if (lastDelimetr == 3){
        for (iter; iter<iterEnd; iter+=3 ){
            compressedVal.push_back((*(iter+2)+*(iter+1)+*(iter))/3);
        }
        return setImageVal(x/3, y, compressedVal);
    }
    else{
        for (iter; iter<iterEnd-3; iter+=4 ){
            compressedVal.push_back((*(iter+2)+*(iter+1)+*(iter))/3);
        }
        return setImageVal(0.25*x, y, compressedVal);
    }
}

QImage IsRGBGGrey::setImage(int x, int y, QVector <unsigned char>& valColor){
    QVector <unsigned char> valGrey;
    QImage tempImg;
    QVector<unsigned char>::iterator iter;
    recalcColors(valColor, valGrey);
    if (valGrey.size() != 0){
        tempImg = compressImage(valGrey.begin(), valGrey.end(), x, y);
    }
    else{
        tempImg = tempImg = compressImage(valColor.begin(), valColor.end(), x, y);
    }
    setGreyImg(tempImg);
    return tempImg;
}

void IsRGBGGrey::recalcColors(QVector <unsigned char>& valBefore, QVector <unsigned char>& valAfter){
    if (_colorMapChanged){
        recalcColorMap();
    }
    if (_rBorder != _maxContrast || _lBorder != 0){
        for (unsigned int i=0; i<valBefore.size(); i++){
            valAfter.push_back(colorMap[valBefore[i]]);
        }
    }
}
//----------------------------------------//
Is24RGB::Is24RGB(){
    _pictureMode = IS_RGB;
    _rBorder = 0;
   // changeColorFormat(QImage::Format_RGB32);
    changeColorFormat(QImage::Format_RGB888);
    _maxBrightness = _maxContrast  = 3000;
    _minBrightness =  _minContrast = -3000;
}

QImage Is24RGB::setImage(int x, int y, QVector <unsigned char>& val){
    return setImageVal(x,y, val);
}

//-----------------------------------------//

Is48BitRGB::Is48BitRGB(){
    _pictureMode = IS_48BIT;
     _maxBrightness = 3000;
     _minBrightness =  _minContrast = -3000;
     _rBorder = 65535;_lBorder =0; _maxContrast = 65535;

    changeColorFormat(QImage::Format_RGB888);
}

QImage Is48BitRGB::setImage(int x, int y, QVector <unsigned char>& val){
    QImage tempImg = setImageVal(x,y, val);
    return tempImg;
}

void Is48BitRGB::convert16BitData(QVector <unsigned short>& val16, QVector<unsigned char>& val8){
    if (_colorMapChanged){
        recalcColorMap();
    }
    /*for (unsigned int i=0; i<val16.size(); i++){
        val8.push_back(colorMap[val16[i]]);
    }*/
    unsigned short * ptr16;
    unsigned char * ptrCM;
    int count = val16.size();
    ptr16 = &val16[0];
    ptrCM = &colorMap[0];
    val8.resize(count);
    unsigned char *ptrVal8 = &val8[0];
    for (unsigned int i=0; i<count; i++){
         *ptrVal8 = *(ptrCM + *(ptr16+i)); ptrVal8++;//val8.push_back(*(ptrCM+*(ptr16+i)));//colorMap.at(val16[i]);
    }
}



void Is48BitRGB::recalcColors(QVector <unsigned char>& valBefore, QVector <unsigned char>& valAfter){
    if (_colorMapChanged){
        recalcColorMap();
    }
    if (_rBorder != _maxContrast || _lBorder != 0){
        unsigned char * ptrBefore;
        unsigned char *ptrAfter;
        unsigned char * ptrCM;
        int count = valBefore.size();
        ptrBefore = &valBefore[0];
        ptrCM = &colorMap[0];
        valAfter.resize(count);
        ptrAfter = &valAfter[0];
        for (unsigned int i=0; i<valBefore.size(); i++){
            *ptrAfter = *(ptrCM + *(ptrBefore+i)); ptrAfter++; //valAfter.push_back(colorMap[valBefore[i]]);
        }
    }
}
///////////////////--------------------------
