#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMdiArea>
#include <imagehistogram.h>
#include <my_device.h>
#include <starttangowin.h>
#include <subwindowrealtime.h>
#include <subwindowsnapshot.h>
#include <tangosettingswin.h>
#include <menutab.h>
#include <tangovariables.h>
#include <mythread.h>
#include <bgcpl_wgt.h>
#include <manipulator.h>
#include <slidermanip.h>
/*!
  \file mainwindow.h
  \author Georgii Vasilev
  \class MainWindow
  \brief Connects GUI with program
  ///Class which connects GUI with main part of app. To keep Snapshot&Realtime Subwins is used QList
*/
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool histogramManip;    /*!< is it manipulator with histogram*/

    /*!
        \brief reset marker label value
        \param subWin - subwindow pointer
    */
    void reSetMarkerPos(SubWindow *subWin);
    /*!
        \brief get proporsion of height/width
        \return difLevelPers
    */
    double isFullPicReal();

    /*!
        \brief Check focused index, set value into curSubwindow; set prefix of index
        \param curSubwindow - current focused index
        \return prefix
    */
    QString setTitlePrefix(int &curSubwindow);

    /*! \brief Read window settings*/
    void readSettings();

    /*! \brief Write window settings*/
    void writeSettings();

    //void disconnectProp();

    /*! \brief delete all realtime subwindows*/
    void deleteAllReal();

    /*! \brief delete all snapshot subwindows*/
    void deleteAllSnap();

    /*!
        \brief Set manipulator with histogram
        \param subW - subwindow for control
    */
    void setSlider(SubWindow* subW);

    /*!
        \brief init manipulator with histogram
        \param subW - subwindow for control
    */
    void connectPropertyValues(SubWindow* subW);

    /*!
        \brief set connects for manipulator with histogram
        \param subW - subwindow for control
        \param mode - BGCPL_WGT_MODE
    */
    void setSliderConnects(SubWindow*subW, int mode);

    /*!
        \brief init manipulator
        \param subW - subwindow for control
    */
    void setManipulatorWGT(SubWindow *subW);

    /*!
        \brief set connects for manipulator
        \param subW - subwindow for control
        \param mode - BGCPL_WGT_MODE
    */
    void setManipConnects(SubWindow *subW, int mode);

    /*!
        \brief Set manipulator
        \param subW - subwindow for control
    */
    void setManip_wgt(SubWindow* subW);

    /*!
        \brief Set full picture mode for subwindow
        \param subW - subwindow for control
    */
    void setFullPictureMode(SubWindow* subW);



    /*!
        \brief init contextmenu for realtime subwindow
        \return contextmenu
    */
    QList<QAction*> realtimeMenu();

    /*!
        \brief init contextmenu for snapshot subwindow
        \return contextmenu
    */
    QList<QAction*> snapshotMenu();


//    void connectPropertyValues(SubWindowRealtime *);
    /*!< \brief delete manipulator with histogram*/
    void deletePropertyValues();
//    void connectPropertyValues(SubWindowSnapshot *);

//    void setManipulatorWGT(SubWindowRealtime *);
    /*!< \brief delete manipulator*/
    void deleteManipulatorWGT();
//    void setManipulatorWGT(SubWindowSnapshot *);

    /*!
        \brief set connect for window manipulator an property
        \param opt - prorety name
    */
    void connectManipulation(int opt);

    /*!
        \brief set PictureMode for realtime subwindow
        \param mode - name of mode
    */
    void setImageMode(int mode);

    /*!
        \brief set BGCPL_WGT_MODE from ImageTypes
        \param mode - name of  PictureMode mode
        \return BGCPL_WGT_MODE value
    */
    int getBGCPL_WGT_MODE(int mode);

    /*! \brief set ImageMode and ImageFormat values which were sended as command parametrs */
    void setStartImgModeAndFormat();

public:
    SliderManip *slider;            /*!< Manipulator with histogram*/
    Manipulator *manip_wgt;         /*!< Manipulator*/
    bool startWithParams;           /*!< Is app was start with -f or -m attribute*/
    int *startImageMode;            /*!< Start ImageMode value*/
    int *startImageFormat;          /*!< Start ImageFormat value*/
    int *startDelayTime;            /*!< Delay value*/
    bool *startWithDelay;           /*!< Start realtime with delay*/

    QList<SubWindowRealtime *>  listReal;       /*!< List of realtime subwindows*/
    QList<SubWindowSnapshot *>  listSnap;       /*!< List of snapshot subwindows*/
    int  curRealtimeInt;            /*!< current realtime subwindow index*/
    int  realtimeIntLast;           /*!< last focused realtime subwindow index*/
    int  curSnapshotInt;            /*!< current snapshot subwindow index*/
    int curSnapshotIntLast;         /*!< last focused snapshot subwindow index*/
    QList<MyThread *>  threads;     /*!< list of threads*/

    Ui::MainWindow *ui;             /*!< pointer to some widgets*/
    StartTangoWin* tangoDev;        /*!< Window for setting connection with tango device*/
    TangoSettingsWin* tangoDevSet;  /*!< Manipulator window*/
    TangoVariables *tangoVar;       /*!< window for setting tango attributes name*/
    SetMarker *marker;              /*!< window for setting marker position*/
    QMdiArea*  area;                /*!< Area for subwindow locaton*/
    MenuTab* commandMenu;           /*!< Command menu of app*/

    QLabel *lbMouseX;               /*!< label for displaying Mouse X position*/
    QLabel *lbMouseY;               /*!< label for displaying Mouse Y position*/
    QLabel *lbPixVal;               /*!< label for displaying pixel value in mouse position*/
    QLabel *lbMarker;               /*!< label for displaying marker position*/
    QPushButton *bt;                /*!< NOT USED*/
    QPushButton *btMkSnap;          /*!< NOT USED*/
    QPushButton *bt16bit;           /*!< NOT USED*/

    /*! \brief Constructor*/
    explicit MainWindow(QWidget *parent = 0);

    /*! \brief Destructor*/
    ~MainWindow();
public slots:
    /*!
        \brief Set connects subwindow and mainwindow
        \param subW - subwindow for control
    */
    void connectSubwindowSignals(SubWindow *subWin);

    /*! \brief delete window for setting tango device*/
    void delStartTangoWin();

    /*! \brief delete manipulator window*/
    void delTangoSettingWin();

    /*! \brief delete window for setting tango attributes name*/
    void delTangoNamesWin();

    /*! \brief init manipulator window*/
    void initTangoSettingWin(int param);

    /*! \brief init window for setting tango device*/
    void initStartTangoWin();

     /*! \brief init window for setting tango attributes name*/
    void initTangoNamesWin();

    /*!
        \brief init raltime subwindow
        \param servName - tango_host+device_name
        \param imgAtr - image attribure name
    */
    void mkRealtime(QString servName, QString imgAtr );

    /*! \brief make snapshot (slot)*/
    void mkSnapshot();

    /*!
        \brief init snapshot subwindow
        \param image - widget for copy information
        \param difHW - image proporsion
    */
    void mkSnapshot(ImageWidget* image, double difHW);

    /*!
        \brief on resize Mainwindow
        \param e - event pointer
    */
    void resizeEvent( QResizeEvent *e );

    /*!
        \brief on realtime subwindow change focus
        \param curRealtimeWin - pointer to focused realtime subwindow
    */
    void realtimeChanged(SubWindowRealtime* curRealtimeWin);

    /*!
        \brief on snapshot subwindow change focus
        \param curSnapWin - pointer to focused snapshot subwindow
    */
    void SnapshotChanged(SubWindowSnapshot* curSnapWin);

    /*!
        \brief on click close
        \param closeEvent - event pointer
    */
    void closeEvent ( QCloseEvent * closeEvent);

    /*!
        \brief on close realtime subwindow
        \param pointer - pointer to realtime
    */
    void onCloseRaltime(SubWindowRealtime *pointer);

    /*!
        \brief on close snapshot subwindow
        \param pointer - pointer to snapshot
    */
    void onCloseSnapshot(SubWindowSnapshot *pointer);

    /*! \brief init manipulator window for manipulate Brightnes*/
    void settingBrightness();

    /*! \brief init manipulator window for manipulate Contrast*/
    void settingContrast();

    /*! \brief init manipulator window for manipulate Gamma*/
    void settingGamma();

    /*! \brief init manipulator window for manipulate Rotation*/
    void settingRotation();

    /*! \brief init manipulator window for manipulate Scale*/
    void settingScale();

    /*! \brief init manipulator window for manipulate Horizontal fliping (HorFlip)*/
    void settingHorFlip();

    /*! \brief init manipulator window for manipulate Horizontal fliping (VerFlip)*/
    void settingVerFlip();

    /*! \brief init manipulator window for setting timeout value*/
    void settingTimeOut();

    /*! \brief init manipulator window for sending command*/
    void sendingTangoCommand();

    /*! \brief init manipulator window for manipulate Brightnes (change value on some one)*/
    void chBrightnessOn();

    /*! \brief init manipulator window for manipulate Contrast (change value on some one)*/
    void chContrastOn();

    /*! \brief init manipulator window for manipulate Gamma (change value on some one)*/
    void chGammaOn();

    /*! \brief init manipulator window for manipulate Rotation (change value on some one)*/
    void chRotationOn();

    /*! \brief init manipulator window for manipulate Scale (change value on some one)*/
    void chScaleOn();

    /*! \brief save snapshot (slot)*/
    void saveImg();

    /*! \brief print snapshot (slot) (NOT RELEASED)*/
    void printSnap();

    /*! \brief set server operation*/
    void chServerManipulation();

    /*! \brief reset subwindow (slot)*/
    void resetImg();

    /*!
        \brief change color format of realtime
        \param val - color format (QImage::Format)
    */
    void changeColorFormat(int val);

    /*!
        \brief set tango attributes name (from tangoVar )
        \param ls - list of attributes name
    */
    void setTangoVar(QStringList ls);

    /*!
        \brief set in label information about pixel color
        \param r - 8bit [0..255] red pixel value
        \param g - 8bit [0..255] green pixel value
        \param b - 8bit [0..255] blue pixel value
    */
    void setRGBlbVal(int r, int g, int b);

    /*!
        \brief set in label information about pixel color
        \param RGB - 8bit [0..255] greyscale pixel value
        \param RGB - 16bit [0..65535] greyscale pixel value
    */
    void setGreylbVal(int RGB, int val);

    /*!
        \brief set in label information about pixel color
        \param RGB - 8bit [0..255] greyscale pixel value
    */
    void setGreylbVal(int RGB);

    /*!
        \brief set in label information about mouse X position
        \param x - X mouse position
    */
    void setMouseXlbVal(int x);

    /*!
        \brief set in label information about mouse Y position
        \param y - Y mouse position
    */
    void setMouseYlbVal(int y);

    /*!
        \brief set in labels information about mouse position
        \param x - X mouse position
        \param y - Y mouse position
    */
    void setMousePos(int x, int y);

    /*!
        \brief set in labels information about marker position
        \param str - text for displaying
    */
    void setMarker(QString str);

    /*!
        \brief set left pixel limit for realtime
        \param val - value
    */
    void setLeftBorder(unsigned short val);

    /*!
        \brief set right pixel limit for realtime
        \param val - value
    */
    void setRightBorder(unsigned short val);

    /*!
        \brief set left pixel limit for snapshot
        \param val - value
    */
    void setLeftBorderSnp(unsigned short val);

    /*!
        \brief set right pixel limit for snapshotMenu()
        \param val - value
    */
    void setRightBorderSnp(unsigned short val);

    /*! \brief set PictureMode as IS_16BITIMG_GREY */
    void set16BitGreyImageMode();

    /*! \brief set PictureMode as IS_16BITIMG_RGB */
    void set16BitRGBImageMode();

    /*! \brief set PictureMode as IS_8BITIMG_GREY */
    void set8BitGreyImageMode();

    /*! \brief set PictureMode as IS_8BITIMG_COLOR */
    void set8BitColorImageMode();

    /*! \brief set PictureMode as IS_RGBIMG_GREY */
    void setRGBGreyImageMode();

    /*! \brief set PictureMode as IS_RGBIMG_COLOR */
    void setRGB_ARGBImageMode();

    /*! \brief set Full picture mode for realtime subwindow*/
    void setFullPictureMode();
    void setRealtimePause();

    /*! \brief prepare variables for change manipulator*/
    void setManipulator();

    /*! \brief change manipulator for realtime subwindow*/
    void setManipulatorReal();

    /*! \brief change manipulator for snapshot subwindow*/
    void setManipulatorSnap();

    /*! \brief set Full picture mode for snapshot subwindow*/
    void setFullPictureModeSnap();

    /*! \brief change manipulator with/without histogram*/
    void chManipulator(SubWindow* subW);

    /*! \brief Set Qt image format*/
    void setIndex8();
    /*! \brief Set Qt image format*/
        void setRGB32();
        /*! \brief Set Qt image format*/
        void setARGB32();
        /*! \brief Set Qt image format*/
        void setARGB32Pre();
        /*! \brief Set Qt image format*/
        void setRGB16();
        /*! \brief Set Qt image format*/
        void setARGB8565Pre();
        /*! \brief Set Qt image format*/
        void setRGB666();
        /*! \brief Set Qt image format*/
        void setARGB6666Pre();
        /*! \brief Set Qt image format*/
        void setRGB555();
        /*! \brief Set Qt image format*/
        void setARGB8555Pre();
        /*! \brief Set Qt image format*/
        void setRGB888();
        /*! \brief Set Qt image format*/
        void setRGB444();
        /*! \brief Set Qt image format*/
        void setARGB4444Pre();


        /*! \brief Create window for setting marker */
        void setMarkerPos();
        /*!
            \brief set Marker position
            \param X - X marker position
            \param Y - Y marker position
        */
        void createMarker(int X,int Y);
        /*!  \brief Delete set Marker  window */
        void delMarkerWin();

};

#endif // MAINWINDOW_H
