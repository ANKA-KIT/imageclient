#include "picturemode.h"

PictureMode::PictureMode(){}

int PictureMode::getPictureMode(){
    return _pictureMode;
}

int PictureMode::getColorFormat(){
    return _colorFormat;
}
int PictureMode::getDelimitr(){
    return _delim;
}
void PictureMode::setColorFormat(int val){
    _colorFormat = val;
}

void PictureMode::setDelimitr(int val){
     _delim = val;
}
void PictureMode::changeColorFormat(int format){
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

QImage PictureMode::setImageVal(unsigned int width, unsigned int height, vector <unsigned char>& val){
    QImage image;
    image = QImage(&val[0], width/getDelimitr(),  height, width,
                  (QImage::Format )getColorFormat());
    image = image.copy();
    return image;
}

QImage PictureMode::setImage(int x, int y, vector <unsigned char>& val){
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

void GreyImg::recalcColors(vector <unsigned char>& valBefore, vector <unsigned char>& valAfter){
    if (_colorMapChanged){
        recalcColorMap();
    }
    if (_rBorder != _maxContrast || _lBorder != 0){
        for (unsigned int i=0; i<valBefore.size(); i++){
            valAfter.push_back(colorMap[valBefore[i]]);
        }
    }
}

QImage GreyImg::recalcGreyImg(int x, int y, vector <unsigned char>& val){
    QImage img = setImageVal(x, y, val);
    setGreyImg(img);
    return img;
}
//-----------------------------------------//

Is16BitGrey::Is16BitGrey(){
    _pictureMode = IS_16BITIMG_GREY;
    _maxContrast = 65535;
     _lBorder = 0;
    _rBorder = _maxContrast;
}

QImage Is16BitGrey::setImage(int x, int y, vector <unsigned char>& val){
    QImage tempImg = setImageVal(x,y, val);
    setGreyImg(tempImg);
    return tempImg;
}

void Is16BitGrey::Convert16BitData(vector <unsigned short>& val16, vector <unsigned char>& val8){
    if (_colorMapChanged){
        recalcColorMap();
    }
    for (unsigned int i=0; i<val16.size(); i++){
        val8.push_back(colorMap[val16[i]]);
    }
}



void Is16BitGrey::recalcColors(vector <unsigned char>& valBefore, vector <unsigned char>& valAfter){
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
    _maxContrast = 255;
    _pictureMode = IS_8BITIMG_GREY;
    _lBorder = 0;
    _rBorder = _maxContrast;
}

QImage Is8BitGrey::setImage(int x, int y, vector <unsigned char>& valColor){
    vector <unsigned char> valGrey;
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

void Is8BitGrey::recalcColors(vector <unsigned char>& valBefore, vector <unsigned char>& valAfter){
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
    _pictureMode = IS_RGBIMG_GREY;
    _lBorder = 0;
    _maxContrast = 255;
    _rBorder = _maxContrast;
}

QImage IsRGBGGrey::compressImage(vector<unsigned char>::iterator iter, vector<unsigned char>::iterator iterEnd, int x, int y){
    vector <unsigned char> compressedVal;
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

QImage IsRGBGGrey::setImage(int x, int y, vector <unsigned char>& valColor){
    vector <unsigned char> valGrey;
    QImage tempImg;
    vector<unsigned char>::iterator iter;
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

void IsRGBGGrey::recalcColors(vector <unsigned char>& valBefore, vector <unsigned char>& valAfter){
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
IsRGB::IsRGB(){
    _pictureMode = IS_RGBIMG_COLOR;
    changeColorFormat(QImage::Format_RGB32);
}

QImage IsRGB::setImage(int x, int y, vector <unsigned char>& val){
    return setImageVal(x,y, val);
}
//----------------------------------------//

Is8BitColor::Is8BitColor(){
    _pictureMode = IS_8BITIMG_COLOR;
    changeColorFormat(QImage::Format_Indexed8);
}

QImage Is8BitColor::setImage(int x, int y, vector <unsigned char>& val){
    return setImageVal(x, y, val);
}
//----------------------------------------//


//-----------------------------------------//

Is16BitRGB::Is16BitRGB(){
    _pictureMode = IS_16BITIMG_RGB;
    _maxContrast = 65535;
     _lBorder = 0;
    _rBorder = _maxContrast;
    changeColorFormat(QImage::Format_RGB888);
}

QImage Is16BitRGB::setImage(int x, int y, vector <unsigned char>& val){
    QImage tempImg = setImageVal(x,y, val);
    //setGreyImg(tempImg);
   // tempImg.invertPixels(QImage::InvertRgb);
    return tempImg;
}

void Is16BitRGB::Convert16BitData(vector <unsigned short>& val16, vector <unsigned char>& val8){
    if (_colorMapChanged){
        recalcColorMap();
    }
    for (unsigned int i=0; i<val16.size(); i++){
        val8.push_back(colorMap[val16[i]]);
    }
}



void Is16BitRGB::recalcColors(vector <unsigned char>& valBefore, vector <unsigned char>& valAfter){
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
