#ifndef RealtimeContainer_H
#define RealtimeContainer_H

#include <QObject>
#include <QMenu>
#include <realtimesubwindow.h>

#include  "mainwindow.h"
class MainWindow;

class RealtimeContainer : public QWidget
{
    Q_OBJECT
private:
    MainWindow* windowElement;
    void setModeIcon();
    RealtimeSubWindow* realtimeLast;
    QString emptyIcon, trueIcon;
public:
    QAction *actSerSideR;
    QAction *actSerSideW;
    QAction *actSerKeepSideR;
    QAction *actSerKeepSideW;
    QAction *actClientSide;
    QMenu *actSerKeepSide;
    QMenu *serverMode;

    explicit RealtimeContainer(MainWindow *parent = 0);
    RealtimeSubWindow* getRealtimeLastWin()
    {
        return realtimeLast;
    }
    TImage* getRealtimeLastImage()
    {
        return realtimeLast->tim;
    }
signals:

public slots:
    void windowActivated(SubWindow*);
    void windowDeactivated(SubWindow*);
    void onCloseRaltime(QObject *pointer);

    void setServerModeR();
    void setServerModeW();
    void setClientSideMode();
};

#endif // RealtimeContainer_H
