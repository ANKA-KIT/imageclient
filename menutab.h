#ifndef MENUTAB_H
#define MENUTAB_H
#include <QObject>
#include <QString>
#include <QMenu>
#include <enum.h>
/*!
  \file menutab.h
  \author Georgii Vasilev
  \class MenuTab
  \brief Command menu
  ///keep whole apps manipulations
*/
class MainWindow;
class SubWindowRealtime;
class SubWindowSnapshot;

class MenuTab : public QObject
{
    Q_OBJECT

private:
    /*! \brief init actions for realtime subwindow manipulation*/
    void initPropManipRealtime();

    /*! \brief init actions for snapshot subwindow manipulation*/
    void initPropManipSnap();

    /*! \brief init actions for picture mode*/
    void initPicMode();

    /*! \brief init server actions*/
    void initServer();

    /*! \brief init realtime actions*/
    void initRealtime();

    /*! \brief init snapshot actions*/
    void initSnap();

    /*! \brief init menu*/
    void createMenu();

    /*! \brief init Actions*/
    void createActions();

    /*! \brief set enable for not 16 bit image mode*/
    void setUCharImageModeEnable(bool mode);
public:
    QString trueIcon;                   /*!< path to true icon*/
    QString falseIcon;                  /*!< path to false icon*/
    MainWindow *mainWin;                /*!< mainwindow pointer*/
    QMenu *server;                      /*!< Server menu*/
    QMenu *snapshot;                    /*!< Snapshot menu*/
    QMenu *realtime;                    /*!< Realtime menu */

    QAction * addNewDevice;             /*!< set tango device in new app */
    QAction * pushCommand;              /*!< set tango command */
    QAction * serverManipulation;       /*!< Make operations on the server */
    QAction * serverAttrNames;          /*!< Set tango attributes name*/
    QAction * exitAct ;                 /*!< Stop app */

    QMenu *setValRealtime;              /*!< Set value for realtime */
    QAction *scaleRealtime;             /*!< Set Scale value realtime */
    QAction *setBrightnessRealtime;     /*!< Set Brightness value realtime */
    QAction *setContrastRealtime;       /*!< Set Contrast value realtime */
    QAction *setGammaRealtime ;         /*!< Set Gamma value realtime */
    QAction *setRotationRealtime;       /*!< Set Rotation value realtime */
    QMenu *changeOnValRealtime;         /*!< Change value for realtime */
    QAction *chOnScaleRealtime;         /*!< Change Scale value realtime on*/
    QAction *chOnBrightnessRealtime;    /*!< Change Brightness value realtime on*/
    QAction *chOnContrastRealtime;      /*!< Change Contrast value realtime on*/
    QAction *chOnGammaRealtime ;        /*!< Change Gamma value realtime on*/
    QAction *chOnRotationRealtime;      /*!< Change Rotation value realtime on*/
    QAction *verFlipRealtime;           /*!< Set Vertical fliping (VerFlip) value realtime*/
    QAction *horFlipRealtime ;          /*!< Set Horizontal fliping (HorFlip) value realtime*/
    QAction *resetImgRealtime;          /*!< Reset value realtime*/
    QAction *makeMarker;                /*!< Create marker throw window*/

    QAction *makeSnapshot;              /*!< make snapshot from realtime*/
    QAction *printSnapshot;             /*!< print snapshot */
    QAction *saveSnapshot;              /*!< save snapshot */
    QMenu *setValSnapshot;              /*!< Set value for snapshot*/
    QAction *scaleSnapshot;             /*!< Set Scale value snapshot */
    QAction *setBrightnessSnapshot;     /*!< Set Brightness value snapshot */
    QAction *setContrastSnapshot;       /*!< Set Contrast value snapshot */
    QAction *setGammaSnapshot	;       /*!< Set Gamma value snapshot */
    QAction *setRotationSnapshot;       /*!< Set Rotation value snapshot */
    QMenu *changeOnValSnapshot;         /*!< Change value for snapshot */
    QAction *chOnScaleSnapshot;         /*!< Change Scale value snapshot on*/
    QAction *chOnBrightnessSnapshot;    /*!< Change Brightness value snapshot on*/
    QAction *chOnContrastSnapshot;      /*!< Change Contrast value snapshot on*/
    QAction *chOnGammaSnapshot	;       /*!< Change Gamma value snapshot on*/
    QAction *chOnRotationSnapshot;      /*!< Change Rotation value snapshot on*/
    QAction *horFlipSnapshot;           /*!< Set Vertical fliping (VerFlip) value snapshot*/
    QAction *verFlipSnapshot;           /*!< Set Horizontal fliping (HorFlip) value snapshot*/
    QAction *resetImgSnapshot;          /*!< Reset value snapshot*/

    QMenu *setImageMode;                /*!< Set image mode*/
    QAction *is16BitGrey;               /*!< Set image mode IS_16BITIMG_GREY*/
    QAction *is16BitRGB;               /*!< Set image mode IS_16BITIMG_RGB*/
    QAction *is8BitGrey;                /*!< Set image mode IS_8BITIMG_GREY*/
    QAction *is8BitColor;               /*!< Set image mode IS_8BITIMG_COLOR*/
    QAction *isRGBGrey;                 /*!< Set image mode IS_RGBIMG_GREY*/
    QAction *isRGB_ARGB;                /*!< Set image mode IS_RGBIMG_COLOR*/

    QAction *fullPictureMode;           /*!< Set full picture mode realtime*/
    QAction *pauseRealtime;             /*!< Set pause in realtime getting image*/
    QAction *timeOutRealtime;           /*!< Set timeout value (event)*/
    QAction *fullPictureModeSnap;       /*!< Set full picture mode snapshot*/

    /////////////
    QMenu *submenuImageFormat;
    QAction *setImageFormatIndex8;
        QAction *setImageFormatRGB32;
        QAction *setImageFormatARGB32;
        QAction *setImageFormatARGB32Pre;
        QAction *setImageFormatRGB16;
        QAction *setImageFormatARGB8565Pre;
        QAction *setImageFormatRGB666;
        QAction *setImageFormatARGB6666Pre;
        QAction *setImageFormatRGB555;
        QAction *setImageFormatARGB8555Pre;
        QAction *setImageFormatRGB888;
        QAction *setImageFormatRGB444;
        QAction *setImageFormatARGB4444Pre;
    ///////////


    /*! \brief Constructor*/
    MenuTab(MainWindow *);

    /*!
        \brief set picture mode on true
        \param mode - set this picture mode on true
    */
    void chImageMode(int mode);

    /*!
        \brief set correct icon for full picture mode
        \param val - set this full picture mode on val
    */
    void setChFullPictureMode(bool val);

    /*!
        \brief set correct icon for realtime pause
        \param val - set this realtime pause on val
    */
    void setRealtimePause(bool val);

    /*! \brief Destructor*/
    ~MenuTab();
signals:
    void initTangoSettingWin(int param);        /*!< \brief init tangosettingwin \param param - VideoSettingsWinValue*/
    void initStartTangoWin();                   /*!< \brief init starttangowin*/
   // void sendCommandSignal(QString command);
    void changeServerManipulation();            /*!< \brief set server operation*/
    void changeFullPictureMode();               /*!< \brief change full picture mode realtime*/
    void changeFullPictureModeSnap();           /*!< \brief change full picture mode snapshot*/
   // void changeColorFormat(int);

    void chFlipHorSnapshot(bool val);           /*!< \brief set horizontal flip snapshot icon \param val - true/false icon*/
    void chFlipVerSnapshot(bool val);           /*!< \brief set vertical flip snapshot icon \param val - true/false icon*/
    void chFlipHorRealtime(bool val);           /*!< \brief set horizontal flip realtime icon \param val - true/false icon*/
    void chFlipVerRealtime(bool val);           /*!< \brief set vertical flip realtime icon \param val - true/false icon*/

    void saveSnap();                            /*!< \brief send save snapshot*/
    void resetImg();                            /*!< \brief reset subwindow*/
    void printSnap();                           /*!< \brief send print snapshot*/
    void mkSnap();                              /*!< \brief send make snapshot*/
    void setTangoAttrNames();                   /*!< \brief send set attributes name*/


public slots:
    /*! \brief on saveSnapshot event*/
    void saveCurSnapshot();

    /*! \brief on printSnapshot event*/
    void printCurSnapshot();

    /*! \brief on makeSnapshot event*/
    void mkSnapshot();

    /*! \brief on setBrightnessSnapshot event*/
    void settingBrightnessSnapshot() ;

    /*! \brief on setGammaSnapshot event*/
    void settingGammaSnapshot() ;

    /*! \brief on setContrastSnapshot event*/
    void settingContrastSnapshot();

    /*! \brief on chOnScaleSnapshot event*/
    void settingScaleSnapshot()    ;

    /*! \brief on chOnRotationSnapshot event*/
    void settingRotationSnapshot() ;

    /*! \brief on resetImgSnapshot event*/
    void setResetImgSnapshot()     ;

    /*! \brief on resetImgRealtime event*/
    void setResetImgRealtime()     ;

    /*! \brief on setBrightnessRealtime event*/
    void settingBrightnessRealtime();

    /*! \brief on setGammaRealtime event*/
    void settingGammaRealtime() ;

    /*! \brief on setContrastRealtime event*/
    void settingContrastRealtime();

    /*! \brief on setScaleRealtime event*/
    void settingScaleRealtime()  ;

    /*! \brief on setRotationRealtime event*/
    void settingRotationRealtime();

    /*! \brief on timeOutRealtime event*/
    void settingTimeOutRealtime();

    /*! \brief on chOnBrightnessRealtime event*/
    void onChBrightnessRealtime();

    /*! \brief on chOnGammaRealtime event*/
    void onChGammaRealtime() ;

    /*! \brief on chOnContrastRealtime event*/
    void onChContrastRealtime();

    /*! \brief on chOnScaleRealtime event*/
    void onChScaleRealtime()  ;

    /*! \brief on chOnRotationRealtime event*/
    void onChRotationRealtime();

    /*! \brief on chOnBrightnessSnapshot event*/
    void onChBrightnessSnapshot() ;

    /*! \brief on chOnGammaSnapshot event*/
    void onChGammaSnapshot() ;

    /*! \brief on chOnContrastSnapshot event*/
    void onChContrastSnapshot();

    /*! \brief on chOnScaleSnapshot event*/
    void onChScaleSnapshot()    ;

    /*! \brief on chOnRotationSnapshot event*/
    void onChRotationSnapshot() ;

    /*! \brief on horFlipRealtime event*/
    void changeFlipHorRealtime();

    /*! \brief on verFlipRealtime event*/
    void changeFlipVerRealtime();

    /*! \brief on horFlipSnapshot event*/
    void changeFlipHorSnapshot();

    /*! \brief on verFlipSnapshot event*/
    void changeFlipVerSnapshot();

    /*! \brief on addNewDevice event*/
    void startNewDevice();

    /*! \brief on pushCommand event*/
    void sendCommand();

    /*! \brief on serverManipulation event*/
    void setServerManipulation();

    /*! \brief on serverAttrNames event*/
    void setServerAttrNames();

    /*! \brief on exit event*/
    void exit();

    /*!
        \brief set Icon for horizontal flip snapshot
        \param val - value
    */
    void setChFlipHorSnapshot(bool val);

    /*!
        \brief set Icon for vertical flip snapshot
        \param val - value
    */
    void setChFlipVerSnapshot(bool val);

    /*!
        \brief set Icon for horizontal flip realtime
        \param val - value
    */
    void setChFlipHorRealtime(bool val);

    /*!
        \brief set Icon for vertical flip realtime
        \param val - value
    */
    void setChFlipVerRealtime(bool val);

    /*!
        \brief set Icons for pointer
        \param rt - pointer of realtime subwindow
    */
    void setRealtimeProp(SubWindowRealtime* rt);

    /*!
        \brief set Icons for pointer
        \param snap - pointer of snapshot subwindow
    */
    void setSnapshotProp(SubWindowSnapshot* snap);

    /*!
        \brief set Icon for serverManipulation
        \param val - value
    */
    void setChServerManip(bool val);

    /*! \brief on fullpicturemode event*/
    void setFullPictureMode();

    /*! \brief on fullpicturemodesnap event*/
    void setFullPictureModeSnap();

    /*!
        \brief set Icon for fullpicturemodesnap
        \param val - value
    */
    void setChFullPictureModeSnap(bool val);

    /*!
        \brief set enable for realtime Menu
        \param val - value
    */
    void setRealTimeEnable(bool val);

    /*!
        \brief set enable for snapshot Menu
        \param val - value
    */
    void setSnapshotEnable(bool val);

    /*!
        \brief set enable for Brightness Gamma Contrast setting
        \param val - value
    */
    void setBGCEnable(bool val);
};

#endif // MENUTAB_H
