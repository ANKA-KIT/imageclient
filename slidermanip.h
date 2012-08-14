#ifndef SLIDERMANIP_H
#define SLIDERMANIP_H

#include <propertymanipulation.h>
#include <bgcpl_wgt.h>
#include <mydevproperty.h>
#include <picturemode.h>
#include <imagehistogram.h>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <rsfl_wgt.h>

/*!
  \file slidermanip.h
  \author Georgii Vasilev
  \class SliderManip
  \brief Manipulator with Histogram widget
  /// Manipulator with Histogram widget
*/
using namespace br_gm_con_pixLevel;
class SliderManip : public QWidget
{
    Q_OBJECT
protected:
    /*! \brief Strat widgets' position*/
    void setStartWidgetPosition();

    /*! \brief init lef-top corner panel*/
    void setLeftPanel();

    /*!  \briefinit btHis*/
    void initBtHis();

    /*! \brief init manipulators*/
    void initManipulators(int mode,  QList <MyDevProperty *> &prop, PictureMode *pm, QImage* img, vector <unsigned short> &usData);
public:
    BGCPL_WGT *bgcpl;           /*!< manipulator widget*/
    RSFL_WGT *rsfl;             /*!< manipulator widget*/
    Histogrammm *histogram;     /*!< histogram widget*/
    QImage *imgPointer;         /*!< pointer to the image*/
    int curPicMode;             /*!< current picture mode*/
    QCheckBox *cbData;          /*!< CheckBox 16 bit histogram*/
    QCheckBox *cbAutoData;      /*!< CheckBox auto redrawing histogram*/
    QPushButton *refreshHis;    /*!< button redraw histogram*/
    QPushButton *btHis;         /*!< button change manipulator style*/

    /*!
        \brief Constructor
        \param mode -   BGCPL_WGT_MODE
        \param prop -   list of properties
        \param pm -     picture mode object
        \param img -    image
        \param usData - 16 bit data image
    */
    explicit SliderManip(int mode, QList <MyDevProperty *> &prop, PictureMode *pm, QImage* img, vector <unsigned short> &usData, QWidget *parent = 0);

    /*!
        \brief Constructor
        \param mode -   BGCPL_WGT_MODE
        \param prop -   list of properties
        \param pm -     picture mode object
        \param img -    image
        \param usData - 16 bit data image
    */
    void changeDevice(int mode,  QList <MyDevProperty *> &prop, PictureMode *pm, QImage* img, vector <unsigned short> &usData );

    /*! \brief Destructor*/
    ~SliderManip();
signals:
    void get16Bit();            /*!< get 16 bit data for drawing histogram*/
    void hidehistogram();       /*!< change manipulator style*/
public slots:
    /*! \brief get 16bit data from image to draw histogram \param data - 16 bit image data*/
    void get16BitData(vector <unsigned short> data);

    /*! \brief on refreshHis click*/
    void redrawHistogram();

    /*! \brief recalculate histogram (Not 16bit)*/
    void recalcHistogram();

    /*! \brief recalculate histogram (16bit) \param data - 16 bit image data*/
    void recalcHistogram16Bit(vector <unsigned short> data);

    /*! \brief on window resize \param event - event  pointer*/
    void resizeEvent ( QResizeEvent * event );

    /*! \brief on window close \param e - event  pointer*/
    void closeEvent (QCloseEvent *e);

    /*! \brief on btHis click */
    void turnOffHistogram();
};

#endif // SLIDERMANIP_H
