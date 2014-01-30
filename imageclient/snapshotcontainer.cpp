#include "snapshotcontainer.h"

SnapshotContainer::SnapshotContainer(MainWindow *parent) :
    QObject(parent)
{
    windowElement = parent;
}
void SnapshotContainer::snapshotChanged(SubWindow* curSnapWin){
    qDebug("MainWindow::SnapshotChanged");
    if(curSnapWin){
        QList<SnapshotSubWindow*>::iterator iter;
        int  i = 0;
        for (iter = snapshotList.begin(); iter < snapshotList.end(); ++iter){
            if(curSnapWin == *iter){                            /*Find current window in list of snapshot windows*/
                curSnapshot = snapshotList.indexOf((SnapshotSubWindow*)curSnapWin);
                snapshotLast = curSnapshot;
                break;
            }
            i++;
        }
        connect(snapshotList.at(curSnapshot)->snp, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)),Qt::UniqueConnection);
        connect(snapshotList.at(curSnapshot)->snp, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)),Qt::UniqueConnection);
        connect(snapshotList.at(curSnapshot)->snp, SIGNAL(rgbImageColor(int,int,int)), windowElement, SLOT(curColor(int,int,int)),Qt::UniqueConnection);
    }
    else{
        disconnect(snapshotList.at(curSnapshot)->snp, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)));
        disconnect(snapshotList.at(curSnapshot)->snp, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)));
        disconnect(snapshotList.at(curSnapshot)->snp, SIGNAL(rgbImageColor(int,int,int)), windowElement, SLOT(curColor(int,int,int)));
        curSnapshot = -1;
    }
}

void SnapshotContainer::onCloseSnapshot(QObject *pointer){
    qDebug("ERase Snapsubwin");
    QList<SnapshotSubWindow*>::iterator iter;
    for (iter = snapshotList.begin(); iter < snapshotList.end(); ++iter){
         if(pointer == *iter){
            snapshotList.erase(iter);
            break;
        }
    }
    if (snapshotList.count() == 0){
        curSnapshot = -1;
    }
}
