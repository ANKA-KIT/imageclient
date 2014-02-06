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
    int curRealtime;
    int realtimeLast;
    QList<RealtimeSubWindow *> realtimeList;
    void setModeIcon();
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
    void add(RealtimeSubWindow *rt){realtimeList.push_back(rt);}
    int getRealtimeLastVal(){return realtimeLast;}
    RealtimeSubWindow* getRealtimeLastWin(){return realtimeList[realtimeLast];}
    RealtimeSubWindow* getRealtimeCurWin(){return realtimeList[curRealtime];}
    TImage* getRealtimeLastImage(){return realtimeList.at(realtimeLast)->tim;}
signals:

public slots:
    void realtimeChanged(SubWindow*);
    void onCloseRaltime(QObject *pointer);

    void setServerModeR();
    void setServerModeW();
    void setClientSideMode();
};

#endif // RealtimeContainer_H
