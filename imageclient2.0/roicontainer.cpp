#include "roicontainer.h"

RoiContainer::RoiContainer(MainWindow *parent) :
    QObject(parent)
{
    windowElement = parent;
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
        connect(roiList.at(curRoi)->roi->sample, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)),Qt::UniqueConnection);
        connect(roiList.at(curRoi)->roi->sample, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)),Qt::UniqueConnection);
        connect(roiList.at(curRoi)->roi->sample, SIGNAL(rgbImageColor(int,int,int)), windowElement, SLOT(curColor(int,int,int)),Qt::UniqueConnection);
    }
    else{
         disconnect(roiList.at(curRoi)->roi->sample, SIGNAL(mousePosition(QPoint)), windowElement, SLOT(curPosition(QPoint)));
         disconnect(roiList.at(curRoi)->roi->sample, SIGNAL(greyscaleImageColor(int)), windowElement, SLOT(curColor(int)));
         disconnect(roiList.at(curRoi)->roi->sample, SIGNAL(rgbImageColor(int,int,int)), windowElement, SLOT(curColor(int,int,int)));
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
