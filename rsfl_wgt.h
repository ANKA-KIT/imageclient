#ifndef RSFL_H
#define RSFL_H

#include <propertymanipulation.h>
#include <mydevproperty.h>
#include <picturemode.h>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QWidget>

/*!
  \file rsfl_wgt.h
  \author Georgii Vasilev
  \class RSFL_WGT
  \brief Rotation-Scale-Fliping manipulation widget of
  ///Rotation, Scale, Fliping (VerFlip, HorFlip)  manipulation widget. Based on Scl_WGT,RSFL_WGT, Fliping as QCheckBox, Rotation as QComboBox
*/
class RSFL_WGT : public QWidget
{
    Q_OBJECT
protected:
    /*!
      \brief init fliping manipulator
      \param hor - horizontal fliping value
      \param ver - vertical fliping value
    */
    void setFliping(bool hor, bool ver);

    /*!
      \brief init rotation manipulator
      \param stVal - rotation value
    */
    void setRotation(int stVal);
public:
    QCheckBox *hFl;             /*!< horizontal fliping manipulator*/
    QCheckBox *vFl;             /*!< vertical fliping manipulator*/
    QComboBox *rotation;        /*!< rotation manipulator*/
    QLabel *lbRotation;         /*!< label rotation*/
    Scl_WGT   *scale;           /*!< scale manipulator*/

    /*!
      \brief Constructor
      \param prop - device property values
    */
    explicit RSFL_WGT(QList <MyDevProperty *> &prop, QWidget *parent = 0);

    /*!
      \brief set rotation value
      \param stVal - rotation value
    */
    void setRotationVal(int stVal);

    /*! \brief Destructor  */
    ~RSFL_WGT();
signals:
    void sendHorFlipVal(QVariant val);  /*!< sending horizontal fliping value \param val - value*/
    void sendVerFlipVal(QVariant val);  /*!< sending vertical fliping value \param val - value*/
    void sendRotationVal(QVariant val); /*!< sending rotation value \param val - value*/
public slots:

    /*!
      \brief on hFl checked
      \param val - set value
    */
    void horFlipSlot(bool val);

    /*!
      \brief on vFl checked
      \param val - set value
    */
    void verFlipSlot(bool val);

    /*!
      \brief on rotation currentIndexChanged
      \param val - set value
    */
    void rotationSlot(QString val);

};

#endif // RSFL_H
