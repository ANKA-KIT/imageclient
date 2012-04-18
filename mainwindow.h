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

struct thread_data{
   MainWindow *parent;
   int threadNum;
};

class ImageWidget : public QWidget{
    Q_OBJECT
public:
    QPainter *paint;
    int mouseX;
    int mouseY;
public slots:
    void mousePressEvent ( QMouseEvent * e);
    void mouseMoveEvent ( QMouseEvent * e);
    void paintEvent( QPaintEvent * event);
};


class SubWindow : public QMdiSubWindow{
    Q_OBJECT
public:
    MainWindow *parent;
    SubWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    void setParent(MainWindow *);
    void closeEvent ( QCloseEvent * closeEvent);
    void focusInEvent ( QFocusEvent *e);
public:
    bool isSnapshot;
    int numOfWin;
    bool work;
    QString attrName;
    Tango::DeviceProxy *device;
    ImageWidget *wgt;
    QScrollArea *scrollArea;
    //Tango::DeviceAttribute *attr;
    int dimX;
    int dimY;
    vector <unsigned char> val;
    QImage *img;

    ~SubWindow();
public slots:
    //void delSubWin(QCloseEvent * closeEvent);
    void handleWindowStateChanged(Qt::WindowStates, Qt::WindowStates);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int countDev;
    int curDev;
    int curImg;
    int countImg;
    QMdiArea* area;
    SubWindow *subWin;
    bool firstTime;

    SubWindow *subWinSnapPointer;
    QList<SubWindow *> listSnap;


    ~MainWindow();

public:
    Ui::MainWindow *ui;
    void addDevice(QString s);
    void test();
public slots:
    void openDevInNewProc();
    void scaleImage();
    void startTesting(void*);
    void mkSnapshot();
    void changeDevice();
    void addNewSubWin();
    void delSubWin();
    void mousePressEvent ( QMouseEvent * e);
    void resizeEvent( QResizeEvent *e);
    void closeEvent ( QCloseEvent * closeEvent);
    QImage scaleImage(QImage image);

    void insertSnapShot();

};


#endif // MAINWINDOW_H
