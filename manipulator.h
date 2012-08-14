#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <rsfl_wgt.h>
#include <bgcpl_wgt.h>
#include <picturemode.h>
/*!
  \file manipulator.h
  \author Georgii Vasilev
  \class Manipulator
  \brief Basic Manipulator panel
  ///Based on modal widget
*/
using namespace br_gm_con_pixLevel;
class Manipulator : public QWidget
{
    Q_OBJECT
protected:
    /*!
      \brief Init widgets
      \param mode - BGCPL_WGT_MODE
      \param prop - device properties
      \param pm - current picture mode
    */
    void initObjects(int mode, QList <MyDevProperty *> &prop, PictureMode *pm);
public:
    BGCPL_WGT *bgcpl; /*!< Brightness gamma comtrast pixel level manipulator*/
    RSFL_WGT  *rsfl;    /*!< rotation scale flping manipulator*/
    QPushButton *btHis; /*!< Histogram/single manipulator change button*/
    /*!
      \brief Constructor
      \param mode - BGCPL_WGT_MODE
      \param prop - device properties
      \param pm - current picture mode
    */
    explicit Manipulator(int mode, QList <MyDevProperty *> &prop, PictureMode *pm,QWidget *parent = 0);

    /*!
      \brief On change manipulator style (Histogram - single manipulator)
      \param mode - BGCPL_WGT_MODE
      \param prop - device properties
      \param pm - current picture mode
    */
    void changeDevice(int mode, QList <MyDevProperty *> &prop, PictureMode *pm);

    /*! \brief Destructor */
    ~Manipulator();

signals:
    void showhistogram(); /*!< change manipulator style*/
public slots:
    /*!
        \brief on click close
        \param e - event pointer
    */
    void closeEvent (QCloseEvent *e);

    /*! \brief On btHis click */
    void turnOnHistogram();
};

#endif // MANIPULATOR_H
