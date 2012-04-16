#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tango.h>
#include <QtGui>
#include <QList>
#include <pthread.h>
#include <semaphore.h>
#include <QThread>

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
    SubWindow *nextSubWin;
    bool isSnapshot;
    int numOfWin;
    bool work;
    QString attrName;
    Tango::DeviceProxy *device;
    ImageWidget *wgt;
    QScrollArea *scrollArea;
    Tango::DeviceAttribute *attr;
    QImage *img;

    ~SubWindow();
public slots:
    //void delSubWin(QCloseEvent * closeEvent);
    void handleWindowStateChanged(Qt::WindowStates, Qt::WindowStates);

};


class mythread : public QThread{
    Q_OBJECT
public:
    thread_data data;
    mythread();
    mythread(MainWindow *w, int n);

protected:
    void run();

signals:
    void done(const QString &results);
    void* signal(void*);
private slots:
    void doTheWork();
    void stop();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    pthread_mutex_t *mutex;
    sem_t threadCount;

//    QString attrName;
    int countDev;
    int curDev;
    int curImg;
    int countImg;
    QMdiArea* area;
    SubWindow *subWin;

//    SubWindow *subWinSnap;
//    SubWindow *subWinSnapTail;
    SubWindow *subWinSnapPointer;
    QList<SubWindow *> listSnap;
    mythread *thr;


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
