#ifndef RealtimeContainer_H
#define RealtimeContainer_H

#include <QObject>
#include <QMenu>
#include <realtimesubwindow.h>

class RealtimeContainer : public QWidget//QObject
{
    Q_OBJECT
private:
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

    explicit RealtimeContainer(QWidget *parent = 0);//(QObject *parent = 0);
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
