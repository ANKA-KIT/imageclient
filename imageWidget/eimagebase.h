#ifndef EIMAGEBASE_H
#define EIMAGEBASE_H

#include <QFileDialog>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QRgb>
#include <QScrollArea>
#include <QVariant>

#include "eimagescreen.h"
#include "imagemanipulator.h"
#include "imagepicturemode.h"

struct Parametres {
    int brightness;
    int contrast;
    int gamma;
};

class EImageBase : public QScrollArea
{
    Q_OBJECT
private:
    void init();
protected:
    QImage setImageByFullScreenMode(QImage img);
public:

    Parametres imageParams;

    EImageBase(QWidget *parent = 0);
    EImageBase(QImage img, int x, int y, int pm, QWidget *p = 0);
    EImageBase(QVector<unsigned short > vector, int x, int y, int pm, QWidget *p);
// EImage(QVector<unsigned char>& vector, int x, int y, int pm, QScrollArea *p = 0);

    void drawing(QImage &img);

    QVector<unsigned char> getImageVector(QImage &img, int w, int h);
    void saveImg(QImage img);
    void fastSave();

    QAction *params;
    unsigned long iii;
    QVector<unsigned short> val16;
    QVector<unsigned char>  val;
    bool manipulatorIsClosed;
    int dimX, dimY;
    int _timer;

    QImage errorImage();
    QImage setPropertiesOnImg(QImage img);
    QImage setPropertiesOnImg(QImage img, QVariant *params);

//    void ShowContextMenu(const QPoint& pos);
//    void setActionMenu(QList<QAction *> acts);
    ImageManipulator *manip;
    double imageWidth();
    double imageHeight();

    ImagePictureMode *picMode;
    EImageScreen *wgt;

    QImage setVisualPropertiesOnImg(QImage img);

    double getRotate();
    bool getHFlip();
    bool getVFlip();
    double getScale();
    int getBrightness();
    int getGamma();
    int getContrast();

    double serverValues[7];
    double valuesForWrite[6];
    int __serverMode;
    enum WORKMODE {
        SINGLE,
        READ,
        READ_WITH_SERVERTRANSFORMATION,
        WRITE,
        WRITE_WITH_SERVERTRANSFORMATION
    };

    QMenu *saveWholePic;
    QMenu *saveCatPic;
signals:
    void timerSignal(int time);
    void imgChanged(QImage);

    void scaleValue(double);
    void rotateValue(double);
    void vFlipValue(bool);
    void hFlipValue(bool);
    void gammaValue(int);
    void contrastValue(int);
    void brightnessValue(int);

    void mousePosition(QPoint);
    void rgbImageColor(int, int, int);
    void greyscaleImageColor(int);

    void newMarker(QPoint, QRgb );
    void fullscreenMode(bool);
public slots:
    void onNewMarker(QPoint, QRgb col);
    void setMarker(QPoint, QRgb);
    void onScreenReapinting(QPoint p);
    void saveImgWithMarkers(QImage img);
    void saveCatImgWithMarkers(QImage img);

    void initMarker();
    QPoint convertToImagePoint(int x, int y);
    void setFullscreenMode(bool val);

    void sendTimer(int time);////////////////
    void chImageMode(int mode);
    void  setImageType(int type);

    virtual void showParams(){}
    virtual void drawHistogram();

    void saveWhole();
    void saveWholeMarked();
    void saveCatMarked();
    void saveCat();

    void setBrightness(QVariant);
    void setContrast(QVariant);
    void setGamma(QVariant);
    void setLBorder(unsigned short);
    void setRBorder(unsigned short);
    void setRotate(QVariant);
    void setHFlip(QVariant);
    void setVFlip(QVariant);
    void setScale(double val);

protected slots:
    void manipDestroed();

    QImage changeGammaImg( const QImage& image, int gamma );
    QImage changeContrastImg( const QImage& image, int contrast );
    QImage changeBrightnessImg( const QImage& image, int brightness );
};
//My_Code_End
#endif // EIMAGEBASE_H
