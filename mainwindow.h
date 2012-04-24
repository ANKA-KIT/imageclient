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


namespace Ui {
class MainWindow;
}
class MainWindow;

/*used in version with multi threading (data which transfered to MainWindow::startTesting)*/
struct thread_data{
   MainWindow *parent;                      //Main window
   int threadNum;                           //current Realtime subwin   //(not used)
};

/*Send command*/
class CommandLine : public QWidget{
    Q_OBJECT
public:
    MainWindow *parent;
    QWidget *centralWidget;
    CommandLine(MainWindow *main, CommandLine *MainWindow);
    QLabel *lbCommand;
    QLineEdit *tlCommand;
    QPushButton *btSend;
    QPushButton *btCancel;
};

/*Tango settings*/
class TangoProperties : public QWidget{
    Q_OBJECT
public:
    TangoProperties(MainWindow *main, TangoProperties *MainWindow);
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
    double scale;

    ~SubWindow();
public slots:
    void handleWindowStateChanged(Qt::WindowStates, Qt::WindowStates);
    void saveImg();
};


/*MainWindow*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int countDev;                       //const //count of realtime subwindows
    int curDev;                         //const //current realtime subwindow
    int curImg;                         //current snapshot subwindow
    int countImg;                       //count of snapshot subwindows
    QMdiArea* area;                     //area for displaying subwindows
    SubWindow *subWin;                  //realtime subwindow
    bool firstTime;                     //is it first time showed realtime subwindow
    TangoProperties *tangoDev;          //Window for seting tango properties
    CommandLine *cmdTangoLine;          //Window for sending command to current tango device

    SubWindow *subWinSnapPointer;       //Pointer to current snapshot
    QList<SubWindow *> listSnap;        //List snapshot subwindows
    void createMenu();                  //init Menu
    void createActions();               //init Actions
    ~MainWindow();

    QMenu *server;                      //Server menu
    QMenu *snapshot;                    //Snapshot menu

    QAction *setDevice;                 //set for current app tango device
    QAction *addNewDevice;              //set tango device in new app
    QAction *pushCommand;
    QAction *exitAct;                   //Stop app

    QAction *makeSnapshot;              //Make snapshot
    QAction *saveSnapshot;              //Save current snapshot
    QAction *scaleSnapshot;             //scale current snapshot  //not used

    QStringList tangoCommands;
public:
    Ui::MainWindow *ui;
    void addDevice(QString s);          //Set Tango device
public slots:
    void openDevInNewProc();            //Start Tango device in new process
    void scaleImage();                  //scale snapshot
    QImage scaleImage(QImage image);    //scale realtime subwindow
    void startTesting(void*);           //reading data from Tango server
    void mkSnapshot();                  //Make snapshot
    void changeDevice();                //Starting realtime subwindow where will be showed data from Tango server
    void closeEvent ( QCloseEvent * closeEvent);
    void resizeEvent( QResizeEvent *e );

    void contextMenuEvent(QContextMenuEvent *event);
    void setTangoDevice();
    void setRealtimeScale();            //set Realtime Scale
    void setSnapshotScale();            //set Snapshot Scale
    void sendTangoCommand();            //Send a command to current tango device
};


#endif // MAINWINDOW_H
