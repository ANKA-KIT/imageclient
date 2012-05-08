/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tango.h>
#include <QtGui>
#include <QList>
#include <enum.h>

namespace Ui {
class MainWindow;
}
class MainWindow;
class SubWindow;

/*Send command*/
class VideoSettingsWin : public QWidget{
    Q_OBJECT
public:
    int param;
    MainWindow *parent;
    QWidget *centralWidget;
    //SubWindow *window;
    VideoSettingsWin(MainWindow *main, int param);//, SubWindow* win);
    QLabel *lb;
    QLineEdit *tl;
    QPushButton *btOk;
    QPushButton *btCancel;
    void initButtons();
    void initText();
    void initTextLine();
    ~VideoSettingsWin();
public slots:
    //void closeEvent ( QCloseEvent * closeEvent);
};

/*Send command*/
class CommandLine : public QWidget{
    Q_OBJECT
public:
    MainWindow *parent;
    QWidget *centralWidget;
    CommandLine(MainWindow *main);
    QLabel *lbCommand;
    QLineEdit *tlCommand;
    QPushButton *btSend;
    QPushButton *btCancel;
    void initButtons();
    void initText();
    void initTextLine();
    ~CommandLine();
public slots:

    void closeEvent ( QCloseEvent * closeEvent);
};

/*Tango settings*/
class TangoProperties : public QWidget{
    Q_OBJECT
public:
    TangoProperties(MainWindow *main);
    ~TangoProperties();
    MainWindow *parent;
    QWidget *centralWidget;
    QLineEdit *tlAttr;
    QLineEdit *tlDevice;
    QLineEdit *tlServer;
    QLabel *lbServer;
    QLabel *lbDevice;
    QLabel *lbAttr;

    QPushButton *btCancel;
    QPushButton *btNewDev;
    QPushButton *btChangeDevice;
    void initButtons();
    void initText();
    void initTextLine();
public slots:

    void closeEvent ( QCloseEvent * closeEvent);
};


/*display Images*/
class ImageWidget : public QWidget{
    Q_OBJECT
public:
    MainWindow *parent;
    int mouseX;                             //Mouse position
    int mouseY;                             //Mouse position
    int lastMouseX;                         //Mouse position when clicked last time
    int lastMouseY;                         //Mouse position when clicked last time
    void setParent(MainWindow *);
public slots:
    void mousePressEvent ( QMouseEvent * e);
    void mouseMoveEvent ( QMouseEvent * e);
    void paintEvent( QPaintEvent * event);
};

/*Subwindows of MainWindow*/
class SubWindow : public QMdiSubWindow{
    Q_OBJECT
public:
    MainWindow *parent;
    SubWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    void setParent(MainWindow *);                   // overloaded
    void closeEvent ( QCloseEvent * closeEvent);
public:
    bool isSnapshot;
    int numOfWin;
    bool work;                      // on/off thread of reading data from Tango Server
    QString attrName;
    Tango::DeviceProxy *device;
    ImageWidget *wgt;
    QScrollArea *scrollArea;
    int dimX;                       //image size
    int dimY;                       //image size
    vector <unsigned char> val;     //keep image data (used in making snapshot)
    QImage *img;                    //Image
    double scale;                   //scale value
    bool verFlip;
    bool horFlip;
    int rotation;
    int contrast;
    int brightness;
    int gamma;
    QImage *imgOrigin;                    //Image

    ~SubWindow();
public slots:
    void handleWindowStateChanged(Qt::WindowStates, Qt::WindowStates);
};


/*MainWindow*/
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int curImg;                         //current snapshot subwindow
    int countImg;                       //count of snapshot subwindows

    double delim;                       //need in choosing different color format
    QString colorFormat;
    int intColorFormat;

    QMdiArea* area;                     //area for displaying subwindows
    SubWindow *subWin;                  //realtime subwindow
    bool firstTime;                     //is it first time showed realtime subwindow
    TangoProperties *tangoDev;          //Window for seting tango properties
    CommandLine *cmdTangoLine;          //Window for sending command to current tango device
    VideoSettingsWin *vSetting;

    SubWindow *subWinSnapPointer;       //Pointer to current snapshot
    QList<SubWindow *> listSnap;        //List snapshot subwindows
    void createMenu();                  //init Menu
    void createActions();               //init Actions
    ~MainWindow();

    QMenu *server;                      //Server menu
    QMenu *snapshot;                    //Snapshot menu
    QMenu *realtime;                    //Realtime menu
    QMenu *submenuImageFormat;

    QAction *setDevice;                 //set for current app tango device
    QAction *addNewDevice;              //set tango device in new app
    QAction *pushCommand;               //set tango command
    QAction *exitAct;                   //Stop app

    QAction *scaleRealtime;
    QAction *setBrightnessRealtime;
    QAction *setContrastRealtime;
    QAction *setGammaRealtime;
    QAction *setRotationRealtime;
    QAction *verFlipRealtime;
    QAction *horFlipRealtime;
    QAction *resetImgRealtime;

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

    QAction *makeSnapshot;              //Make snapshot
    QAction *saveSnapshot;              //Save current snapshot
    QAction *scaleSnapshot;             //scale current snapshot  //not used
    QAction *horFlipSnapshot;
    QAction *verFlipSnapshot;
    QAction *setBrightnessSnapshot;
    QAction *setContrastSnapshot;
    QAction *setGammaSnapshot;
    QAction *setRotationSnapshot;
    QAction *resetImgSnapshot;

    int isWork(int);                    //!!!!!!need in remaning!!!!!!!!!
public:
    Ui::MainWindow *ui;
    Tango::DeviceProxy addDevice(QString s);          //Set Tango device
    Tango::DeviceAttribute setTangoAttr(Tango::DeviceProxy &device, QString attrName);
    void setImage(Tango::DeviceAttribute &attr);
    void tangoDeviceWin();
    void vSettingWin(int param);
public slots:
    void openDevInNewProc();            //Start Tango device in new process
    void scaleImage();                  //scale snapshot
    QImage scaleImage(QImage image);    //scale realtime subwindow
    void startTesting();           //reading data from Tango server
    void mkSnapshot();                  //Make snapshot
    void changeDevice();                //Starting realtime subwindow where will be showed data from Tango server
    void closeEvent ( QCloseEvent * closeEvent);
    void resizeEvent( QResizeEvent *e );

    void contextMenuEvent(QContextMenuEvent *event);
    void setRealtimeScale();            //set Realtime Scale
    void setSnapshotScale();            //set Snapshot Scale
    void changeScaleSnapshot();
    void sendTangoCommand(Tango::DeviceProxy *, QString);            //Send a tango command to current tango device
    void sendTangoCommandSLOT();
    void setTangoCommand();             //Set a tango command to current tango device
    void saveImg();
    void setTangoDevice();
    void setNewTangoDevice();
    void changeColorFormat(int);
    void changeBrightnessSnapshot();
    void changeContrastSnapshot();
    void changeGammaSnapshot();
    void rotateImg(int);
    void rotateImg();
    void setFlipHor();
    void setFlipVer();

    void cancelTangoProperties();
    void cancelVSettingWin();
    void cancelCommandLine();
    void setEnabledSnapshot(bool);

    void settingBrightnessSnapshot();
    void settingGammaSnapshot();
    void settingContrastSnapshot();
    void settingScaleSnapshot();
    void settingRotationSnapshot();
    void setResetImgSnapshot();
    void delVSetting();
    void settingBrightnessRealtime();
    void settingGammaRealtime();
    void settingContrastRealtime();
    void settingScaleRealtime();
    void settingRotationRealtime();
    void setResetImgRealtime();

/*    void setBrightnessSnapshotValue(int );
    void setGammaSnapshotValue(int );
    void setContrastSnapshotValue(int );
    void setRotateImgValue(int );
    void setScaleSnapshotValue(double);
*/
    void setBrightnessValue(int, SubWindow &subwinPointer);
    void setGammaValue(int, SubWindow &subwinPointer );
    void setContrastValue(int, SubWindow &subwinPointer );
    void setRotateImgValue(int, SubWindow &subwinPointer );
    void setScaleSnapshotValue(double);


    void changeScaleRealtime();
    void setScaleRealtimeValue(double);
    void changeBrightnessRealtime();
    void setBrightnessRealtimeValue(int val);
    void changeContrastRealtime();
    void setContrastRealtimeValue(int val);
    void changeGammaRealtime();
    void setGammaRealtimeValue(int val);
    void changeFlipHorRealtime();
    void changeFlipVerRealtime();
    QImage setFlipHorRealtime(QImage&);
    QImage setFlipVerRealtime(QImage&);
    void setRotateImgRealtimeValue(double);
    void changeRotationRealtime();

    void setIndex8();
    void setRGB32();
    void setARGB32();
    void setARGB32Pre();
    void setRGB16();
    void setARGB8565Pre();
    void setRGB666();
    void setARGB6666Pre();
    void setRGB555();
    void setARGB8555Pre();
    void setRGB888();
    void setRGB444();
    void setARGB4444Pre();


    QImage chGamma(QImage &, int);
    QImage chContrast(QImage &, int);
    QImage chBrightness(QImage &, int);

};


#endif // MAINWINDOW_H
