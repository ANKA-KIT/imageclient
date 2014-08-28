#include "realtimecontainer.h"

#include <QDebug>

RealtimeContainer::RealtimeContainer(MainWindow *parent) : QWidget(parent)
{
    windowElement = parent;
    realtimeLast = 0;
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

void RealtimeContainer::windowActivated(SubWindow* curRealtimeWin){
    qDebug() << "MainWindow::SnapshotChanged -> activated " << curRealtimeWin;
    RealtimeSubWindow* realtimeWindow = dynamic_cast<RealtimeSubWindow*>(curRealtimeWin);
    if (!realtimeWindow) {
        qDebug() << "Wrong window type passed. Doing nothing.";
        return;
    }
    connect(realtimeWindow->tim, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)), Qt::UniqueConnection);
    connect(realtimeWindow->tim, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)), Qt::UniqueConnection);
    connect(realtimeWindow->tim, SIGNAL(rgbImageColor(int, int, int)), windowElement, SLOT(curColor(int, int, int)), Qt::UniqueConnection);
    realtimeLast = realtimeWindow;
    setModeIcon();
}

void RealtimeContainer::windowDeactivated(SubWindow* curRealtimeWin){
    qDebug() << "MainWindow::SnapshotChanged -> activated " << curRealtimeWin;
    RealtimeSubWindow* realtimeWindow = dynamic_cast<RealtimeSubWindow*>(curRealtimeWin);
    if (!realtimeWindow) {
        qDebug() << "Wrong window type passed. Doing nothing.";
        return;
    }
    disconnect(realtimeWindow->tim, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)));
    disconnect(realtimeWindow->tim, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)));
    disconnect(realtimeWindow->tim, SIGNAL(rgbImageColor(int, int, int)), windowElement, SLOT(curColor(int, int, int)));
    realtimeLast = 0;
}

void RealtimeContainer::onCloseRaltime(QObject *pointer){
    qDebug("ERase Realsubwin");
}

void RealtimeContainer::setServerModeR(){
    if (getRealtimeLastWin()) {
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
    if (getRealtimeLastWin()) {
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
    if (getRealtimeLastWin()) {
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
    if (getRealtimeLastWin()) {
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
