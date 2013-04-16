#include "snapshotcontainer.h"

SnapshotContainer::SnapshotContainer(QObject *parent) :
    QObject(parent)
{
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
    }
    else{
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
