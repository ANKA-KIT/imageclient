#ifndef RoiContainer_H
#define RoiContainer_H

#include <QObject>
#include <roisubwindow.h>
#include  "mainwindow.h"
class MainWindow;

class RoiContainer : public QObject
{
    Q_OBJECT
private:
    MainWindow* windowElement;
    int curRoi;
    int roiLast;
    QList<RoiSubWindow *> roiList;
public:
    explicit RoiContainer(MainWindow *parent = 0);
    void add(RoiSubWindow *roi){roiList.push_back(roi);}
    int getRoiLastVal(){return roiLast;}
    RoiSubWindow* getRoiLastWin(){return roiList[roiLast];}
    RoiSubWindow* getRoiCurWin(){return roiList[curRoi];}
    ROIClass* getRoiLastImage(){return roiList.at(roiLast)->roi;}
signals:

public slots:
    void roiChanged(SubWindow*);
    void onCloseRoi(QObject *pointer);
    
};

#endif // RoiContainer_H
