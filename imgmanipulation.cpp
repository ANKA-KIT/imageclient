#include "imgmanipulation.h"

#include "math.h"

ImgManipulation::ImgManipulation(QObject *parent) :
    QObject(parent)
{
    MyDevProperty *br = new Brightness();
    MyDevProperty *con = new Contrast;
    MyDevProperty *gm = new Gamma();
    MyDevProperty *rot = new Rotation();
    MyDevProperty *scl = new Scale();
    MyDevProperty *hfl = new HorFlip();
    MyDevProperty *vfl = new VerFlip();
//    BRIGHTNESS = 0, CONTRAST = 1, GAMMA = 2, ROTATION = 3, SCALE = 4, HOR_FLIP = 5, VER_FLIP = 6,
    listProp.push_back(br);
    listProp.push_back(con);
    listProp.push_back(gm);
    listProp.push_back(rot);
    listProp.push_back(scl);
    listProp.push_back(hfl);
    listProp.push_back(vfl);

    qDebug("in ImgManipulation constructor");
}
ImgManipulation::~ImgManipulation(){
    qDebug("in ImgManipulation destructor");
    qDeleteAll(listProp.begin(), listProp.end());
}

///////////http://www.qtforum.org/article/26907/contrast-transparency-brightness.html////////////////////////
////////////////////////////////////////////////http://code.google.com/p/weaver-ncmir/
////////////////////////http://code.google.com/p/weaver-ncmir/source/browse/trunk/src/weaverGui/qImageOperations.cpp?spec=svn11&r=11
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
QImage changeBrightness( const QImage& image, int brightness )
    {
    if( brightness == 0 ) // no change
        return image;
    return changeImage< changeBrightness >( image, brightness );
    }

// contrast is multiplied by 100 in order to avoid floating point numbers
QImage changeContrast( const QImage& image, int contrast )
    {
    if( contrast == 100 ) // no change
        return image;
    return changeImage< changeContrast >( image, contrast );
    }

// gamma is multiplied by 100 in order to avoid floating point numbers
QImage changeGamma( const QImage& image, int gamma )
    {
    if( gamma == 100 ) // no change
        return image;
    return changeImage< changeGamma >( image, gamma );
    }
//---------------------------------------//

////////////////////////////////////////////////////////////////////////////////////////
QImage ImgManipulation::chBrightness(QImage& image, int brightness ){
    return changeBrightness(image, brightness );
}
QImage ImgManipulation::chContrast(QImage& image, int brightness ){
    return changeContrast(image, brightness );
}
QImage ImgManipulation::chGamma(QImage& image, int brightness ){
    return changeGamma(image, brightness );
}
/////////////////////////////////////////


QImage ImgManipulation::chRotate(QImage &image, int val){
    QTransform mat;
    mat.rotate(val);
    QImage tempImg;
    tempImg = image.transformed(mat);
    return tempImg;
}

QImage ImgManipulation::chScale(QImage &image, double val){
    QImage tempImg;
    tempImg = image.scaled(image.width() * val, image.height() * val);
    return tempImg;
}

QImage ImgManipulation::chScale(QImage &image, double valX, double valY){
    QImage tempImg;
    tempImg = image.scaled(valX, valY);
    return tempImg;
}

QImage ImgManipulation::chHorFlip(QImage &image, bool val){
    QImage tempImg;
    QMatrix mat;
    mat = QMatrix().scale(-1, 1); // make a vertical flip      !!!!!!!!!!!!!!!!!!!!!!!!1
    tempImg = image.transformed(mat);
    return tempImg;
}

QImage ImgManipulation::chVerFlip(QImage &image, bool val){
    QImage tempImg;
    QMatrix mat;
    mat = QMatrix().scale(1, -1); // make a vertical flip      !!!!!!!!!!!!!!!!!!!!!!!!1
    tempImg = image.transformed(mat);
    return tempImg;
}

double ImgManipulation::getScaleVal(){
    return listProp.at(SCALE)->getValue().toDouble();
}
double ImgManipulation::getRotationVal(){
    return listProp.at(ROTATION)->getValue().toDouble();
}
int ImgManipulation::getContrastVal(){
    return listProp.at(CONTRAST)->getValue().toInt();
}
int ImgManipulation::getBrightnessVal(){
    return listProp.at(BRIGHTNESS)->getValue().toInt();
}
int ImgManipulation::getGammaVal(){
    return listProp.at(GAMMA)->getValue().toInt();
}
bool ImgManipulation::getHorFlipVal(){
    return listProp.at(HOR_FLIP)->getValue().toBool();
}
bool ImgManipulation::getVerFlipVal(){
    return listProp.at(VER_FLIP)->getValue().toBool();
}

void ImgManipulation::resetParam(){
    listProp.at(SCALE)->setValue(1.0);
    listProp.at(VER_FLIP)->setValue("false");
    listProp.at(HOR_FLIP)->setValue("false");
    listProp.at(ROTATION)->setValue(0);
    listProp.at(BRIGHTNESS)->setValue(0);
    listProp.at(CONTRAST)->setValue(100);
    listProp.at(GAMMA)->setValue(100);
}

void ImgManipulation::resetParam(QImage &img){
    chScale(img, 1);
    chVerFlip(img, false);
    chHorFlip(img, false);
    chRotate(img, 0);
    chBrightness(img, 0);
    chContrast(img, 100);
    chGamma(img, 100);
}

void ImgManipulation::setParams(QList <QVariant> &newListProp){
    for (int i =0; i<newListProp.size(); i++)
        listProp.at(i)->setValue(newListProp.at(i));
}

void ImgManipulation::getParams(QList <QVariant> &getListProp){
    for (int i =0; i<listProp.size(); i++)
        getListProp.push_back(listProp.at(i)->getValue());
}
