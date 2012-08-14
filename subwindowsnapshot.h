#ifndef SUBWINDOWSNAPSHOT_H
#define SUBWINDOWSNAPSHOT_H

#include <subwindow.h>
#include <QMenu>
#include <QHBoxLayout>
#include <QResizeEvent>

/*!
  \file subwindowsnapshot.h
  \author Georgii Vasilev
  \class SubWindowSnapshot
  \brief Snapshot subwindow
  ///Class for dealing with snapshot
*/
class SubWindowSnapshot : public SubWindow
{
    Q_OBJECT
private:
    /*!
        \brief Init property values labels
    */
    void initLbSnap();
public:
   // QHBoxLayout *_widgetLayout;
   // QHBoxLayout *hLayoutScrollArea;
  //  QImage* _originImg;     /*!< copy of image for manipulation (not for 16bit gamma,brightness,contrast)*/
    double scl;         /*!< Scale of image when it was made*/
    double difLevelPers;  /*!< picture proportion*/

    /*!
        \brief Contructor
        \param img - realtime snapshot
        \param man - image property
        \param diff - picture proportion
        \param scale - current scale
    */
    SubWindowSnapshot(QImage* img, ImgManipulation* man, double diff, double scale);

    /*!
        \brief void Contructor
    */
    SubWindowSnapshot(){}

    /*!
        \brief Destructor
    */
    ~SubWindowSnapshot();

    /*!
        \brief Create Sizable picture mode
        \param img - image for Sizable mode
    */
    void initFullPicMode(QImage& img);

    /*!
        \brief Create Full picture mode
        \param img - image for fullpicture mode
    */
    void initSizableMode(QImage& img);

    /*!
        \brief Init connects between properties and manipulation
    */
    void initPropConnects();


signals:
    void SnapshotWinChanged(SubWindowSnapshot* pointer);  /*!< snapshot subwindow state was changed \param pointer - subwindow pointer*/
    void closeSnap(SubWindowSnapshot* pointer);           /*!< snapshot subwindow was closed \param pointer - subwindow pointer*/
public slots:
    /*!
        \brief on click close
        \param e - event pointer
    */
    void closeEvent (QCloseEvent *e);

    /*!
        \brief on window state change
        \param oldWSt - last window station
        \param newWSt - new window station
    */
    void handleWindowStateChanged(Qt::WindowStates oldWSt, Qt::WindowStates newWSt);

    /*!
        \brief change scale value on some value
        \param val - value
    */
    void chScaleOn(double val);

    /*!
        \brief change rotation value on some value
        \param val - value
    */
    void chRotationOn(double val);

    /*!
        \brief change brightness value on some value
        \param val - value
    */
    void chBrightnessOn(int val);

    /*!
        \brief change gamma value on some value
        \param val - value
    */
    void chGammaOn(int val);

    /*!
        \brief change contrast value on some value
        \param val - value
    */
    void chContrastOn(int val);

    /*!
        \brief set default values
    */
    void resetImg();

    /*!
        \brief resize subwindow
        \param x - width
        \param y - height
    */
    void resizeWgt(int x, int y);

    /*!
        \brief set scale value server/client
        \param val - value
    */
    void setScale(double val);

    /*!
        \brief set rotation value server/client
        \param val - value
    */
    void setRotation(double val);

    /*!
        \brief set brightness value server/client
        \param val - value
    */
    void setBrightness(int val);

    /*!
        \brief set gamma value server/client
        \param val - value
    */
    void setGamma(int val);

    /*!
        \brief set contrast value server/client
        \param val - value
    */
    void setContrast(int val);

    /*!
        \brief set horizontal fliping value server/client
        \param val - value
    */
    void setHorFlipValue(QString val);

    /*!
        \brief set vertical fliping value server/client
        \param val - value
    */
    void setVerFlipValue(QString val);

    /*!
        \brief set image mode
    */
    void setImageMode(int mode);

    /*!
        \brief On resize subwindow
        \param event  - resize event pointer
    */
    void resizeEvent ( QResizeEvent * event );

    /*!
        \brief set/unset fullpicture mode
        \param val - set/unset fullPictureMode (true - set fullPictureMode/ false - set siziable mode)
    */
    void setFullPictureMode(bool val);
};

#endif // SUBWINDOWSNAPSHOT_H
