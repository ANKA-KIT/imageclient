#ifndef IMGMANIPULATION_H
#define IMGMANIPULATION_H

#include <QObject>
#include <QImage>
#include <enum.h>
#include <mydevproperty.h>
/*!
  \file imgmanipulation.h
  \author Georgii Vasilev
  \class ImgManipulation
  \brief Keep basic manipulation for color image, set property values
  ///Class answear for keeping basic manipulations and connecting devise properties
*/
class ImgManipulation : public QObject
{
    Q_OBJECT
public:
    QList <MyDevProperty *> listProp; /*!< list of properties*/

    /*!
        \brief Constructor
    */
    explicit ImgManipulation(QObject *parent = 0);

    /*!
        \brief Get scale value
        \return Scale value
    */
    double getScaleVal();

    /*!
        \brief Get rotation value
        \return rotation value
    */
    double getRotationVal();

    /*!
        \brief Get Contrast value
        \return Contrast value
    */
    int getContrastVal();

    /*!
        \brief Get Brightness value
        \return Brightness value
    */
    int getBrightnessVal();

    /*!
        \brief Get Gamma value
        \return Gamma value
    */
    int getGammaVal();

    /*!
        \brief Get Horizontal fliping  value
        \return Horizontal fliping (HorFlip) value
    */
    bool getHorFlipVal();

    /*!
        \brief Get Vertical fliping  value
        \return Vertical fliping (VerFlip) value
    */
    bool getVerFlipVal();

    /*!
        \brief change Brightness value
        \param image - image to set
        \param val - value
    */
    QImage chBrightness(QImage& image, int val );

    /*!
        \brief change Contrast value
        \param image - image to set
        \param val - value
    */
    QImage chContrast(QImage& image, int val );

    /*!
        \brief change Gamma value
        \param image - image to set
        \param val - value
    */
    QImage chGamma(QImage& image, int val );

    /*!
        \brief change Rotation value
        \param image - image to set
        \param val - value
    */
    QImage chRotate(QImage &image, int val);

    /*!
        \brief change Scale value
        \param image - image to set
        \param val - value
    */
    QImage chScale(QImage &image, double val);


    /*!
        \brief change Scale value
        \param image - image to set
        \param val - value
    */
    QImage chScale(QImage &image, double valX, double valY);

    /*!
        \brief change Horizotal fliping (HorFlip) value
        \param image - image to set
        \param val - value
    */
    QImage chHorFlip(QImage &image, bool val);

    /*!
        \brief change Vertical fliping (VerFlip) value
        \param image - image to set
        \param val - value
    */
    QImage chVerFlip(QImage &image, bool val);

    /*!
        \brief change properties on default
        \param img - image to set
    */
    void resetParam(QImage &img);

    /*!
        \brief set list of properties
        \param newListProp - property values to set
    */
    void setParams(QList <QVariant> &newListProp);

    /*!
        \brief get list of properties
        \param getListProp - property variable to get
    */
    void getParams(QList <QVariant> &getListProp);

    /*!
        \brief Destructor
    */
    ~ImgManipulation();
public slots:
    /*!
        \brief set default values
    */
    void resetParam();
};

#endif // IMGMANIPULATION_H
