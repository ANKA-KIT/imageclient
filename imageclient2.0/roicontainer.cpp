#include "roicontainer.h"

RoiContainer::RoiContainer(QObject *parent) :
    QObject(parent)
{
}

void RoiContainer::roiChanged(SubWindow* curWin){
    if(curWin){             //if realtimewindow active
        QList<RoiSubWindow*>::iterator iter;
        int  i = 0;
        for (iter = roiList.begin(); iter < roiList.end(); ++iter){
            if(curWin == *iter){                             /*Find current window in list of realtime windows*/
                curRoi = roiList.indexOf((RoiSubWindow*)curWin);
                roiLast = curRoi;
                break;
                }
            i++;
        }
    }
    else{
         curRoi = -1;
    }
}



void RoiContainer::onCloseRoi(QObject *pointer){
    qDebug("ERase Roisubwin");
    QList<RoiSubWindow*>::iterator iter;
    for (iter = roiList.begin(); iter < roiList.end(); ++iter){
         if(pointer == *iter){
            roiList.erase(iter);
            break;
        }
    }
    if (roiList.count() == 0){
        curRoi = -1;
        roiLast = -1;
    }
}
