#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QSlider>
#include <QLineEdit>
#include <QKeyEvent>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPalette>

#include "imagehistogram.h"
#include "imagepicturemode.h"
//My_Code
class PropertyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    bool isNumericLine;         /*!< is it numeric line*/

    /*!
        \brief Constructor
        \param parent - parent widget
        \param itIsNumericLine - is it numeric line
    */
   // MyLineEdit(QLineEdit *parent=0, bool itIsNumericLine=true);
   PropertyLineEdit(QWidget *parent=0, bool itIsNumericLine=true): QLineEdit(parent){
        isNumericLine = itIsNumericLine;
    }

signals:
    void setVal(int);           /*!< set value*/
    void setValD(double);       /*!< set value double*/
public slots:
    /*!
        \brief on key press
        \param event - event pointer
    */
    void keyPressEvent ( QKeyEvent * event ){
        if (isNumericLine){
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
                int val;
                double valD;
                bool temp;
                valD = text().toDouble(&temp);
                if (temp){
                    emit setValD(valD);
                }
                val = text().toInt(&temp);
                if (temp){
                    emit setVal(val);
                }
            }
            else if ((event->key() >= '0' && event->key() <= '9') || event->key() == Qt::Key_Backspace || event->key() == '.' ||
                      event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Delete){
                QLineEdit::keyPressEvent(event);
            }
        }
        else{
            if (event->key() == Qt::Key_Return  || event->key() == Qt::Key_Enter){
                emit setVal(Qt::Key_Return);
            }
            else{
                QLineEdit::keyPressEvent(event);
            }
        }
    }
};


class ImageManipulator : public QDialog{
    Q_OBJECT
public:
    enum PARAMETERS{BRIGHTNESS, CONTRAST, ROTATE, GAMMA, LBORDER, RBORDER, HORFLIP, VERFLIP,
                    SCALE,MAXCONTR, TIMER, PICMODE, FULLPICMODE, PICX,PICY, DIMX,DIMY};
    //QGroupBox *gbPicManip;
    QGroupBox *gbHistogram;
    QGroupBox *gbDisplayPic;
    QGroupBox *gbDisplayPicPos;
    PropertyLineEdit *rightLine;      /*!< right border line edit*/
    PropertyLineEdit *leftLine;       /*!< left border line edit*/
    PropertyLineEdit *brLine;         /*!< brightness line edit*/
    PropertyLineEdit *conLine;        /*!< contrast line edit*/
    PropertyLineEdit *gmLine;         /*!< gamma line edit*/
    PropertyLineEdit *sclLine;         /*!< scale line edit*/
    PropertyLineEdit *TimerLine;         /*!< gamma line edit*/
    QSlider *leftBorder;        /*!< left border slider*/
    QSlider *rightBorder;       /*!< right border slider*/
    QSlider *brig;              /*!< brightness slider*/
    QSlider *contr;             /*!< contrast slider*/
    QSlider *gamma;             /*!< gamma slider*/
    QSlider *scale;             /*!< scale slider*/
    QCheckBox *hFl;             /*!< horizontal fliping manipulator*/
    QCheckBox *vFl;             /*!< vertical fliping manipulator*/
    QLabel *lbRotation;
    QComboBox *rotation;

    QLabel *lbHisLB;            /*!< left border label*/
    QLabel *lbHisRB;            /*!< right border label*/
    QLabel *lbHisBr;            /*!< brightness label*/
    QLabel *lbHisCon;           /*!< contrast label*/
    QLabel *lbHisGm;            /*!< gamma label*/
    QLabel *lbScl;              /*!< Scale label*/
    QLabel *lbTimer;            /*!< Timer label*/

    QComboBox *cmb;
    QComboBox *cmbPicMode;
    QCheckBox *fullScreen;
    ImageHistogram *histogram;
    QPushButton *btNewHis;
    QCheckBox *autoNewHis;

    PropertyLineEdit *picMoveXLine;
    PropertyLineEdit *picMoveYLine;
    QLabel *lbPicX;
    QLabel *lbPicY;
    QLabel *lbPicSize;
    int lastbr;                 /*!< brightness value*/
    int lastContr;              /*!< contrast value*/

    int maxContrast;            /*!< maximum contrast value*/
    int minContrast;            /*!< minimum contrast value*/
    int maxBrightness;          /*!< maximum brightness value*/
    int minBrightness;          /*!< minimum brightness value*/
    bool isRGB;                 /*!< is it RGB image*/
    bool resetParam;            /*!< is should reset widget values*/

    ImageManipulator(QList<QVariant> param, QVector <unsigned short> val16, QImage image);
    void setRotationVal(int stVal);
    void setRotation(int stVal);
    void initFliping(bool ver, bool hor );
    void initBr(int stBr);
    void initCon(int stContr);
    void initScale(double scl);
    void initGm(int gm);
    void initLBorder(int stLBorder);
    void initRBorder(int stRBorder);
    void initTimer(int time);
    void setVisibleGamma(bool);
    void setVisibleBorder(bool);

    QGroupBox* createHis(int, int, int, QVector<unsigned short> val16, QImage image);
    QGroupBox* createDisplayPicPos(QString px, QString py, QString dx, QString dy);
    QGroupBox* createDisplayPic(bool full, int pm, int time);

signals:
    void sendHorFlipVal(QVariant val);  /*!< sending horizontal fliping value \param val - value*/
    void sendVerFlipVal(QVariant val);  /*!< sending vertical fliping value \param val - value*/
    void sendRotationVal(QVariant val); /*!< sending rotation value \param val - value*/

    void setRBorder(unsigned short);        /*!< set right border limit of grescale image*/
    void setLBorder(unsigned short);        /*!< set left border limit of grescale image*/
    void setBr(QVariant);                   /*!< set brightness value*/
    void setCon(QVariant);                  /*!< set contrast value*/
    void setGm(QVariant);                   /*!< set Gamma value*/
    void setTime(int val);
    void setScaleSignal(double val);
    void changeFormatOfColor(int);          /*!< set Color Format*/
    void changePictureModeSignal(int value);      /*!< set Picture Mode*/
    void fullScreenMode(bool);
    void autoHistogram(bool);
    void getDataHistogram();
    void chPicY(int);
    void chPicX(int);
public slots:
    void setPicX(int val);
    void setPicY(int val);
    void setShowPicSize(int,int,int,int);
    void setDim(int valX, int valY);
    void showHistogramSlot(bool);
    void autoHistogramSlot(bool val);
    void onBtNewHisClick();
    void fullScreenSlot(bool val);
    void changeFormat(int value);
    void changePictureMode(int value);
    void setRightBorder(int val);
    void setLeftBorder(int val);
    void setLeftVal(int val);
    void setRightVal(int val);
    void setBrImg(int val);
    void setConImg(int val);
    void setGmImg(int val);
    void horFlipSlot(bool val);
    void verFlipSlot(bool val);
    void rotationSlot(QString val);
    void setTimer(int val);
    void setScaleD(double);
    void setScale(int);
};

#endif // IMAGEMANIPULATOR_H
