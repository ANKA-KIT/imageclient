#include "realtimecontainer.h"

RealtimeContainer::RealtimeContainer(MainWindow *parent) : QWidget(parent)
{
    windowElement = parent;
    realtimeLast = curRealtime = -1;
    setVisible(false);
    emptyIcon = "/icons/true.png";
    trueIcon = ":/icons/true.png";

    QMenu *actSerSide = new QMenu("Server side operations", this);
    actSerSideR = new QAction(QIcon(trueIcon),"Read", this);
    actSerSideW = new QAction(QIcon(trueIcon),"Write", this);
    actSerSide->setEnabled(false);
    actSerSide->setIcon(QIcon(trueIcon));
    actSerSide->addAction(actSerSideR);
    actSerSide->addAction(actSerSideW);


    serverMode =new QMenu(tr("&Server Mode"),this);
    serverMode->setIcon(QIcon(emptyIcon));

    actSerKeepSide = new QMenu("Server keeping side", this);
    actSerKeepSideR = new QAction(QIcon(trueIcon),"Read", this);
    actSerKeepSideW = new QAction(QIcon(trueIcon),"Write", this);
    actSerKeepSide->setIcon(QIcon(trueIcon));
    actSerKeepSide->addAction(actSerKeepSideR);
    actSerKeepSide->addAction(actSerKeepSideW);

    serverMode->addMenu(actSerKeepSide);
    serverMode->addMenu(actSerSide);
    actSerKeepSideW->setIconVisibleInMenu(false);
    actSerKeepSideR->setIconVisibleInMenu(false);
    actSerKeepSide->menuAction()->setIconVisibleInMenu(false);
    actSerKeepSideR->setIcon(QIcon(emptyIcon));
    actSerKeepSideW->setIcon(QIcon(emptyIcon));
    actSerKeepSide->setIcon(QIcon(emptyIcon));
    actSerSide->menuAction()->setIconVisibleInMenu(false);
    actSerSide->setIcon(QIcon(emptyIcon));
    actSerSideR->setIcon(QIcon(emptyIcon));
    actSerSideW->setIcon(QIcon(emptyIcon));
    actSerSideR->setIconVisibleInMenu(false);
    actSerSideW->setIconVisibleInMenu(false);

    actClientSide =  new QAction(QIcon(trueIcon),"Client Mode", this);
    actClientSide->setIconVisibleInMenu(true);

    connect(actSerKeepSideR,SIGNAL(triggered()),SLOT(setServerModeR()));
    connect(actSerKeepSideW,SIGNAL(triggered()),SLOT(setServerModeW()));
    connect(actClientSide,SIGNAL(triggered()),SLOT(setClientSideMode()));
}

void RealtimeContainer::realtimeChanged(SubWindow* curRealtimeWin){
    if (curRealtimeWin) {
        QList<RealtimeSubWindow*>::iterator iter;
        int  i = 0;
        for (iter = realtimeList.begin(); iter < realtimeList.end(); ++iter){
            if(curRealtimeWin == *iter){                             /*Find current window in list of realtime windows*/
                curRealtime = realtimeList.indexOf((RealtimeSubWindow*)curRealtimeWin);
                realtimeLast = curRealtime;
                setModeIcon();
                break;
                }
            i++;
        }
        connect(realtimeList.at(curRealtime)->tim, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)),Qt::UniqueConnection);
        connect(realtimeList.at(curRealtime)->tim, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)),Qt::UniqueConnection);
        connect(realtimeList.at(curRealtime)->tim, SIGNAL(rgbImageColor(int,int,int)), windowElement, SLOT(curColor(int,int,int)),Qt::UniqueConnection);
    } else {
         disconnect(realtimeList.at(curRealtime)->tim, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)));
         disconnect(realtimeList.at(curRealtime)->tim, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)));
         disconnect(realtimeList.at(curRealtime)->tim, SIGNAL(rgbImageColor(int,int,int)), windowElement, SLOT(curColor(int,int,int)));
         curRealtime = -1;
    }
}



void RealtimeContainer::onCloseRaltime(QObject *pointer){
    qDebug("ERase Realsubwin");
    QList<RealtimeSubWindow*>::iterator iter;
    for (iter = realtimeList.begin(); iter < realtimeList.end(); ++iter){
         if(pointer == *iter){
            realtimeList.erase(iter);
            break;
        }
    }
    if (realtimeList.count() == 0){
        curRealtime = -1;
        realtimeLast = -1;
    }
}


void RealtimeContainer::setServerModeR(){
    if (getRealtimeLastVal() !=-1){
        actClientSide->setIconVisibleInMenu(false);
        actSerKeepSide->menuAction()->setIconVisibleInMenu(true);
        actSerKeepSideR->setIconVisibleInMenu(true);
        actSerKeepSideW->setIconVisibleInMenu(false);
        serverMode->setIcon(QIcon(trueIcon));
        actClientSide->setIcon(QIcon(emptyIcon));
        actSerKeepSide->menuAction()->setIcon(QIcon(trueIcon));
        actSerKeepSideR->setIcon(QIcon(trueIcon));
        actSerKeepSideW->setIcon(QIcon(emptyIcon));
        RealtimeSubWindow *rt = getRealtimeLastWin();
        rt->setServerModeRead(true);
        if (rt->tim->__serverMode == TImage::SINGLE) setModeIcon();
    }
}

void RealtimeContainer::setServerModeW(){
    if (getRealtimeLastVal() !=-1){
        actClientSide->setIconVisibleInMenu(false);
        actSerKeepSide->menuAction()->setIconVisibleInMenu(true);
        actSerKeepSideR->setIconVisibleInMenu(false);
        actSerKeepSideW->setIconVisibleInMenu(true);

        serverMode->setIcon(QIcon(trueIcon));
        actClientSide->setIcon(QIcon(emptyIcon));
        actSerKeepSide->menuAction()->setIcon(QIcon(trueIcon));
        actSerKeepSideR->setIcon(QIcon(emptyIcon));
        actSerKeepSideW->setIcon(QIcon(trueIcon));
        RealtimeSubWindow *rt = getRealtimeLastWin();
        rt->setServerModeWrite(true);
        if (rt->tim->__serverMode == TImage::SINGLE) setModeIcon();  //in case incorect parameter value it will be Client Mode
    }
}

void RealtimeContainer::setClientSideMode(){
    if (getRealtimeLastVal() !=-1){
        actClientSide->setIconVisibleInMenu(true);
        actSerKeepSide->menuAction()->setIconVisibleInMenu(false);
        actSerKeepSideR->setIconVisibleInMenu(false);
        actSerKeepSideW->setIconVisibleInMenu(false);

        serverMode->setIcon(QIcon(emptyIcon));
        actClientSide->setIcon(QIcon(trueIcon));
        actSerKeepSide->menuAction()->setIcon(QIcon(emptyIcon));
        actSerKeepSideR->setIcon(QIcon(emptyIcon));
        actSerKeepSideW->setIcon(QIcon(emptyIcon));
        RealtimeSubWindow *rt = getRealtimeLastWin();
        rt->setClientSideMode(true);
    }

}
void RealtimeContainer::setModeIcon(){
    if (getRealtimeLastVal() !=-1){
        switch(getRealtimeLastImage()->__serverMode){
            case TImage::SINGLE:
                actClientSide->setIconVisibleInMenu(true);
                actSerKeepSide->menuAction()->setIconVisibleInMenu(false);
                actSerKeepSideR->setIconVisibleInMenu(false);
                actSerKeepSideW->setIconVisibleInMenu(false);

                serverMode->setIcon(QIcon(emptyIcon));
                actClientSide->setIcon(QIcon(trueIcon));
                actSerKeepSide->menuAction()->setIcon(QIcon(emptyIcon));
                actSerKeepSideR->setIcon(QIcon(emptyIcon));
                actSerKeepSideW->setIcon(QIcon(emptyIcon));
                break;
            case TImage::WRITE:
                actClientSide->setIconVisibleInMenu(false);
                actSerKeepSide->menuAction()->setIconVisibleInMenu(true);
                actSerKeepSideR->setIconVisibleInMenu(false);
                actSerKeepSideW->setIconVisibleInMenu(true);

                serverMode->setIcon(QIcon(trueIcon));
                actClientSide->setIcon(QIcon(emptyIcon));
                actSerKeepSide->menuAction()->setIcon(QIcon(trueIcon));
                actSerKeepSideR->setIcon(QIcon(emptyIcon));
                actSerKeepSideW->setIcon(QIcon(trueIcon));
                break;
            case TImage::READ:
                actClientSide->setIconVisibleInMenu(false);
                actSerKeepSide->menuAction()->setIconVisibleInMenu(true);
                actSerKeepSideR->setIconVisibleInMenu(true);
                actSerKeepSideW->setIconVisibleInMenu(false);
                serverMode->setIcon(QIcon(trueIcon));
                actClientSide->setIcon(QIcon(emptyIcon));
                actSerKeepSide->menuAction()->setIcon(QIcon(trueIcon));
                actSerKeepSideR->setIcon(QIcon(trueIcon));
                actSerKeepSideW->setIcon(QIcon(emptyIcon));
                break;
        }
    }
}
